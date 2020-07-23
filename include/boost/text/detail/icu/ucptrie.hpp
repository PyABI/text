// © 2017 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html

// ucptrie.h (modified from utrie2.h)
// created: 2017dec29 Markus W. Scherer

#ifndef UCPTRIE_H_
#define UCPTRIE_H_

#include <boost/text/detail/icu/ucpmap.hpp>
#include <boost/text/detail/icu/utf8.hpp>
#include <boost/text/detail/icu/utf16.hpp>

#include <boost/assert.hpp>

#include <cstring>
#include <memory>


namespace boost { namespace text { namespace detail { namespace icu {

    /**
     * \file
     *
     * This file defines an immutable Unicode code point trie.
     *
     * @see UCPTrie
     * @see UMutableCPTrie
     */

    /** @internal */
    typedef union UCPTrieData
    {
        /** @internal */
        const void * ptr0;
        /** @internal */
        const uint16_t * ptr16;
        /** @internal */
        const uint32_t * ptr32;
        /** @internal */
        const uint8_t * ptr8;
    } UCPTrieData;

    /**
     * Immutable Unicode code point trie structure.
     * Fast, reasonably compact, map from Unicode code points (U+0000..U+10FFFF)
     * to integer values. For details see
     * http://site.icu-project.org/design/struct/utrie
     *
     * Do not access UCPTrie fields directly; use public functions and macros.
     * Functions are easy to use: They support all trie types and value widths.
     *
     * When performance is really important, macros provide faster access.
     * Most macros are specific to either "fast" or "small" tries, see
     * UCPTrieType. There are "fast" macros for special optimized use cases.
     *
     * The macros will return bogus values, or may crash, if used on the wrong
     * type or value width.
     *
     * @see UMutableCPTrie
     * @draft ICU 63
     */
    struct UCPTrie
    {
        /** @internal */
        const uint16_t * index;
        /** @internal */
        UCPTrieData data;

        /** @internal */
        int32_t indexLength;
        /** @internal */
        int32_t dataLength;
        /** Start of the last range which ends at U+10FFFF. @internal */
        UChar32 highStart;
        /** highStart>>12 @internal */
        uint16_t shifted12HighStart;

        /** @internal */
        int8_t type; // UCPTrieType
        /** @internal */
        int8_t valueWidth; // UCPTrieValueWidth

        /** padding/reserved @internal */
        uint32_t reserved32;
        /** padding/reserved @internal */
        uint16_t reserved16;

        /**
         * Internal index-3 null block offset.
         * Set to an impossibly high value (e.g., 0xffff) if there is no
         * dedicated index-3 null block.
         * @internal
         */
        uint16_t index3NullOffset;
        /**
         * Internal data null block offset, not shifted.
         * Set to an impossibly high value (e.g., 0xfffff) if there is no
         * dedicated data null block.
         * @internal
         */
        int32_t dataNullOffset;
        /** @internal */
        uint32_t nullValue;
    };
    typedef struct UCPTrie UCPTrie;

    /**
     * Selectors for the type of a UCPTrie.
     * Different trade-offs for size vs. speed.
     *
     * @see umutablecptrie_buildImmutable
     * @see ucptrie_openFromBinary
     * @see ucptrie_getType
     * @draft ICU 63
     */
    enum UCPTrieType {
        /**
         * For ucptrie_openFromBinary() to accept any type.
         * ucptrie_getType() will return the actual type.
         * @draft ICU 63
         */
        ucptrie_type_any = -1,
        /**
         * Fast/simple/larger BMP data structure. Use functions and "fast"
         * macros.
         * @draft ICU 63
         */
        ucptrie_type_fast,
        /**
         * Small/slower BMP data structure. Use functions and "small" macros.
         * @draft ICU 63
         */
        ucptrie_type_small
    };
    typedef enum UCPTrieType UCPTrieType;

