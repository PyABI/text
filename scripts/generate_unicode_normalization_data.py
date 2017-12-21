#!/usr/bin/env python

ccc_file_form = decls = '''\
// Warning! This file is autogenerated.
#include <boost/text/normalization_data.hpp>

#include <boost/container/static_vector.hpp>

#include <unordered_map>


namespace boost {{ namespace text {{

static const std::unordered_map<uint32_t, int> g_ccc_map = {{
{0}
}};

int ccc(uint32_t cp) noexcept
{{
    auto const it = g_ccc_map.find(cp);
    if (it == g_ccc_map.end())
        return 0;
    return it->second;
}}

}}}}
'''

canonical_file_form = decls = '''\
// Warning! This file is autogenerated.
#include <boost/text/normalization_data.hpp>

#include <boost/container/static_vector.hpp>

#include <array>
#include <unordered_map>


namespace boost {{ namespace text {{

static const std::unordered_map<uint32_t, canonical_decomposition>
g_canonical_decomposition_map = {{
{0}
}};

canonical_decomposition canonical_decompose(uint32_t cp) noexcept
{{
    // Hangul decomposition as described in Unicode 10.0 Section 3.12.
    if (0xAC00 <= cp && cp <= 0xD7A3) {{
        uint32_t const SBase = 0xAC00;
        uint32_t const LBase = 0x1100;
        uint32_t const VBase = 0x1161;
        uint32_t const TBase = 0x11A7;
        //uint32_t const LCount = 19;
        uint32_t const VCount = 21;
        uint32_t const TCount = 28;
        uint32_t const NCount = VCount * TCount; // 588
        //uint32_t const SCount = LCount * NCount; // 11172

        auto const SIndex = cp - SBase;

        auto const LIndex = SIndex / NCount;
        auto const VIndex = (SIndex % NCount) / TCount;
        auto const TIndex = SIndex % TCount;
        auto const LPart = LBase + LIndex;
        auto const VPart = VBase + VIndex;
        if (TIndex == 0) {{
            return canonical_decomposition{{{{{{LPart, VPart}}}}, 2}};
        }} else {{
            auto const TPart = TBase + TIndex;
            return canonical_decomposition{{{{{{LPart, VPart, TPart}}}}, 3}};
        }}
    }}

    auto const it = g_canonical_decomposition_map.find(cp);
    if (it == g_canonical_decomposition_map.end())
        return canonical_decomposition{{{{{{cp}}}}, 1}};
    return it->second;
}}

}}}}
'''

compatible_file_form = decls = '''\
// Warning! This file is autogenerated.
#include <boost/text/normalization_data.hpp>

#include <boost/container/static_vector.hpp>

#include <array>
#include <unordered_map>


namespace boost {{ namespace text {{

static const std::unordered_map<uint32_t, compatible_decomposition>
g_compatible_decomposition_map = {{
{0}
}};

compatible_decomposition compatible_decompose(uint32_t cp) noexcept
{{
    // Hangul decomposition as described in Unicode 10.0 Section 3.12.
    if (0xAC00 <= cp && cp <= 0xD7A3) {{
        uint32_t const SBase = 0xAC00;
        uint32_t const LBase = 0x1100;
        uint32_t const VBase = 0x1161;
        uint32_t const TBase = 0x11A7;
        //uint32_t const LCount = 19;
        uint32_t const VCount = 21;
        uint32_t const TCount = 28;
        uint32_t const NCount = VCount * TCount; // 588
        //uint32_t const SCount = LCount * NCount; // 11172

        auto const SIndex = cp - SBase;

        auto const LIndex = SIndex / NCount;
        auto const VIndex = (SIndex % NCount) / TCount;
        auto const TIndex = SIndex % TCount;
        auto const LPart = LBase + LIndex;
        auto const VPart = VBase + VIndex;
        if (TIndex == 0) {{
            return compatible_decomposition{{{{{{LPart, VPart}}}}, 2}};
        }} else {{
            auto const TPart = TBase + TIndex;
            return compatible_decomposition{{{{{{LPart, VPart, TPart}}}}, 3}};
        }}
    }}

    auto const it = g_compatible_decomposition_map.find(cp);
    if (it == g_compatible_decomposition_map.end())
        return compatible_decomposition{{{{{{cp}}}}, 1}};
    return it->second;
}}

}}}}
'''

