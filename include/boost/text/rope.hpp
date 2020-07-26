// Copyright (C) 2020 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_TEXT_ROPE_HPP
#define BOOST_TEXT_ROPE_HPP

#include <boost/text/grapheme.hpp>
#include <boost/text/grapheme_iterator.hpp>
#include <boost/text/normalize_fwd.hpp>
#include <boost/text/unencoded_rope.hpp>
#include <boost/text/transcode_iterator.hpp>

#include <iterator>


#ifndef BOOST_TEXT_DOXYGEN

#ifdef BOOST_TEXT_TESTING
#define BOOST_TEXT_CHECK_ROPE_NORMALIZATION()                                  \
    do {                                                                       \
        std::string str(rope_.begin(), rope_.end());                           \
        normalize<nf::fcc>(str);                                               \
        BOOST_ASSERT(rope_ == str);                                            \
    } while (false)
#else
#define BOOST_TEXT_CHECK_ROPE_NORMALIZATION()
#endif

#endif

namespace boost { namespace text {

    namespace detail {
        struct const_rope_iterator;
    }

    template<typename Iter>
    struct replace_result;
    struct text;
    struct rope_view;

    /** A mutable sequence of graphemes with copy-on-write semantics.  A rope
        is non-contiguous and is not null-terminated.  The underlying storage
        is an unencoded_rope that is UTF-8-encoded and FCC-normalized. */
    struct rope
    {
        using value_type = grapheme;
        using size_type = std::size_t;
        using iterator = grapheme_iterator<
            utf_8_to_32_iterator<detail::const_rope_iterator>>;
        using const_iterator = iterator;
        using reverse_iterator = stl_interfaces::reverse_iterator<iterator>;
        using const_reverse_iterator = reverse_iterator;

        /** Default ctor. */
        rope() {}

        /** Constructs a text from a pair of iterators. */
        rope(const_iterator first, const_iterator last);

        /** Constructs a rope from a null-terminated string. */
        rope(char const * c_str);

#if defined(__cpp_char8_t)
        /** Constructs a rope from a null-terminated string. */
        rope(char8_t const * c_str);
#endif

        /** Constructs a rope from a string_view. */
        explicit rope(string_view sv);

        /** Constructs a rope from a rope_view. */
        explicit rope(rope_view rv);

        /** Constructs a rope from a string. */
        explicit rope(std::string s);

        /** Constructs a rope from a text. */
        explicit rope(text t);

#ifdef BOOST_TEXT_DOXYGEN

        /** Constructs a rope from a range of char.

            This function only participates in overload resolution if
            `CharRange` models the CharRange concept. */
        template<typename CharRange>
        explicit rope(CharRange const & r);

        /** Constructs a rope from a sequence of char.

            This function only participates in overload resolution if
            `CharIter` models the CharIter concept. */
        template<typename CharIter, typename Sentinel>
        rope(CharIter first, Sentinel last);

#else

        template<typename CharRange>
        explicit rope(
            CharRange const & r, detail::rng_alg_ret_t<int *, CharRange> = 0);

        template<typename CharIter, typename Sentinel>
        rope(
            CharIter first,
            Sentinel last,
            detail::char_iter_ret_t<void *, CharIter> = 0);

#endif

        /** Assignment from a null-terminated string. */
        rope & operator=(char const * c_str);

#if defined(__cpp_char8_t)
        /** Assignment from a null-terminated string. */
        rope & operator=(char8_t const * c_str);
#endif

        /** Assignment from a rope_view. */
        rope & operator=(rope_view rv);

        /** Assignment from a string_view. */
        rope & operator=(string_view sv);

        /** Move-assignment from a string. */
        rope & operator=(std::string s);

        /** Move-assignment from a text. */
        rope & operator=(text t);

#ifdef BOOST_TEXT_DOXYGEN

        /** Assignment from a range of char.

            This function only participates in overload resolution if
            `CharRange` models the CharRange concept. */
        template<typename CharRange>
        rope & operator=(CharRange const & r);

#else

        template<typename CharRange>
        auto operator=(CharRange const & r)
            -> detail::rng_alg_ret_t<rope &, CharRange>;

#endif

        const_iterator begin() const noexcept;
        const_iterator end() const noexcept;

        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;

        const_reverse_iterator rbegin() const noexcept;
        const_reverse_iterator rend() const noexcept;

        const_reverse_iterator crbegin() const noexcept;
        const_reverse_iterator crend() const noexcept;

        /** Returns true if begin() == end(), false otherwise. */
        bool empty() const noexcept;

        /** Returns the number of bytes controlled by *this, not including the
            null terminator. */
        size_type storage_bytes() const noexcept;

        /** Returns the number of graphemes in *this.  This operation is
            O(n). */
        size_type distance() const noexcept;

        /** Returns the maximum size in bytes a rope can have. */
        size_type max_bytes() const noexcept { return PTRDIFF_MAX; }