    /**
     * Selectors for the number of bits in a UCPTrie data value.
     *
     * @see umutablecptrie_buildImmutable
     * @see ucptrie_openFromBinary
     * @see ucptrie_getValueWidth
     * @draft ICU 63
     */
    enum UCPTrieValueWidth {
        /**
         * For ucptrie_openFromBinary() to accept any data value width.
         * ucptrie_getValueWidth() will return the actual data value width.
         * @draft ICU 63
         */
        ucptrie_value_bits_any = -1,
        /**
         * The trie stores 16 bits per data value.
         * It returns them as unsigned values 0..0xffff=65535.
         * @draft ICU 63
         */
        ucptrie_value_bits_16,
        /**
         * The trie stores 32 bits per data value.
         * @draft ICU 63
         */
        ucptrie_value_bits_32,
        /**
         * The trie stores 8 bits per data value.
         * It returns them as unsigned values 0..0xff=255.
         * @draft ICU 63
         */
        ucptrie_value_bits_8
    };
    typedef enum UCPTrieValueWidth UCPTrieValueWidth;

    // UCPTrie signature values, in platform endianness and opposite endianness.
    // The UCPTrie signature ASCII byte values spell "Tri3".
    namespace {
        constexpr uint32_t ucptrie_sig = 0x54726933;
        constexpr uint32_t ucptrie_oe_sig = 0x33697254;
    }

    /**
     * Header data for the binary, memory-mappable representation of a
     * UCPTrie/CodePointTrie.
     * @internal
     */
    struct UCPTrieHeader
    {
        /** "Tri3" in big-endian US-ASCII (0x54726933) */
        uint32_t signature;

        /**
         * Options bit field:
         * Bits 15..12: Data length bits 19..16.
         * Bits 11..8: Data null block offset bits 19..16.
         * Bits 7..6: UCPTrieType
         * Bits 5..3: Reserved (0).
         * Bits 2..0: UCPTrieValueWidth
         */
        uint16_t options;

        /** Total length of the index tables. */
        uint16_t indexLength;

        /** Data length bits 15..0. */
        uint16_t dataLength;

        /** Index-3 null block offset, 0x7fff or 0xffff if none. */
        uint16_t index3NullOffset;

        /** Data null block offset bits 15..0, 0xfffff if none. */
        uint16_t dataNullOffset;

        /**
         * First code point of the single-value range ending with U+10ffff,
         * rounded up and then shifted right by UCPTRIE_SHIFT_2.
         */
        uint16_t shiftedHighStart;
    };

    /**
     * Constants for use with UCPTrieHeader.options.
     * @internal
     */
    enum {
        ucptrie_options_data_length_mask = 0xf000,
        ucptrie_options_data_null_offset_mask = 0xf00,
        ucptrie_options_reserved_mask = 0x38,
        ucptrie_options_value_bits_mask = 7,
        /**
         * Value for index3NullOffset which indicates that there is no index-3
         * null block. Bit 15 is unused for this value because this bit is used
         * if the index-3 contains 18-bit indexes.
         */
        ucptrie_no_index3_null_offset = 0x7fff,
        ucptrie_no_data_null_offset = 0xfffff
    };

    /**
     * Internal implementation constants.
     * These are needed for the API macros, but users should not use these
     * directly.
     * @internal
     */
    enum {
        /** @internal */
        ucptrie_fast_shift = 6,

        /** Number of entries in a data block for code points below the fast
           limit. 64=0x40 @internal */
        ucptrie_fast_data_block_length = 1 << ucptrie_fast_shift,

        /** Mask for getting the lower bits for the in-fast-data-block offset.
           @internal */
        ucptrie_fast_data_mask = ucptrie_fast_data_block_length - 1,

        /** @internal */
        ucptrie_small_max = 0xfff,

        /**
         * Offset from dataLength (to be subtracted) for fetching the
         * value returned for out-of-range code points and ill-formed UTF-8/16.
         * @internal
         */
        ucptrie_error_value_neg_data_offset = 1,
        /**
         * Offset from dataLength (to be subtracted) for fetching the
         * value returned for code points highStart..U+10FFFF.
         * @internal
         */
        ucptrie_high_value_neg_data_offset = 2
    };

    /** @internal */
    int32_t ucptrie_internalSmallIndex(const UCPTrie * trie, UChar32 c);