compose_file_form = decls = '''\
// Warning! This file is autogenerated.
#include <boost/text/normalization_data.hpp>

#include <boost/container/static_vector.hpp>

#include <array>
#include <unordered_map>


namespace boost {{ namespace text {{

namespace {{
    constexpr uint64_t key(uint64_t cp0, uint32_t cp1) noexcept
    {{
        return (cp0 << 32) | cp1;
    }}
}}

static const std::unordered_map<uint64_t, uint32_t>
g_composition_map = {{
{0}
}};

uint32_t compose_unblocked(uint32_t cp0, uint32_t cp1) noexcept
{{
    auto const it = g_composition_map.find(key(cp0, cp1));
    if (it == g_composition_map.end())
        return 0;
    return it->second;
}}

}}}}
'''

quick_checks_set_file_form = decls = '''\
// Warning! This file is autogenerated.
#include <boost/text/normalization_data.hpp>

#include <boost/container/static_vector.hpp>

#include <array>
#include <unordered_set>


namespace boost {{ namespace text {{

static const std::unordered_set<uint32_t>
g_{1}_quick_check_set = {{
{0}
}};

quick_check quick_check_{1}_code_point(uint32_t cp) noexcept
{{
    auto const it = g_{1}_quick_check_set.find(cp);
    if (it == g_{1}_quick_check_set.end())
        return quick_check::yes;
    return quick_check::no;
}}

}}}}
'''

quick_checks_map_file_form = decls = '''\
// Warning! This file is autogenerated.
#include <boost/text/normalization_data.hpp>

#include <boost/container/static_vector.hpp>

#include <array>
#include <unordered_map>


namespace boost {{ namespace text {{

static const std::unordered_map<uint32_t, quick_check>
g_{1}_quick_check_map = {{
{0}
}};

quick_check quick_check_{1}_code_point(uint32_t cp) noexcept
{{
    auto const it = g_{1}_quick_check_map.find(cp);
    if (it == g_{1}_quick_check_map.end())
        return quick_check::yes;
    return it->second;
}}

}}}}
'''


def cccs(filename):
    intervals = []
    lines = open(filename, 'r').readlines()
    for line in lines:
        line = line[:-1]
        if not line.startswith('#') and len(line) != 0:
            comment_start = line.find('#')
            comment = ''
            if comment_start != -1:
                comment = line[comment_start + 1:].strip()
                line = line[:comment_start]
            fields = map(lambda x: x.strip(), line.split(';'))
            ccc = fields[1]
            if ccc == '0':
                continue
            code_points = fields[0]
            if '..' in code_points:
                cps = code_points.split('.')
                interval = (int(cps[0], 16), int(cps[2], 16) + 1, ccc)
            else:
                cp = int(code_points, 16)
                interval = (cp, cp + 1, ccc)
            intervals.append(interval)

    intervals = sorted(intervals)
    intervals_list = ''
    cccs_dict = {}
    num_intervals = 0
    for interval in intervals:
        if False: #128 < interval[1] - interval[0]:
            num_intervals += 1
            intervals_list += '    ccc_interval{{{}, {}, {}}},\n'.format(
                hex(interval[0]), hex(interval[1]), interval[2]
            )
        else:
            for i in range(interval[0], interval[1]):
                cccs_dict[i] = interval[2]
    return cccs_dict

def expand_decomp_canonical(decomp, all_decomps):
    first_cp = decomp[0][0]
    if decomp[1] and first_cp in all_decomps and all_decomps[first_cp][1]:
        return expand_decomp_canonical((all_decomps[first_cp][0] + decomp[0][1:], True), all_decomps)
    return decomp

def expand_decomp_compatible(decomp, all_decomps):
    expandables = len(filter(lambda cp: cp in all_decomps, decomp[0]))
    if 0 < expandables:
        cps = map(lambda cp: cp in all_decomps and all_decomps[cp][0] or cp, decomp[0])
        flat_cps = []
        for cp in cps:
            if type(cp) == list:
                flat_cps += cp
            else:
                flat_cps.append(cp)
        return expand_decomp_compatible((flat_cps, True), all_decomps)
    return decomp