        /** Returns true if *this and rhs contain the same root node pointer.
            This is useful when you want to check for equality between two
            unencoded_ropes that are likely to have originated from the same
            initial unencoded_rope, and may have since been mutated. */
        bool equal_root(rope rhs) const noexcept;

        /** Clear. */
        void clear() noexcept;

        /** Inserts the sequence of char from c_str into *this starting at
            position at. */
        replace_result<const_iterator>
        insert(const_iterator at, char const * c_str);

#if defined(__cpp_char8_t)
        /** Inserts the sequence of char from c_str into *this starting at
            position at. */
        replace_result<const_iterator>
        insert(const_iterator at, char8_t const * c_str);
#endif

        /** Inserts the sequence of char from rv into *this starting at position
            at. */
        replace_result<const_iterator> insert(const_iterator at, rope_view rv);

        /** Inserts s into *this starting at position at. */
        replace_result<const_iterator>
        insert(const_iterator at, std::string && s);

        /** Inserts the sequence of char from sv into *this starting at position
            at. */
        replace_result<const_iterator>
        insert(const_iterator at, string_view sv);

#ifdef BOOST_TEXT_DOXYGEN

        /** Inserts the char range r into *this starting at position at.

            This function only participates in overload resolution if
            `CharRange` models the CharRange concept. */
        template<typename CharRange>
        replace_result<const_iterator>
        insert(const_iterator at, CharRange const & r);

        /** Inserts the char sequence [first, last) into *this starting at
            position at.

            This function only participates in overload resolution if
            `CharIter` models the CharIter concept. */
        template<typename CharIter, typename Sentinel>
        replace_result<const_iterator>
        insert(const_iterator at, CharIter first, Sentinel last);

#else

        template<typename CharRange>
        auto insert(const_iterator at, CharRange const & r)
            -> detail::rng_alg_ret_t<replace_result<const_iterator>, CharRange>;

        template<typename CharIter, typename Sentinel>
        auto insert(const_iterator at, CharIter first, Sentinel last)
            -> detail::
                char_iter_ret_t<replace_result<const_iterator>, CharIter>;

#endif

        /** Inserts the sequence [first, last) into *this starting at position
            at. */
        replace_result<const_iterator>
        insert(const_iterator at, const_iterator first, const_iterator last);

        /** Inserts the grapheme g into *this at position at. */
        replace_result<const_iterator>
        insert(const_iterator at, grapheme const & g);

        /** Inserts the grapheme g into *this at position at. */
        template<typename CPIter>
        replace_result<const_iterator>
        insert(const_iterator at, grapheme_ref<CPIter> g);

        /** Erases the portion of *this delimited by rv.

            \pre !std::less(rv.begin().base().base(), begin().base().base()) &&
            !std::less(end().base().base(), rv.end().base().base()) */
        replace_result<const_iterator> erase(rope_view rv);

        /** Erases the portion of *this delimited by [first, last).

            \pre first <= last */
        replace_result<const_iterator>
        erase(const_iterator first, const_iterator last);

        /** Replaces the portion of *this delimited by old_substr with the
            sequence of char from new_substr.

            \pre !std::less(old_substr.begin().base().base(),
            begin().base().base()) && !std::less(end().base().base(),
            old_substr.end().base().base()) */
        replace_result<const_iterator>
        replace(rope_view old_substr, rope_view new_substr);

        /** Replaves the  portion of *this delimited by old_substr with the
            sequence of char from new_substr.

            \pre !std::less(old_substr.begin().base().base(),
            begin().base().base()) && !std::less(end().base().base(),
            old_substr.end().base().base()) */
        replace_result<const_iterator>
        replace(rope_view old_substr, string_view new_substr);

#ifdef BOOST_TEXT_DOXYGEN

        /** Replaces the portion of *this delimited by old_substr with the
            char range r.

            This function only participates in overload resolution if
            `CharRange` models the CharRange concept.

            \pre !std::less(old_substr.begin().base().base(),
            begin().base().base()) && !std::less(end().base().base(),
            old_substr.end().base().base()) */
        template<typename CharRange>
        replace_result<const_iterator>
        replace(rope_view old_substr, CharRange const & r);

        /** Replaces the portion of *this delimited by old_substr with the
            char sequence [first, last).

            This function only participates in overload resolution if
            `CharIter` models the CharIter concept.

            \pre !std::less(old_substr.begin().base().base(),
            begin().base().base()) && !std::less(end().base().base(),
            old_substr.end().base().base()) */
        template<typename CharIter, typename Sentinel>
        replace_result<const_iterator>
        replace(rope_view old_substr, CharIter first, Sentinel last);

#else

        template<typename CharRange>
        auto replace(rope_view old_substr, CharRange const & r)
            -> detail::rng_alg_ret_t<replace_result<const_iterator>, CharRange>;