    /** @internal */
    int32_t ucptrie_internalSmallU8Index(
        const UCPTrie * trie, int32_t lt1, uint8_t t2, uint8_t t3);

    /**
     * Internal function for part of the UCPTRIE_FAST_U8_PREVxx() macro
     * implementations. Do not call directly.
     * @internal
     */
    template<typename CharIter>
    int32_t ucptrie_internalU8PrevIndex(
        const UCPTrie * trie, UChar32 c, CharIter start, CharIter src);

    /** Internal trie getter for a code point below the fast limit. Returns the
     * data index. @internal */
    inline int ucptrie_fast_index_(const UCPTrie * trie, UChar32 c)
    {
        return (
            (int32_t)(trie)->index[(c) >> ucptrie_fast_shift] +
            ((c)&ucptrie_fast_data_mask));
    }

    /** Internal trie getter for a code point at or above the fast limit.
     * Returns the data index. @internal */
    inline int ucptrie_small_index_(const UCPTrie * trie, UChar32 c)
    {
        return (
            (c) >= (trie)->highStart
                ? (trie)->dataLength - ucptrie_high_value_neg_data_offset
                : detail::icu::ucptrie_internalSmallIndex(trie, c));
    }

    /**
     * Internal trie getter for a code point, with checking that c is in
     * U+0000..10FFFF. Returns the data index.
     * @internal
     */
    inline int
    ucptrie_cp_index_(const UCPTrie * trie, uint32_t fastMax, UChar32 c)
    {
        return (
            (uint32_t)(c) <= (uint32_t)(fastMax)
                ? detail::icu::ucptrie_fast_index_(trie, c)
                : (uint32_t)(c) <= 0x10ffff
                      ? detail::icu::ucptrie_small_index_(trie, c)
                      : (trie)->dataLength -
                            ucptrie_error_value_neg_data_offset);
    }

    /**
     * Macro parameter value for a trie with 16-bit data values.
     * Use the name of this macro as a "dataAccess" parameter in other macros.
     * Do not use this macro in any other way.
     *
     * @see UCPTRIE_VALUE_BITS_16
     * @draft ICU 63
     */
    inline uint16_t ucptrie_16(const UCPTrie * trie, int i)
    {
        return trie->data.ptr16[i];
    }

    /**
     * Macro parameter value for a trie with 32-bit data values.
     * Use the name of this macro as a "dataAccess" parameter in other macros.
     * Do not use this macro in any other way.
     *
     * @see UCPTRIE_VALUE_BITS_32
     * @draft ICU 63
     */
    inline uint32_t ucptrie_32(const UCPTrie * trie, int i)
    {
        return trie->data.ptr32[i];
    }

    /**
     * Macro parameter value for a trie with 8-bit data values.
     * Use the name of this macro as a "dataAccess" parameter in other macros.
     * Do not use this macro in any other way.
     *
     * @see UCPTRIE_VALUE_BITS_8
     * @draft ICU 63
     */
    inline uint8_t ucptrie_8(const UCPTrie * trie, int i)
    {
        return trie->data.ptr8[i];
    }

    /**
     * Returns a trie value for a code point, with range checking.
     * Returns the trie error value if c is not in the range 0..U+10FFFF.
     *
     * @param trie (const UCPTrie *, in) the trie; must have type
     * UCPTRIE_TYPE_FAST
     * @param dataAccess UCPTRIE_16, UCPTRIE_32, or UCPTRIE_8 according to the
     * trie’s value width
     * @param c (UChar32, in) the input code point
     * @return The code point's trie value.
     * @draft ICU 63
     */
    template<typename AccessFunc>
    inline auto
    ucptrie_fast_get(const UCPTrie * trie, AccessFunc dataAccess, UChar32 c)
        -> decltype(
            dataAccess(trie, detail::icu::ucptrie_cp_index_(trie, 0xffff, c)))
    {
        return dataAccess(
            trie, detail::icu::ucptrie_cp_index_(trie, 0xffff, c));
    }