def get_decompositions(filename, cccs_dict, expand_decomp):
    decomps = {}

    # Pass 1: Find top-level decompositions
    lines = open(filename, 'r').readlines()
    for line in lines:
        line = line[:-1]
        if not line.startswith('#') and len(line) != 0:
            comment_start = line.find('#')
            comment = ''
            if comment_start != -1:
                comment = line[comment_start + 1:].strip()
                line = line[:comment_start]
            fields = map(lambda x: x.strip(), line.split(';'))
            if fields[5] == '':
                continue
            decomp_cps = fields[5].split(' ')
            canonical = True
            if decomp_cps[0].startswith('<'):
                decomp_cps = decomp_cps[1:]
                canonical = False
            decomp_cps = map(lambda x: int(x, 16), decomp_cps)
            cp = int(fields[0], 16)
            decomp = (decomp_cps, canonical)
            decomps[cp] = decomp

    # Pass 2: Expand Pass-1 decompositions
    expanded_decomps = map(
        lambda item: (item[0], expand_decomp(item[1], decomps)),
        sorted(decomps.items())
    )

    # Pass 3: Reorder Pass-2 decompositions uing cccs
    def reorder_cps(cps, cccs_dict):
        for i in range(1, len(cps) - 1):
            cp_a = cps[i]
            cp_b = cps[i + 1]
            # Each must be nonzero....
            if cp_a not in cccs_dict or cp_b not in cccs_dict:
                continue
            ccc_a = cccs_dict[cp_a]
            ccc_b = cccs_dict[cp_b]
            if ccc_b < ccc_a:
                cps[i] = cp_b
                cps[i + 1] = cp_a
        return cps

    decomps = map(
        lambda x: (x[0], (reorder_cps(x[1][0], cccs_dict), x[1][1])),
        expanded_decomps
    )

    return decomps


def get_compositions(filename, derived_normalization_props_filename):
    comps = []

    exclusions = set()
    lines = open(derived_normalization_props_filename, 'r').readlines()
    for line in lines:
        line = line[:-1]
        if not line.startswith('#') and len(line) != 0:
            comment_start = line.find('#')
            comment = ''
            if comment_start != -1:
                comment = line[comment_start + 1:].strip()
                line = line[:comment_start]
            fields = map(lambda x: x.strip(), line.split(';'))
            prop = fields[1]
            if prop != 'Full_Composition_Exclusion':
                continue
            code_points = fields[0]
            if '..' in code_points:
                cps = code_points.split('.')
                interval = (int(cps[0], 16), int(cps[2], 16) + 1)
            else:
                cp = int(code_points, 16)
                interval = (cp, cp + 1)
            for cp in range(interval[0], interval[1]):
                exclusions.add(cp)

    lines = open(filename, 'r').readlines()
    for line in lines:
        line = line[:-1]
        if not line.startswith('#') and len(line) != 0:
            comment_start = line.find('#')
            comment = ''
            if comment_start != -1:
                comment = line[comment_start + 1:].strip()
                line = line[:comment_start]
            fields = map(lambda x: x.strip(), line.split(';'))
            if fields[5] == '':
                continue
            decomp_cps = fields[5].split(' ')
            if len(decomp_cps) != 2 or decomp_cps[0].startswith('<'):
                continue
            decomp_cps = map(lambda x: int(x, 16), decomp_cps)
            cp = int(fields[0], 16)
            if cp not in exclusions:
                comps.append((decomp_cps, cp))

    return sorted(comps)

def get_quick_checks(filename):
    retval = {'NFD': {}, 'NFC': {}, 'NFKD': {}, 'NFKC': {}}

    file_prop_to_enum = {'N': 'quick_check::no', 'M': 'quick_check::maybe'}

    lines = open(filename, 'r').readlines()
    for line in lines:
        line = line[:-1]
        if not line.startswith('#') and len(line) != 0:
            comment_start = line.find('#')
            comment = ''
            if comment_start != -1:
                comment = line[comment_start + 1:].strip()
                line = line[:comment_start]
            fields = map(lambda x: x.strip(), line.split(';'))
            prop = fields[1]
            if not prop.endswith('_QC'):
                continue
            normalization_form = prop.split('_')[0]
            code_points = fields[0]
            if '..' in code_points:
                cps = code_points.split('.')
                interval = (int(cps[0], 16), int(cps[2], 16) + 1)
            else:
                cp = int(code_points, 16)
                interval = (cp, cp + 1)
            for cp in range(interval[0], interval[1]):
                retval[normalization_form][cp] = file_prop_to_enum[fields[2]]

    return retval