        template<typename CharIter, typename Sentinel>
        auto replace(rope_view old_substr, CharIter first, Sentinel last)
            -> detail::
                char_iter_ret_t<replace_result<const_iterator>, CharIter>;

#endif

        /** Replaces the portion of *this delimited by old_substr with the
            sequence of char from c_str.

            \pre !std::less(old_substr.begin().base().base(),
            begin().base().base()) && !std::less(end().base().base(),
            old_substr.end().base().base()) */
        replace_result<const_iterator>
        replace(rope_view old_substr, char const * c_str);

#if defined(__cpp_char8_t)
        /** Replaces the portion of *this delimited by old_substr with the
            sequence of char from c_str.

            \pre !std::less(old_substr.begin().base().base(),
            begin().base().base()) && !std::less(end().base().base(),
            old_substr.end().base().base()) */
        replace_result<const_iterator>
        replace(rope_view old_substr, char8_t const * c_str);
#endif

        /** Replaces the portion of *this delimited by old_substr with the
            sequence [first, last).

            \pre !std::less(old_substr.begin().base().base(),
            begin().base().base()) && !std::less(end().base().base(),
            old_substr.end().base().base()) */
        replace_result<const_iterator> replace(
            rope_view old_substr, const_iterator first, const_iterator last);

        /** Swaps *this with rhs. */
        void swap(rope & rhs) noexcept;

        /** Removes and returns the underlying unencoded_rope from *this. */
        unencoded_rope extract() && noexcept;

        /** Replaces the underlying unencoded_rope in *this.

            \pre ur is normalized FCC. */
        void replace(unencoded_rope && ur) noexcept;

        /** Appends c_str to *this. */
        rope & operator+=(char const * c_str);

#if defined(__cpp_char8_t)
        /** Appends c_str to *this. */
        rope & operator+=(char8_t const * c_str);
#endif

        /** Appends rv to *this. */
        rope & operator+=(rope_view rv);

        /** Appends tv to *this. */
        rope & operator+=(string_view sv);

#ifdef BOOST_TEXT_DOXYGEN

        /** Appends the char range r to *this.

            This function only participates in overload resolution if
            `CharRange` models the CharRange concept. */
        template<typename CharRange>
        rope & operator+=(CharRange const & r);

#else

        template<typename CharRange>
        auto operator+=(CharRange const & r)
            -> detail::rng_alg_ret_t<rope &, CharRange>;

#endif

        /** Stream inserter; performs formatted output, in UTF-8 encoding. */
        friend std::ostream & operator<<(std::ostream & os, rope const & r)
        {
            if (os.good()) {
                auto const size = r.distance();
                detail::pad_width_before(os, size);
                os << r.rope_;
                if (os.good())
                    detail::pad_width_after(os, size);
            }
            return os;
        }

#ifndef BOOST_TEXT_DOXYGEN

    private:
        static const_iterator make_iter(
            detail::const_rope_iterator first,
            detail::const_rope_iterator it,
            detail::const_rope_iterator last) noexcept;

        using utf32_iter = utf_8_to_32_iterator<detail::const_rope_iterator>;

        replace_result<const_iterator>
        mutation_result(std::size_t first_offset, std::size_t last_offset);

        replace_result<const_iterator>
        normalize_endpoints(std::size_t first_, std::size_t last_);

        replace_result<const_iterator> insert_impl(
            iterator at,
            std::string str,
            insertion_normalization insertion_norm);
        replace_result<const_iterator> replace_impl(
            rope_view old_substr,
            std::string str,
            insertion_normalization insertion_norm);

        template<typename CPIter>
        struct insert_grapheme_ref_impl;

        unencoded_rope rope_;

        friend struct ::boost::text::rope_view;

        template<typename CPIter>
        friend struct insert_grapheme_ref_impl;

#endif // Doxygen
    };

    inline rope::iterator begin(rope const & t) noexcept { return t.begin(); }
    inline rope::iterator end(rope const & t) noexcept { return t.end(); }
    inline rope::iterator cbegin(rope const & t) noexcept { return t.cbegin(); }
    inline rope::iterator cend(rope const & t) noexcept { return t.cend(); }

    inline rope::reverse_iterator rbegin(rope const & t) noexcept
    {
        return t.rbegin();
    }
    inline rope::reverse_iterator rend(rope const & t) noexcept
    {
        return t.rend();
    }
    inline rope::reverse_iterator crbegin(rope const & t) noexcept
    {
        return t.crbegin();
    }
    inline rope::reverse_iterator crend(rope const & t) noexcept
    {
        return t.crend();
    }

}}

#include <boost/text/text.hpp>
#include <boost/text/rope_view.hpp>
#include <boost/text/normalize_string.hpp>
#include <boost/text/normalize_algorithm.hpp>
#include <boost/text/detail/rope_iterator.hpp>

#ifndef BOOST_TEXT_DOXYGEN

namespace boost { namespace text {