    /**
     * Returns a 16-bit trie value for a code point, with range checking.
     * Returns the trie error value if c is not in the range U+0000..U+10FFFF.
     *
     * @param trie (const UCPTrie *, in) the trie; must have type
     * UCPTRIE_TYPE_SMALL
     * @param dataAccess UCPTRIE_16, UCPTRIE_32, or UCPTRIE_8 according to the
     * trie’s value width
     * @param c (UChar32, in) the input code point
     * @return The code point's trie value.
     * @draft ICU 63
     */
    template<typename AccessFunc>
    inline auto
    ucptrie_small_get(const UCPTrie * trie, AccessFunc dataAccess, UChar32 c)
        -> decltype(dataAccess(
            trie, detail::icu::ucptrie_cp_index_(trie, ucptrie_small_max, c)))
    {
        return dataAccess(
            trie, detail::icu::ucptrie_cp_index_(trie, ucptrie_small_max, c));
    }

    /**
     * UTF-16: Reads the next code point (UChar32 c, out), post-increments src,
     * and gets a value from the trie.
     * Sets the trie error value if c is an unpaired surrogate.
     *
     * @param trie (const UCPTrie *, in) the trie; must have type
     * UCPTRIE_TYPE_FAST
     * @param dataAccess UCPTRIE_16, UCPTRIE_32, or UCPTRIE_8 according to the
     * trie’s value width
     * @param src (const UChar *, in/out) the source text pointer
     * @param limit (const UChar *, in) the limit pointer for the text, or NULL
     * if NUL-terminated
     * @param c (UChar32, out) variable for the code point
     * @param result (out) variable for the trie lookup result
     * @draft ICU 63
     */
    template<
        typename AccessFunc,
        typename Iter,
        typename Sentinel,
        typename Out>
    inline void ucptrie_fast_u16_next(
        const UCPTrie * trie,
        AccessFunc dataAccess,
        Iter & src,
        Sentinel limit,
        UChar32 & c,
        Out & result)
    {
        (c) = *(src)++;
        int32_t index_;
        if (!detail::icu::u16_is_surrogate(c)) {
            index_ = detail::icu::ucptrie_fast_index_(trie, c);
        } else {
            uint16_t c2_;
            if (detail::icu::u16_is_surrogate_lead(c) && (src) != (limit) &&
                detail::icu::u16_is_trail(c2_ = *(src))) {
                ++(src);
                (c) = detail::icu::u16_get_supplementary((c), c2_);
                index_ = detail::icu::ucptrie_small_index_(trie, c);
            } else {
                index_ =
                    (trie)->dataLength - ucptrie_error_value_neg_data_offset;
            }
        }
        (result) = dataAccess(trie, index_);
    }

    /**
     * UTF-16: Reads the previous code point (UChar32 c, out), pre-decrements
     * src, and gets a value from the trie. Sets the trie error value if c is an
     * unpaired surrogate.
     *
     * @param trie (const UCPTrie *, in) the trie; must have type
     * UCPTRIE_TYPE_FAST
     * @param dataAccess UCPTRIE_16, UCPTRIE_32, or UCPTRIE_8 according to the
     * trie’s value width
     * @param start (const UChar *, in) the start pointer for the text
     * @param src (const UChar *, in/out) the source text pointer
     * @param c (UChar32, out) variable for the code point
     * @param result (out) variable for the trie lookup result
     * @draft ICU 63
     */
    template<typename AccessFunc, typename Iter, typename Out>
    void ucptrie_fast_u16_prev(
        const UCPTrie * trie,
        AccessFunc dataAccess,
        Iter start,
        Iter & src,
        UChar32 c,
        Out & result)
    {
        (c) = *--(src);
        int32_t index_;
        if (!detail::icu::u16_is_surrogate(c)) {
            index_ = detail::icu::ucptrie_fast_index_(trie, c);
        } else {
            uint16_t c2_;
            if (detail::icu::u16_is_surrogate_trail(c) && (src) != (start) &&
                detail::icu::u16_is_lead(c2_ = *std::prev(src))) {
                --(src);
                (c) = detail::icu::u16_get_supplementary(c2_, (c));
                index_ = detail::icu::ucptrie_small_index_(trie, c);
            } else {
                index_ =
                    (trie)->dataLength - ucptrie_error_value_neg_data_offset;
            }
        }
        (result) = dataAccess(trie, index_);
    }