cccs_dict = cccs('DerivedCombiningClass.txt')
item_strings = map(lambda x : '{}, {}'.format(hex(x[0]), x[1]), sorted(cccs_dict.items()))
ccc_intervals_map = '    { ' + ' },\n    { '.join(item_strings) + ' },\n'
cpp_file = open('normalization_data_ccc.cpp', 'w')
cpp_file.write(ccc_file_form.format(ccc_intervals_map))

def cps_to_vec(cps):
    return '{ {{ ' + ', '.join(map(lambda x: hex(x), cps)) + ' }}}}, {} }}'.format(len(cps))

decomposition_mapping = get_decompositions('UnicodeData.txt', cccs_dict, expand_decomp_canonical)
item_strings = map(
    lambda x : '{}, {}'.format(hex(x[0]), cps_to_vec(x[1][0])),
    filter(lambda x: x[1][1], decomposition_mapping)
)
decompositions_map = '    { ' + ' },\n    { '.join(item_strings) + ' },\n'
cpp_file = open('normalization_data_canonical.cpp', 'w')
cpp_file.write(canonical_file_form.format(decompositions_map))

decomposition_mapping = get_decompositions('UnicodeData.txt', cccs_dict, expand_decomp_compatible)
item_strings = map(
    lambda x : '{}, {}'.format(hex(x[0]), cps_to_vec(x[1][0])),
    decomposition_mapping
)
decompositions_map = '    { ' + ' },\n    { '.join(item_strings) + ' },\n'

cpp_file = open('normalization_data_compatible.cpp', 'w')
cpp_file.write(compatible_file_form.format(decompositions_map))

composition_mapping = get_compositions('UnicodeData.txt', 'DerivedNormalizationProps.txt')
item_strings = map(
    lambda x : 'key({}, {}), {}'.format(hex(x[0][0]), hex(x[0][1]), hex(x[1])),
    composition_mapping
)
compositions_map = '    { ' + ' },\n    { '.join(item_strings) + ' },\n'

cpp_file = open('normalization_data_compose.cpp', 'w')
cpp_file.write(compose_file_form.format(compositions_map))


quick_check_maps = get_quick_checks('DerivedNormalizationProps.txt')
item_strings = map(
    lambda x : '{}'.format(hex(x[0]), x[1]),
    sorted(quick_check_maps['NFD'].items())
)
nfd_strings = '    ' + ',\n    '.join(item_strings) + ',\n'

cpp_file = open('normalization_data_quick_checks_nfd.cpp', 'w')
cpp_file.write(quick_checks_set_file_form.format(nfd_strings, 'nfd'))

item_strings = map(
    lambda x : '{}'.format(hex(x[0]), x[1]),
    sorted(quick_check_maps['NFKD'].items())
)
nfkd_strings = '    ' + ',\n    '.join(item_strings) + ',\n'

cpp_file = open('normalization_data_quick_checks_nfkd.cpp', 'w')
cpp_file.write(quick_checks_set_file_form.format(nfkd_strings, 'nfkd'))

item_strings = map(
    lambda x : '{}, {}'.format(hex(x[0]), x[1]),
    sorted(quick_check_maps['NFC'].items())
)
nfc_strings = '    { ' + ' },\n    { '.join(item_strings) + ' },\n'

cpp_file = open('normalization_data_quick_checks_nfc.cpp', 'w')
cpp_file.write(quick_checks_map_file_form.format(nfc_strings, 'nfc'))

item_strings = map(
    lambda x : '{}, {}'.format(hex(x[0]), x[1]),
    sorted(quick_check_maps['NFKC'].items())
)
nfkc_strings = '    { ' + ' },\n    { '.join(item_strings) + ' },\n'

cpp_file = open('normalization_data_quick_checks_nfkc.cpp', 'w')
cpp_file.write(quick_checks_map_file_form.format(nfkc_strings, 'nfkc'))