    inline rope::rope(const_iterator first, const_iterator last) :
        rope(rope_view(first, last))
    {}

    inline rope::rope(char const * c_str) : rope_(text(c_str).extract()) {}

#if defined(__cpp_char8_t)
    inline rope::rope(char8_t const * c_str) : rope((char const *)c_str) {}
#endif

    inline rope::rope(rope_view rv) :
        rope_(rv.begin().base().base(), rv.end().base().base())
    {}

    inline rope::rope(string_view sv) : rope_(text(sv).extract()) {}

    inline rope::rope(std::string s) : rope_(text(std::move(s)).extract()) {}

    inline rope::rope(text t) : rope_(std::move(t).extract()) {}

    template<typename CharRange>
    rope::rope(CharRange const & r, detail::rng_alg_ret_t<int *, CharRange>) :
        rope_(text(r).extract())
    {}

    template<typename CharIter, typename Sentinel>
    rope::rope(
        CharIter first,
        Sentinel last,
        detail::char_iter_ret_t<void *, CharIter>) :
        rope_(text(first, last).extract())
    {}

    inline rope & rope::operator=(char const * c_str)
    {
        rope temp(c_str);
        swap(temp);
        return *this;
    }

#if defined(__cpp_char8_t)
    inline rope & rope::operator=(char8_t const * c_str)
    {
        return *this = (char const *)c_str;
    }
#endif

    inline rope & rope::operator=(rope_view rv)
    {
        rope temp(rv);
        swap(temp);
        return *this;
    }

    inline rope & rope::operator=(string_view sv)
    {
        rope temp(sv);
        swap(temp);
        return *this;
    }

    inline rope & rope::operator=(std::string s)
    {
        rope temp(std::move(s));
        swap(temp);
        return *this;
    }

    inline rope & rope::operator=(text t)
    {
        rope temp(std::move(t));
        swap(temp);
        return *this;
    }

    template<typename CharRange>
    auto rope::operator=(CharRange const & r)
        -> detail::rng_alg_ret_t<rope &, CharRange>
    {
        rope temp(r);
        swap(temp);
        return *this;
    }

    inline rope::const_iterator rope::begin() const noexcept
    {
        return make_iter(rope_.begin(), rope_.begin(), rope_.end());
    }
    inline rope::const_iterator rope::end() const noexcept
    {
        return make_iter(rope_.begin(), rope_.end(), rope_.end());
    }

    inline rope::const_iterator rope::cbegin() const noexcept
    {
        return begin();
    }
    inline rope::const_iterator rope::cend() const noexcept { return end(); }

    inline rope::const_reverse_iterator rope::rbegin() const noexcept
    {
        return reverse_iterator(end());
    }
    inline rope::const_reverse_iterator rope::rend() const noexcept
    {
        return reverse_iterator(begin());
    }

    inline rope::const_reverse_iterator rope::crbegin() const noexcept
    {
        return rbegin();
    }
    inline rope::const_reverse_iterator rope::crend() const noexcept
    {
        return rend();
    }

    inline bool rope::empty() const noexcept { return rope_.empty(); }

    inline rope_view::size_type rope::storage_bytes() const noexcept
    {
        return rope_.size();
    }

    inline rope_view::size_type rope::distance() const noexcept
    {
        return std::distance(begin(), end());
    }

    inline bool rope::equal_root(rope rhs) const noexcept
    {
        return rope_.equal_root(rhs.rope_);
    }

    inline void rope::clear() noexcept { rope_.clear(); }

    inline replace_result<rope::const_iterator>
    rope::insert(const_iterator at, char const * c_str)
    {
        return insert_impl(at, std::string(c_str), insertion_not_normalized);
    }

#if defined(__cpp_char8_t)
    inline replace_result<rope::const_iterator>
    rope::insert(const_iterator at, char8_t const * c_str)
    {
        return insert_impl(
            at, std::string((char const *)c_str), insertion_not_normalized);
    }
#endif

    inline replace_result<rope::const_iterator>
    rope::insert(const_iterator at, rope_view rv)
    {
        // TODO: It would be better if we shared nodes with copied nodes from
        // rv.  Same for unencoded_rope probably.
        return insert_impl(
            at,
            std::string(rv.begin().base().base(), rv.end().base().base()),
            insertion_normalized);
    }

    inline replace_result<rope::const_iterator>
    rope::insert(const_iterator at, std::string && s)
    {
        return insert_impl(at, std::move(s), insertion_not_normalized);
    }

    inline replace_result<rope::const_iterator>
    rope::insert(const_iterator at, string_view sv)
    {
        return insert_impl(at, std::string(sv), insertion_not_normalized);
    }

    template<typename CharRange>
    auto rope::insert(const_iterator at, CharRange const & r)
        -> detail::rng_alg_ret_t<replace_result<const_iterator>, CharRange>
    {
        return insert_impl(
            at,
            std::string(detail::make_string(r.begin(), r.end())),
            insertion_not_normalized);
    }