    /**
     * UTF-8: Post-increments src and gets a value from the trie.
     * Sets the trie error value for an ill-formed byte sequence.
     *
     * Unlike ucptrie_fast_u16_next() this UTF-8 macro does not provide the code
     * point because it would be more work to do so and is often not needed. If
     * the trie value differs from the error value, then the byte sequence is
     * well-formed, and the code point can be assembled without revalidation.
     *
     * @param trie (const UCPTrie *, in) the trie; must have type
     * UCPTRIE_TYPE_FAST
     * @param dataAccess UCPTRIE_16, UCPTRIE_32, or UCPTRIE_8 according to the
     * trie’s value width
     * @param src (const char *, in/out) the source text pointer
     * @param limit (const char *, in) the limit pointer for the text (must not
     * be NULL)
     * @param result (out) variable for the trie lookup result
     * @draft ICU 63
     */
    template<
        typename AccessFunc,
        typename CharIter,
        typename Sentinel,
        typename Out>
    void ucptrie_fast_u8_next(
        const UCPTrie * trie,
        AccessFunc dataAccess,
        CharIter & src,
        Sentinel limit,
        Out & result)
    {
        int32_t lead_ = (uint8_t) * (src)++;
        if (!detail::icu::u8_is_single(lead_)) {
            uint8_t t1_, t2_, t3_;
            if ((src) != (limit) &&
                (lead_ >= 0xe0
                     ? lead_ < 0xf0 ? /* U+0800..U+FFFF except surrogates */
                           detail::icu::u8_lead3_t1_bits[lead_ &= 0xf] &
                                   (1 << ((t1_ = *(src)) >> 5)) &&
                               ++(src) != (limit) &&
                               (t2_ = *(src)-0x80) <= 0x3f &&
                               (lead_ =
                                    ((int32_t)(trie)
                                         ->index[(lead_ << 6) + (t1_ & 0x3f)]) +
                                    t2_,
                                1)
                                    : /* U+10000..U+10FFFF */
                           (lead_ -= 0xf0) <= 4 &&
                               detail::icu::u8_lead4_t1_bits
                                       [(t1_ = *(src)) >> 4] &
                                   (1 << lead_) &&
                               (lead_ = (lead_ << 6) | (t1_ & 0x3f),
                                ++(src) != (limit)) &&
                               (t2_ = *(src)-0x80) <= 0x3f &&
                               ++(src) != (limit) &&
                               (t3_ = *(src)-0x80) <= 0x3f &&
                               (lead_ =
                                    lead_ >= (trie)->shifted12HighStart
                                        ? (trie)->dataLength -
                                              ucptrie_high_value_neg_data_offset
                                        : detail::icu::
                                              ucptrie_internalSmallU8Index(
                                                  (trie), lead_, t2_, t3_),
                                1)
                     : /* U+0080..U+07FF */
                     lead_ >= 0xc2 && (t1_ = *(src)-0x80) <= 0x3f &&
                         (lead_ = (int32_t)(trie)->index[lead_ & 0x1f] + t1_,
                          1))) {
                ++(src);
            } else {
                lead_ = (trie)->dataLength -
                        ucptrie_error_value_neg_data_offset; /* ill-formed*/
            }
        }
        (result) = dataAccess(trie, lead_);
    }

    /**
     * UTF-8: Pre-decrements src and gets a value from the trie.
     * Sets the trie error value for an ill-formed byte sequence.
     *
     * Unlike ucptrie_fast_u16_prev() this UTF-8 macro does not provide the code
     * point because it would be more work to do so and is often not needed. If
     * the trie value differs from the error value, then the byte sequence is
     * well-formed, and the code point can be assembled without revalidation.
     *
     * @param trie (const UCPTrie *, in) the trie; must have type
     * UCPTRIE_TYPE_FAST
     * @param dataAccess UCPTRIE_16, UCPTRIE_32, or UCPTRIE_8 according to the
     * trie’s value width
     * @param start (const char *, in) the start pointer for the text
     * @param src (const char *, in/out) the source text pointer
     * @param result (out) variable for the trie lookup result
     * @draft ICU 63
     */
    template<typename AccessFunc, typename CharIter, typename Out>
    void ucptrie_fast_u8_prev(
        const UCPTrie * trie,
        AccessFunc dataAccess,
        CharIter start,
        CharIter & src,
        Out & result)
    {
        int32_t index_ = (uint8_t) * --(src);
        if (!detail::icu::u8_is_single(index_)) {
            index_ = detail::icu::ucptrie_internalU8PrevIndex(
                (trie), index_, start, src);
            (src) -= index_ & 7;
            index_ >>= 3;
        }
        (result) = dataAccess(trie, index_);
    }

    /**
     * Returns a trie value for an ASCII code point, without range checking.
     *
     * @param trie (const UCPTrie *, in) the trie (of either fast or small type)
     * @param dataAccess UCPTRIE_16, UCPTRIE_32, or UCPTRIE_8 according to the
     * trie’s value width
     * @param c (UChar32, in) the input code point; must be U+0000..U+007F
     * @return The ASCII code point's trie value.
     * @draft ICU 63
     */
    template<typename AccessFunc>
    auto
    ucptrie_ascii_get(const UCPTrie * trie, AccessFunc dataAccess, UChar32 c)
        -> decltype(dataAccess(trie, c))
    {
        return dataAccess(trie, c);
    }

    /**
     * Returns a trie value for a BMP code point (U+0000..U+FFFF), without range
     * checking. Can be used to look up a value for a UTF-16 code unit if other
     * parts of the string processing check for surrogates.
     *
     * @param trie (const UCPTrie *, in) the trie; must have type
     * UCPTRIE_TYPE_FAST
     * @param dataAccess UCPTRIE_16, UCPTRIE_32, or UCPTRIE_8 according to the
     * trie’s value width
     * @param c (UChar32, in) the input code point, must be U+0000..U+FFFF
     * @return The BMP code point's trie value.
     * @draft ICU 63
     */
    template<typename AccessFunc>
    auto
    ucptrie_fast_bmp_get(const UCPTrie * trie, AccessFunc dataAccess, UChar32 c)
        -> decltype(dataAccess(trie, detail::icu::ucptrie_fast_index_(trie, c)))
    {
        return dataAccess(trie, detail::icu::ucptrie_fast_index_(trie, c));
    }

    /**
     * Returns a trie value for a supplementary code point (U+10000..U+10FFFF),
     * without range checking.
     *
     * @param trie (const UCPTrie *, in) the trie; must have type
     * UCPTRIE_TYPE_FAST
     * @param dataAccess UCPTRIE_16, UCPTRIE_32, or UCPTRIE_8 according to the
     * trie’s value width
     * @param c (UChar32, in) the input code point, must be U+10000..U+10FFFF
     * @return The supplementary code point's trie value.
     * @draft ICU 63
     */
    template<typename AccessFunc>
    auto ucptrie_fast_supp_get(
        const UCPTrie * trie, AccessFunc dataAccess, UChar32 c)
        -> decltype(
            dataAccess(trie, detail::icu::ucptrie_small_index_(trie, c)))
    {
        return dataAccess(trie, detail::icu::ucptrie_small_index_(trie, c));
    }

    // Internal constants.
    enum {
        /** The length of the BMP index table. 1024=0x400 */
        ucptrie_bmp_index_length = 0x10000 >> ucptrie_fast_shift,

        ucptrie_small_limit = 0x1000,
        ucptrie_small_index_length = ucptrie_small_limit >> ucptrie_fast_shift,

        /** shift size for getting the index-3 table offset. */
        ucptrie_shift_3 = 4,

        /** shift size for getting the index-2 table offset. */
        ucptrie_shift_2 = 5 + ucptrie_shift_3,