    template<typename CharIter, typename Sentinel>
    auto rope::insert(const_iterator at, CharIter first, Sentinel last)
        -> detail::char_iter_ret_t<replace_result<const_iterator>, CharIter>
    {
        return insert_impl(
            at, detail::make_string(first, last), insertion_not_normalized);
    }

    inline replace_result<rope::const_iterator>
    rope::insert(const_iterator at, const_iterator first, const_iterator last)
    {
        return insert(at, rope_view(first, last));
    }

    inline replace_result<rope::const_iterator>
    rope::insert(const_iterator at, grapheme const & g)
    {
        return insert(at, grapheme_ref<grapheme::const_iterator>(g));
    }

    template<typename CPIter>
    replace_result<rope::const_iterator>
    rope::insert(const_iterator at, grapheme_ref<CPIter> g)
    {
        return insert_grapheme_ref_impl<CPIter>::call(*this, at, g);
    }

    inline replace_result<rope::const_iterator> rope::erase(rope_view rv)
    {
        using view = detail::stable_cps_result_t<utf32_iter>;

        rope_view const this_rv(*this);

        auto first_offset =
            rv.begin().base().base() - this_rv.begin().base().base();
        auto last_offset =
            rv.end().base().base() - this_rv.begin().base().base();
        rope_.erase(rope_.begin() + first_offset, rope_.begin() + last_offset);

        utf32_iter const at(
            rope_.begin(), rope_.begin() + first_offset, rope_.end());
        view const unstable{
            detail::last_stable_cp<nf::fcc>(begin().base(), at),
            detail::first_stable_cp<nf::fcc>(at, end().base())};
        std::string normalized;
        boost::text::normalize_append<nf::fcc>(unstable, normalized);

        view const unstable_before_at{unstable.begin(), at};
        view const unstable_after_at{at, unstable.end()};

        auto const normalized_cps = boost::text::as_utf32(normalized);

        auto const prefix_mismatch = std::mismatch(
            unstable_before_at.begin(),
            unstable_before_at.end(),
            normalized_cps.begin(),
            normalized_cps.end());
        auto const after_at_last =
            std::make_reverse_iterator(unstable_after_at.begin());
        auto const suffix_mismatch = std::mismatch(
            std::make_reverse_iterator(unstable_after_at.end()),
            after_at_last,
            std::make_reverse_iterator(normalized_cps.end()),
            std::make_reverse_iterator(normalized_cps.begin()));

        if (prefix_mismatch.first == unstable_before_at.end() &&
            suffix_mismatch.first != after_at_last) {
            return mutation_result(first_offset, first_offset);
        }

        last_offset = first_offset + (suffix_mismatch.first.base().base() -
                                      unstable_after_at.begin().base());
        first_offset -=
            unstable_before_at.end().base() - prefix_mismatch.first.base();
        rope_.replace(
            unencoded_rope_view(
                rope_,
                unstable.begin().base() - rope_.begin(),
                unstable.end().base() - rope_.begin()),
            std::move(normalized));

        return mutation_result(first_offset, last_offset);
    }

    inline replace_result<rope::const_iterator>
    rope::erase(const_iterator first, const_iterator last)
    {
        return erase(rope_view(first, last));
    }

    inline replace_result<rope::const_iterator>
    rope::replace(rope_view old_substr, rope_view new_substr)
    {
        return replace_impl(
            old_substr,
            std::string(
                new_substr.begin().base().base(),
                new_substr.end().base().base()),
            insertion_normalized);
    }

    inline replace_result<rope::const_iterator>
    rope::replace(rope_view old_substr, string_view new_substr)
    {
        return replace_impl(
            old_substr, std::string(new_substr), insertion_not_normalized);
    }

    template<typename CharRange>
    auto rope::replace(rope_view old_substr, CharRange const & r) -> detail::
        rng_alg_ret_t<replace_result<rope::const_iterator>, CharRange>
    {
        return replace(old_substr, std::begin(r), std::end(r));
    }

    inline replace_result<rope::const_iterator>
    rope::replace(rope_view old_substr, char const * str)
    {
        return replace(old_substr, string_view(str));
    }

#if defined(__cpp_char8_t)
    inline replace_result<rope::const_iterator>
    rope::replace(rope_view old_substr, char8_t const * str)
    {
        return replace(old_substr, (char const *)str);
    }
#endif

    template<typename CharIter, typename Sentinel>
    auto rope::replace(rope_view old_substr, CharIter first, Sentinel last)
        -> detail::
            char_iter_ret_t<replace_result<rope::const_iterator>, CharIter>
    {
        return replace_impl(
            old_substr,
            detail::make_string(first, last),
            insertion_not_normalized);
    }

    inline replace_result<rope::const_iterator> rope::replace(
        rope_view old_substr, const_iterator first, const_iterator last)
    {
        return replace(old_substr, rope_view(first, last));
    }