        /** shift size for getting the index-1 table offset. */
        ucptrie_shift_1 = 5 + ucptrie_shift_2,

        /**
         * difference between two shift sizes,
         * for getting an index-2 offset from an index-3 offset. 5=9-4
         */
        ucptrie_shift_2_3 = ucptrie_shift_2 - ucptrie_shift_3,

        /**
         * difference between two shift sizes,
         * for getting an index-1 offset from an index-2 offset. 5=14-9
         */
        ucptrie_shift_1_2 = ucptrie_shift_1 - ucptrie_shift_2,

        /**
         * number of index-1 entries for the bmp. (4)
         * this part of the index-1 table is omitted from the serialized form.
         */
        ucptrie_omitted_bmp_index_1_length = 0x10000 >> ucptrie_shift_1,

        /** number of entries in an index-2 block. 32=0x20 */
        ucptrie_index_2_block_length = 1 << ucptrie_shift_1_2,

        /** mask for getting the lower bits for the in-index-2-block offset. */
        ucptrie_index_2_mask = ucptrie_index_2_block_length - 1,

        /** number of code points per index-2 table entry. 512=0x200 */
        ucptrie_cp_per_index_2_entry = 1 << ucptrie_shift_2,

        /** number of entries in an index-3 block. 32=0x20 */
        ucptrie_index_3_block_length = 1 << ucptrie_shift_2_3,

        /** mask for getting the lower bits for the in-index-3-block offset. */
        ucptrie_index_3_mask = ucptrie_index_3_block_length - 1,

        /** number of entries in a small data block. 16=0x10 */
        ucptrie_small_data_block_length = 1 << ucptrie_shift_3,

        /** mask for getting the lower bits for the in-small-data-block offset.
         */
        ucptrie_small_data_mask = ucptrie_small_data_block_length - 1
    };

    /**
     * Get the least significant bits of a pointer (a memory address).
     * For example, with a mask of 3, the macro gets the 2 least significant
     * bits, which will be 0 if the pointer is 32-bit (4-byte) aligned.
     *
     * ptrdiff_t is the most appropriate integer type to cast to.
     * size_t should work too, since on most (or all?) platforms it has the same
     * width as ptrdiff_t.
     */
    inline ptrdiff_t u_pointer_mask_lsb(const void * ptr, ptrdiff_t mask)
    {
        return (ptrdiff_t)ptr & mask;
    }

    /**
     * Closes a trie and releases associated memory.
     *
     * @param trie the trie
     * @draft ICU 63
     */
    inline void ucptrie_close(UCPTrie * trie) { free(trie); }


    /**
     * \class LocalUCPTriePointer
     * "Smart pointer" class, closes a UCPTrie via ucptrie_close().
     * For most methods see the LocalPointerBase base class.
     *
     * @see LocalPointerBase
     * @see LocalPointer
     * @draft ICU 63
     */
    using LocalUCPTriePointer =
        std::unique_ptr<UCPTrie, decltype(&ucptrie_close)>;

    /**
     * Returns the trie type.
     *
     * @param trie the trie
     * @return the trie type
     * @see ucptrie_openFromBinary
     * @see UCPTRIE_TYPE_ANY
     * @draft ICU 63
     */
    inline UCPTrieType ucptrie_getType(const UCPTrie * trie)
    {
        return (UCPTrieType)trie->type;
    }

    /**
     * Returns the number of bits in a trie data value.
     *
     * @param trie the trie
     * @return the number of bits in a trie data value
     * @see ucptrie_openFromBinary
     * @see UCPTRIE_VALUE_BITS_ANY
     * @draft ICU 63
     */
    inline UCPTrieValueWidth ucptrie_getValueWidth(const UCPTrie * trie)
    {
        return (UCPTrieValueWidth)trie->valueWidth;
    }

    inline uint32_t
    getValue(UCPTrieData data, UCPTrieValueWidth valueWidth, int32_t dataIndex)
    {
        switch (valueWidth) {
        case ucptrie_value_bits_16: return data.ptr16[dataIndex];
        case ucptrie_value_bits_32: return data.ptr32[dataIndex];
        case ucptrie_value_bits_8: return data.ptr8[dataIndex];
        default:
            // Unreachable if the trie is properly initialized.
            return 0xffffffff;
        }
    }