    inline void rope::swap(rope & rhs) noexcept { rope_.swap(rhs.rope_); }

    inline unencoded_rope rope::extract() && noexcept
    {
        return std::move(rope_);
    }

    inline void rope::replace(unencoded_rope && ur) noexcept
    {
        rope_ = std::move(ur);
    }

    inline rope & rope::operator+=(char const * c_str)
    {
        return *this += string_view(c_str);
    }

#if defined(__cpp_char8_t)
    inline rope & rope::operator+=(char8_t const * c_str)
    {
        return *this += string_view((char const *)c_str);
    }
#endif

    inline rope & rope::operator+=(rope_view rv)
    {
        insert(end(), rv);
        return *this;
    }

    inline rope & rope::operator+=(string_view sv)
    {
        insert(end(), sv);
        return *this;
    }

    template<typename CharRange>
    auto rope::operator+=(CharRange const & r)
        -> detail::rng_alg_ret_t<rope &, CharRange>
    {
        insert(end(), r);
        return *this;
    }

    inline rope::const_iterator rope::make_iter(
        detail::const_rope_iterator first,
        detail::const_rope_iterator it,
        detail::const_rope_iterator last) noexcept
    {
        return const_iterator{
            utf_8_to_32_iterator<detail::const_rope_iterator>{
                first, first, last},
            utf_8_to_32_iterator<detail::const_rope_iterator>{first, it, last},
            utf_8_to_32_iterator<detail::const_rope_iterator>{
                first, last, last}};
    }

    inline replace_result<rope::const_iterator>
    rope::mutation_result(std::size_t first_offset, std::size_t last_offset)
    {
        auto const rope_first = rope_.begin();
        auto const rope_lo = rope_first + first_offset;
        auto const rope_hi = rope_first + last_offset;
        auto const rope_last = rope_.end();

        // The insertion that just happened might be merged into the CP or
        // grapheme ending at the offset of the inserted char(s); if so, back
        // up and return an iterator to that.
        auto lo_cp_it = utf32_iter(rope_first, rope_lo, rope_last);
        auto const lo_grapheme_it = boost::text::prev_grapheme_break(
            begin().base(), lo_cp_it, end().base());

        // The insertion that just happened might be merged into the CP or
        // grapheme starting at the offset of the inserted char(s); if so,
        // move up and return an iterator to that.
        auto hi_cp_it = utf32_iter(rope_first, rope_hi, rope_last);
        auto hi_grapheme_it = hi_cp_it;
        if (!boost::text::at_grapheme_break(
                begin().base(), hi_cp_it, end().base())) {
            hi_grapheme_it =
                boost::text::next_grapheme_break(hi_cp_it, end().base());
        }

        return {
            make_iter(
                begin().base().base(),
                lo_grapheme_it.base(),
                end().base().base()),
            make_iter(
                begin().base().base(),
                hi_grapheme_it.base(),
                end().base().base())};
    }

    inline replace_result<rope::const_iterator>
    rope::normalize_endpoints(std::size_t first_offset, std::size_t last_offset)
    {
        using view = detail::stable_cps_result_t<utf32_iter>;

        std::string normalized;

        {
            utf32_iter const first(
                rope_.begin(), rope_.begin() + first_offset, rope_.end());
            utf32_iter const last(
                rope_.begin(), rope_.begin() + last_offset, rope_.end());
            view const unstable{
                detail::last_stable_cp<nf::fcc>(begin().base(), first),
                detail::first_stable_cp<nf::fcc>(first, last)};
            boost::text::normalize_append<nf::fcc>(unstable, normalized);

            auto const normalized_cps = boost::text::as_utf32(normalized);

            view const unstable_before_insertion{unstable.begin(), first};
            auto const mismatch = std::mismatch(
                unstable_before_insertion.begin(),
                unstable_before_insertion.end(),
                normalized_cps.begin(),
                normalized_cps.end());
            if (mismatch.first != unstable_before_insertion.end()) {
                first_offset -= unstable_before_insertion.end().base() -
                                mismatch.first.base();
                rope_.replace(
                    unencoded_rope_view(
                        rope_,
                        unstable.begin().base() - rope_.begin(),
                        unstable.end().base() - rope_.begin()),
                    std::move(normalized));
            }
        }

        normalized.clear();

        {
            utf32_iter const first(
                rope_.begin(), rope_.begin() + first_offset, rope_.end());
            utf32_iter const last(
                rope_.begin(), rope_.begin() + last_offset, rope_.end());
            view const unstable{
                detail::last_stable_cp<nf::fcc>(first, last),
                detail::first_stable_cp<nf::fcc>(last, end().base())};
            boost::text::normalize_append<nf::fcc>(unstable, normalized);

            auto const normalized_cps = boost::text::as_utf32(normalized);

            view const unstable_after_insertion{last, unstable.end()};
            auto const after_insertion_last =
                std::make_reverse_iterator(unstable_after_insertion.begin());
            auto const mismatch = std::mismatch(
                std::make_reverse_iterator(unstable_after_insertion.end()),
                after_insertion_last,
                std::make_reverse_iterator(normalized_cps.end()),
                std::make_reverse_iterator(normalized_cps.begin()));
            if (mismatch.first != after_insertion_last) {
                last_offset += mismatch.first.base().base() -
                               unstable_after_insertion.begin().base();
                rope_.replace(
                    unencoded_rope_view(
                        rope_,
                        unstable.begin().base() - rope_.begin(),
                        unstable.end().base() - rope_.begin()),
                    std::move(normalized));
            }
        }

        return mutation_result(first_offset, last_offset);
    }

    inline replace_result<rope::const_iterator> rope::insert_impl(
        iterator at, std::string str, insertion_normalization insertion_norm)
    {
        if (insertion_norm != insertion_normalized)
            boost::text::normalize<nf::fcc>(str);

        auto const rope_at = at.base().base();
        auto const at_offset = rope_at - rope_.begin();

        auto const insertion_size = str.size();
        rope_.insert(rope_at, std::move(str));

        return normalize_endpoints(at_offset, at_offset + insertion_size);
    }

    replace_result<rope::const_iterator> rope::replace_impl(
        rope_view old_substr,
        std::string str,
        insertion_normalization insertion_norm)
    {
        if (insertion_norm != insertion_normalized)
            boost::text::normalize<nf::fcc>(str);

        rope_view const this_rv(*this);
        unencoded_rope_view const this_urv(rope_);
        unencoded_rope_view const replaced(
            rope_,
            old_substr.begin().base().base() - this_rv.begin().base().base(),
            old_substr.end().base().base() - this_rv.begin().base().base());
        auto const replacement_offset = replaced.begin() - this_urv.begin();

        auto const insertion_size = str.size();
        rope_.replace(replaced, std::move(str));

        return normalize_endpoints(
            replacement_offset, replacement_offset + insertion_size);
    }

    template<typename CPIter>
    struct rope::insert_grapheme_ref_impl
    {
        static auto
        call(rope & r, rope::const_iterator at, grapheme_ref<CPIter> g)
        {
            if (g.empty())
                return replace_result<const_iterator>{at, at};

            std::string s;
            boost::text::transcode_to_utf8(
                g.begin(), g.end(), std::inserter(s, s.end()));
            return r.insert_impl(at, std::move(s), insertion_normalized);
        }
    };

    template<typename Sentinel, typename ErrorHandler>
    struct rope::insert_grapheme_ref_impl<
        utf_8_to_32_iterator<char const *, Sentinel, ErrorHandler>>
    {
        static auto call(
            rope & r,
            rope::const_iterator at,
            grapheme_ref<
                utf_8_to_32_iterator<char const *, Sentinel, ErrorHandler>> g)
        {
            return r.insert_impl(
                at,
                std::string(g.begin().base(), g.end().base()),
                insertion_normalized);
        }
    };

    template<typename Sentinel, typename ErrorHandler>
    struct rope::insert_grapheme_ref_impl<
        utf_8_to_32_iterator<char *, Sentinel, ErrorHandler>>
    {
        static auto call(
            rope & r,
            rope::const_iterator at,
            grapheme_ref<utf_8_to_32_iterator<char *, Sentinel, ErrorHandler>>
                g)
        {
            return r.insert_impl(
                at,
                std::string(g.begin().base(), g.end().base()),
                insertion_normalized);
        }
    };

}}

#endif

namespace boost { namespace text {

    inline bool operator==(text const & lhs, rope_view rhs) noexcept
    {
        return algorithm::equal(
            lhs.begin().base().base(),
            lhs.end().base().base(),
            rhs.begin().base().base(),
            rhs.end().base().base());
    }
    inline bool operator==(rope_view lhs, text const & rhs) noexcept
    {
        return rhs == lhs;
    }

    inline bool operator!=(text const & lhs, rope_view rhs) noexcept
    {
        return !(lhs == rhs);
    }
    inline bool operator!=(rope_view lhs, text const & rhs) noexcept
    {
        return !(lhs == rhs);
    }

    inline bool operator==(text const & lhs, rope rhs) noexcept
    {
        return algorithm::equal(
            lhs.begin().base().base(),
            lhs.end().base().base(),
            rhs.begin().base().base(),
            rhs.end().base().base());
    }
    inline bool operator==(rope lhs, text const & rhs) noexcept
    {
        return rhs == lhs;
    }

    inline bool operator!=(text const & lhs, rope rhs) noexcept
    {
        return !(lhs == rhs);
    }
    inline bool operator!=(rope lhs, text const & rhs) noexcept
    {
        return !(lhs == rhs);
    }