    /**
     * Returns the value for a code point as stored in the trie, with range
     * checking. Returns the trie error value if c is not in the range
     * 0..U+10FFFF.
     *
     * Easier to use than UCPTRIE_FAST_GET() and similar macros but slower.
     * Easier to use because, unlike the macros, this function works on all
     * UCPTrie objects, for all types and value widths.
     *
     * @param trie the trie
     * @param c the code point
     * @return the trie value,
     *         or the trie error value if the code point is not in the range
     * 0..U+10FFFF
     * @draft ICU 63
     */
    inline uint32_t ucptrie_get(const UCPTrie * trie, UChar32 c)
    {
        int32_t dataIndex;
        if ((uint32_t)c <= 0x7f) {
            // linear ASCII
            dataIndex = c;
        } else {
            UChar32 fastMax =
                trie->type == ucptrie_type_fast ? 0xffff : ucptrie_small_max;
            dataIndex = ucptrie_cp_index_(trie, fastMax, c);
        }
        return detail::icu::getValue(
            trie->data, (UCPTrieValueWidth)trie->valueWidth, dataIndex);
    }

    inline int32_t ucptrie_internalSmallIndex(const UCPTrie * trie, UChar32 c)
    {
        int32_t i1 = c >> ucptrie_shift_1;
        if (trie->type == ucptrie_type_fast) {
            BOOST_ASSERT(0xffff < c && c < trie->highStart);
            i1 += ucptrie_bmp_index_length - ucptrie_omitted_bmp_index_1_length;
        } else {
            BOOST_ASSERT(
                (uint32_t)c < (uint32_t)trie->highStart &&
                trie->highStart > ucptrie_small_limit);
            i1 += ucptrie_small_index_length;
        }
        int32_t i3Block = trie->index
                              [(int32_t)trie->index[i1] +
                               ((c >> ucptrie_shift_2) & ucptrie_index_2_mask)];
        int32_t i3 = (c >> ucptrie_shift_3) & ucptrie_index_3_mask;
        int32_t dataBlock;
        if ((i3Block & 0x8000) == 0) {
            // 16-bit indexes
            dataBlock = trie->index[i3Block + i3];
        } else {
            // 18-bit indexes stored in groups of 9 entries per 8 indexes.
            i3Block = (i3Block & 0x7fff) + (i3 & ~7) + (i3 >> 3);
            i3 &= 7;
            dataBlock =
                ((int32_t)trie->index[i3Block++] << (2 + (2 * i3))) & 0x30000;
            dataBlock |= trie->index[i3Block + i3];
        }
        return dataBlock + (c & ucptrie_small_data_mask);
    }

    inline int32_t ucptrie_internalSmallU8Index(
        const UCPTrie * trie, int32_t lt1, uint8_t t2, uint8_t t3)
    {
        UChar32 c = (lt1 << 12) | (t2 << 6) | t3;
        if (c >= trie->highStart) {
            // Possible because the UTF-8 macro compares with shifted12HighStart
            // which may be higher.
            return trie->dataLength - ucptrie_high_value_neg_data_offset;
        }
        return detail::icu::ucptrie_internalSmallIndex(trie, c);
    }

    template<typename CharIter>
    int32_t ucptrie_internalU8PrevIndex(
        const UCPTrie * trie, UChar32 c, CharIter start, CharIter src)
    {
        int32_t i, length;
        // Support 64-bit pointers by avoiding cast of arbitrary difference.
        if ((src - start) <= 7) {
            i = length = (int32_t)(src - start);
        } else {
            i = length = 7;
            start = src - 7;
        }
        c = detail::icu::utf8_prevCharSafeBody(start, 0, &i, c, -1);
        i = length - i; // Number of bytes read backward from src.
        int32_t idx = ucptrie_cp_index_(trie, 0xffff, c);
        return (idx << 3) | i;
    }

}}}}

#endif