    inline bool operator==(rope const & lhs, rope_view rhs) noexcept
    {
        return algorithm::equal(
            lhs.begin().base().base(),
            lhs.end().base().base(),
            rhs.begin().base().base(),
            rhs.end().base().base());
    }
    inline bool operator==(rope_view lhs, rope const & rhs) noexcept
    {
        return rhs == lhs;
    }

    inline bool operator!=(rope const & lhs, rope_view rhs) noexcept
    {
        return !(lhs == rhs);
    }
    inline bool operator!=(rope_view lhs, rope const & rhs) noexcept
    {
        return !(lhs == rhs);
    }

    inline bool operator==(rope const & lhs, rope const & rhs) noexcept
    {
        return algorithm::equal(
            lhs.begin().base().base(),
            lhs.end().base().base(),
            rhs.begin().base().base(),
            rhs.end().base().base());
    }

    inline bool operator!=(rope const & lhs, rope const & rhs) noexcept
    {
        return !(lhs == rhs);
    }

    /** Creates a new rope object that is the concatenation of r and c_str. */
    inline rope operator+(rope t, char const * c_str) { return t += c_str; }

    /** Creates a new rope object that is the concatenation of c_str and r. */
    inline rope operator+(char const * c_str, rope const & r)
    {
        return rope(c_str) += r;
    }

#if defined(__cpp_char8_t)
    /** Creates a new rope object that is the concatenation of r and c_str. */
    inline rope operator+(rope t, char8_t const * c_str)
    {
        return t += (char const *)c_str;
    }

    /** Creates a new rope object that is the concatenation of c_str and r. */
    inline rope operator+(char8_t const * c_str, rope const & r)
    {
        return rope((char const *)c_str) += r;
    }
#endif

    /** Creates a new rope object that is the concatenation of r and r2. */
    inline rope operator+(rope r, rope const & r2) { return r += r2; }

    /** Creates a new rope object that is the concatenation of r and rv. */
    inline rope operator+(rope r, rope_view rv) { return r += rv; }

    /** Creates a new rope object that is the concatenation of rv and r. */
    inline rope operator+(rope_view rv, rope const & r)
    {
        return rope(rv) += r;
    }

#ifdef BOOST_TEXT_DOXYGEN

    /** Creates a new rope object that is the concatenation of r and r2.

        This function only participates in overload resolution if `CharRange`
        models the CharRange concept. */
    template<typename CharRange>
    rope operator+(rope r, CharRange const & r2);

    /** Creates a new rope object that is the concatenation of r and r2.

        This function only participates in overload resolution if `CharRange`
        models the CharRange concept. */
    template<typename CharRange>
    rope operator+(CharRange const & r, rope const & r2);

#else

    template<typename CharRange>
    auto operator+(rope r, CharRange const & r2)
        -> detail::rng_alg_ret_t<rope, CharRange>
    {
        return r += r2;
    }

    template<typename CharRange>
    auto operator+(CharRange const & r, rope const & r2)
        -> detail::rng_alg_ret_t<rope, CharRange>
    {
        return rope(r) += r2;
    }

#endif

    /** Creates a new rope object that is the concatenation of t and rv. */
    inline text & operator+=(text & t, rope_view rv)
    {
        t.insert(t.end(), rv.begin().base().base(), rv.end().base().base());
        return t;
    }

    /** Creates a new rope object that is the concatenation of t and rv. */
    inline rope operator+(text t, rope_view rv)
    {
        return rope(std::move(t)) += rv;
    }

    /** Creates a new rope object that is the concatenation of r and t. */
    inline rope operator+(rope_view rv, text const & t)
    {
        return rope(rv) += t;
    }

    /** Creates a new rope object that is the concatenation of t and r. */
    inline text & operator+=(text & t, rope const & r)
    {
        t.insert(t.end(), r.begin().base().base(), r.end().base().base());
        return t;
    }

    /** Creates a new rope object that is the concatenation of t and r. */
    inline rope operator+(text t, rope const & r)
    {
        return rope(std::move(t)) += r;
    }

    /** Creates a new rope object that is the concatenation of r and t. */
    inline rope operator+(rope r, text const & t) { return r += t; }


    inline replace_result<text::iterator>
    text::insert(iterator at, rope_view rv)
    {
        return insert_impl(
            at,
            rv.begin().base().base(),
            rv.end().base().base(),
            insertion_normalized);
    }

    inline replace_result<text::iterator>
    text::replace(text_view old_substr, rope_view new_substr)
    {
        return replace_impl(
            old_substr,
            new_substr.begin().base().base(),
            new_substr.end().base().base(),
            insertion_normalized);
    }

}}

#ifndef BOOST_TEXT_DOXYGEN

namespace std {
    template<>
    struct hash<boost::text::rope>
    {
        using argument_type = boost::text::rope;
        using result_type = std::size_t;
        result_type operator()(argument_type const & r) const noexcept
        {
            return boost::text::detail::hash_grapheme_range(r);
        }
    };
}

#endif

#endif
