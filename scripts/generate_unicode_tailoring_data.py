#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Point this at the icu4c/source/data/coll directory, and it will create
# several headers containing the collation tailorings found there.

# To get this dumb script to work, I have to spell out some imports in the ICU
# files:

# fi.txt: [import fi-u-co-trad] -> [import fi-u-co-traditional]
# de.txt: [import de-u-co-phonebk] - > [import de-u-co-phonebook]


from generate_unicode_collation_data import get_frac_uca_cet
from generate_unicode_collation_data import ce_to_cpp

import argparse
import os
import re


parser = argparse.ArgumentParser(description='Generates headers with tailoring scripts for use with Boost.Text\'s Unicode collation.')
parser.add_argument('icu_dir', type=str, help='the path to icu4c/source/data/coll containing ICU\'s tailoring data')
parser.add_argument('--tests', action='store_true', help='generate lexer and parser tests instead of the data themselves')
args = parser.parse_args()

all_tailorings = {}
tailorings_by_file = {}

for filename in os.listdir(args.icu_dir):
    lines = open(os.path.join(args.icu_dir, filename)).readlines()
    root,ext = os.path.splitext(filename)
    if ext != '.txt':
        continue
    if root == 'root':
        root = 'und'
    name_prefix = root + '-u-co-'
    name = ''
    line_idx = 0
    max_line_idx = len(lines)
    while line_idx < max_line_idx:
        line = lines[line_idx]
        if 'Sequence{' in line:
            seq_end_line_idx = line_idx
            while not line.strip().endswith('}'):
                seq_end_line_idx += 1
                line = lines[seq_end_line_idx]
            sequence = ''.join(lines[line_idx:seq_end_line_idx + 1]).strip()
            if not sequence.startswith('Sequence{'):
                raise Exception('Oops!')
            sequence = sequence[len('Sequence{'):-1]
            sequence = map(lambda x: x.strip()[1:-1], sequence.splitlines())
            sequence = map(lambda x: (x.startswith('&') or x.startswith('[')) and x or '  ' + x, sequence)
            sequence = '\n'.join(sequence)
            if name == '':
                raise Exception('Somehow we got unnamed tailoring rules!')
            all_tailorings[name_prefix + name] = sequence
            if sequence.strip() != '':
                if root not in tailorings_by_file:
                    tailorings_by_file[root] = {}
                tailorings_by_file[root][name] = sequence
            name = ''
            line_idx = seq_end_line_idx + 1
            continue
        if not 'collations' in line and '{' in line and '"' not in line and '}' not in line:
            name = line.strip()[:-1]
            line_idx += 1
            continue
        line_idx += 1

lexer_tests_form = '''\
// Warning! This file is autogenerated.
#include <boost/text/data/all.hpp>
#include <boost/text/detail/lexer.hpp>

#include <gtest/gtest.h>


TEST(lexer, data)
{{

{0}
}}
'''

parser_tests_form = '''\
// Warning! This file is autogenerated.
#include <boost/text/data/all.hpp>
#include <boost/text/detail/parser.hpp>

#include <gtest/gtest.h>


TEST(parser, data)
{{

    boost::text::detail::collation_tailoring_interface callbacks = {{
        [](boost::text::detail::cp_seq_t const & reset_, bool before_) {{}},
        [](boost::text::detail::relation_t const & rel) {{}},
        [](boost::text::collation_strength strength) {{}},
        [](boost::text::variable_weighting weighting) {{}},
        [](boost::text::l2_weight_order order) {{}},
        [](boost::text::case_level) {{}},
        [](boost::text::case_first) {{}},
        [](boost::text::detail::cp_seq_t const & suppressions) {{}},
        [](std::vector<boost::text::detail::reorder_group> const & reorder_groups) {{}},
        [](boost::text::string const & s) {{
            std::cout << s << std::endl;
            throw std::runtime_error("Parser produced an error!");
        }},
        [](boost::text::string const & s) {{ /*std::cout << s << std::endl;*/ }}
    }};


{0}
}}
'''

any_option_regex = re.compile(r'\[[^ \]]+\] *')
reorder_regex = re.compile(r'\[ *reorder([^\]]+) *\]')
suppress_regex = re.compile(r'\[ *suppressContractions(?: +([^ \]]+))+ *\]')

group_cps = {
    'Mlym': [0x0D05, 0x0D06, 0x0D3B, 0x0D3C],
    'Armn': [0x0561, 0x0531, 0x0556, 0x0559],
    'Hani': [0x2F00, 0x3280, 0x2F88F, 0x2FA1D],
    'Laoo': [0x0EDE, 0x0E81, 0x0EC3, 0x0EC4],
    'Cher': [0xAB70, 0x13A0, 0x13FD, 0x13F5],
    'Ethi': [0x1200, 0x1201, 0x2DDD, 0x2DDE],
    'Mong': [0x1880, 0x1881, 0x18AA, 0x18A9],
    'Hebr': [0x05D0, 0x2135, 0xFB28, 0xFB4A],
    'Bopo': [0x3105, 0x31A0, 0x3129, 0x312D],
    'Geor': [0x10D0, 0x2D00, 0x10FE, 0x10FF],
    'Deva': [0x0950, 0xA8FD, 0x094C, 0x094D],
    'Cyrl': [0x0430, 0x2DF6, 0x04CF, 0x04C0],
    'Arab': [0x0621, 0x077A, 0x077B],
    'Mymr': [0x1000, 0x1075, 0xAA75, 0xAA76],
    'Khmr': [0x1780, 0x1781, 0x17C5, 0x17D2],
    'Sinh': [0x0D85, 0x0D86, 0x0DDE, 0x0DCA],
    'Thai': [0x0E01, 0x0E02, 0x0E43, 0x0E44],
    'Grek': [0x03B1, 0x1D6C2, 0x03F8, 0x03F7],
    'Beng': [0x0980, 0x0985, 0x09D7, 0x09FC],
    'Guru': [0x0A74, 0x0A73, 0x0A4B, 0x0A4C],
    'Gujr': [0x0AD0, 0x0A85, 0x0ACC, 0x0ACD],
    'Orya': [0x0B05, 0x0B06, 0x0B56, 0x0B57],
    'Taml': [0x0BD0, 0x0B85, 0x0BCD, 0x0BD7],
    'Telu': [0x0C05, 0x0C06, 0x0C55, 0x0C56],
    'Knda': [0x0C85, 0x0C86, 0x0CD5, 0x0CD6],
    'Latn': [0x0061, 0xFF41, 0x02AC, 0x02AD],
    'Kana': [0x3041, 0x3042, 0x1B11D, 0x1B11E],
    # Hangul precomposed syllable 0xD7A3 -> 0x1112 0x1175 0x11C2
    'Hang': [0x1100, 0x3131, 0xD7A3, 0xD7FA, 0xD7FB],
    'implicit': [0x2a700, 0x2b740, 0x2b820, 0x2ebe0]
}

groups_in_ce_order = [
    'Latn',
    'Grek',
    'Cyrl',
    'Geor',
    'Armn',
    'Hebr',
    'Arab',
    'Ethi',
    'Deva',
    'Beng',
    'Guru',
    'Gujr',
    'Orya',
    'Taml',
    'Telu',
    'Knda',
    'Mlym',
    'Sinh',
    'Thai',
    'Laoo',
    'Mymr',
    'Khmr',
    'Mong',
    'Cher',
    'Hang',
    'Kana',
    'Bopo',
    'Hani'
]

if args.tests:
    lex_tests = ''
    parse_tests = ''
    for k0,v0 in sorted(tailorings_by_file.items()):
        file_comment = '    // From {}.txt:\n\n'.format(k0)
        lex_tests += file_comment
        parse_tests += file_comment
        for k,v in sorted(v0.items()):
            if k.startswith('private'):
                continue
            strname = 'boost::text::data::{}::{}_collation_tailoring()'.format(
                k0 == 'or' and 'or_' or k0, k
            )
            lex_tests += '''\
    {{
        auto const str = {0};
        EXPECT_NO_THROW(
            boost::text::detail::lex(
                str.begin(),
                str.end(),
                [](boost::text::string const & s) {{
                    std::cout << s << std::endl;
                    throw std::runtime_error("Lexer produced an error!");
                }},
                "{1}.hpp")
        );
    }}
'''.format(strname, k0)
            parse_tests += '''\
    {{
        auto const str = {0};
        EXPECT_NO_THROW(
            boost::text::detail::parse(
                str.begin(),
                str.end(),
                callbacks,
                "{1}.hpp")
        );
    }}
'''.format(strname, k0)
        lex_tests += '\n\n'
        parse_tests += '\n\n'

    f = open('lexer_data.cpp', 'w')
    f.write(lexer_tests_form.format(lex_tests))
    f = open('parser_data.cpp', 'w')
    f.write(parser_tests_form.format(parse_tests))

import_regex = re.compile(r'\[ *import +([^ \]]+) *\] *')

single_tailoring_form = '''\
inline string_view {0}_collation_tailoring()
{{
    return string_view(
{1});
}}

'''

very_long_single_tailoring_form = '''\
inline string {0}_collation_tailoring()
{{
    string str;
{1}
    return str;
}}

'''


header_form = '''\
// Warning! This file is autogenerated.
#ifndef BOOST_TEXT_DATA_{0}_HPP
#define BOOST_TEXT_DATA_{0}_HPP

#include <boost/text/string_view.hpp>


namespace boost {{ namespace text {{ namespace data {{ namespace {1} {{

{2}
}}}}}}}}

#endif
'''

tailored_reordering_form = '''\
// Warning! This file is autogenerated.
#include <boost/text/collation_table.hpp>
#include <boost/text/collate.hpp>
#include <boost/text/data/all.hpp>

#include <gtest/gtest.h>


using namespace boost;

auto const error = [](text::string const & s) {{ std::cout << s; }};
auto const warning = [](text::string const & s) {{}};

{0}
'''

tailored_reordering_test_form = '''\
TEST(tailoring, {0}_{1}_reorders)
{{
    constexpr std::array<uint32_t, {3}> cps = {{{{
        {2}
    }}}};
    text::collation_table const table =
        text::tailored_collation_table(
            text::data::{0}::{1}_collation_tailoring(),
            "{0}::{1}_collation_tailoring()",
            error, warning);

    for (int i = 0, end = (int)cps.size() - 1; i != end; ++i) {{
        EXPECT_LE(
            text::collate(
                cps.begin() + i,
                cps.begin() + i + 1,
                cps.begin() + i + 1,
                cps.begin() + i + 2,
                table,
                text::collation_strength::primary,
                text::case_first::off,
                text::case_level::off,
                text::variable_weighting::non_ignorable),
            0)
            << "CASE " << i << " {0}::{1}_collation_tailoring() "
            << std::hex << "0x" << cps[i] << " 0x" << cps[i + 1] << std::dec;
    }}
}}

'''

tailoring_string_form = '''\
    g_curr_file = "{0}";
    g_curr_tailoring = "{1}";
    g_tailoring = data::{0}::{1}_collation_tailoring();
    make_test();
'''

tailoring_rules_tests_form = '''\
// Warning! This main() is autogenerated.
int main()
{{
{0}
}}
'''

tailoring_suppression_tests_form = '''\
// Warning! This file is autogenerated.
#include <boost/text/collation_table.hpp>
#include <boost/text/collate.hpp>
#include <boost/text/data/all.hpp>

#include <gtest/gtest.h>


using namespace boost;

auto const error = [](text::string const & s) {{ std::cout << s; }};
auto const warning = [](text::string const & s) {{}};
{0}
'''

def escape_chars(s):
    retval = ''
    for c in s:
        value = ord(c)
        if value < 0x80:
            retval += c
        else:
            retval += '\\x' + hex(value)[2:]
    return retval

# These are the only two suppressions that appear in the current tailoring
# data.
short_suppression = [0x0418, 0x0438]
long_suppression = [0x0e40, 0x0e41, 0x0e42, 0x0e43, 0x0e44, 0x0ec0, 0x0ec1, 0x0ec2, 0x0ec3, 0x0ec4, 0xaab5, 0xaab6, 0xaab9, 0xaabb, 0xaabc, 0x19b5, 0x19b6, 0x19b7, 0x19ba]

cet = get_frac_uca_cet('FractionalUCA.txt')
def find_suppressed_contractions(suppressions):
    retval = []
    for s in suppressions:
        for k in cet:
            if 1 < len(k) and k[0] == s:
                alternate_ces = []
                for ki in k:
                    alternate_ces += map(lambda x: 'text::detail::collation_element' + ce_to_cpp(x), cet[(ki,)][0])
                retval.append((k, alternate_ces))
    return retval

suppressed_short_contractions = find_suppressed_contractions(short_suppression)
suppressed_long_contractions = find_suppressed_contractions(long_suppression)

def suppression_test(ns, string, suppressed_contractions):
    test_count = -1
    max_tests = 150
    block_index = 0

    retval = ''

    for sc in suppressed_contractions:
        test_count += 1
        if test_count == max_tests:
            retval += '}\n'
            test_count = 0
            block_index += 1
        if test_count == 0:
            retval += '''\

TEST(tailoring, {0}_{1}_suppressions_{2})
{{
    text::collation_table const table =
        text::tailored_collation_table(
            text::data::{0}::{1}_collation_tailoring(),
            "{0}::{1}_collation_tailoring()",
            error, warning);

'''.format(ns, string, block_index)

        retval += '''\
    {{
        uint32_t cps[{1}] = {{ {0} }};
        container::small_vector<text::detail::collation_element, 1024> ces = {{
            {2}
        }};
        container::small_vector<text::detail::collation_element, 1024> result =
            table.collation_elements(cps, cps + {1});
        // Ignore lead byte reorderings.  We just care if the contractions
        // happen.
        for (auto & ce : ces) {{
            ce.l1_ &= 0x00ffffff;
            ce.l3_ &= text::detail::disable_case_level_mask;
        }}
        for (auto & ce : result) {{ ce.l1_ &= 0x00ffffff; }}
        EXPECT_EQ(result, ces);
    }}
'''.format(', '.join(map(lambda x: hex(x), sc[0])), len(sc[0]), ',\n            '.join(sc[1]))

    if test_count != 0:
        retval += '}\n'
    return retval


reordering_tailoring_tests = ''
have_short_suppression_test = False
have_long_suppression_test = False
suppression_tests = ''
tailoring_string_strings = ''

# Flatten tailorings_by_file by processing the [import]s.
for k0,v0 in sorted(tailorings_by_file.items()):
    tailorings = ''
    for k,v in sorted(v0.items()):
        match = True
        while match:
            match = import_regex.search(v)
            if match:
                import_ = match.group(1)
                if not import_ in all_tailorings:
                    import_ += '-u-co-standard'
                if not import_ in all_tailorings:
                    print '{}.txt: error: Unable to satisfy import "{}".'.format(k0, match.group(1))
                    done = True
                    break
                replacement = all_tailorings[import_]
                v = v.replace(v[match.start(0):match.end(0)], replacement)
        if not k.startswith('private'):
            lines = v.replace('\\', '\\\\').splitlines()
            lines = map(lambda x: 'u8"' + x + '\\n"', lines)
            chunked_lines = []
            for i in range(len(lines)):
                chunk_size = 4096
                if len(lines[i]) < chunk_size:
                    chunked_lines.append(lines[i])
                else:
                    chunks = len(lines[i]) / chunk_size
                    remainder = len(lines[i]) % chunk_size
                    prev_offset = 0
                    offset = 0
                    for j in range(chunks):
                        line_ok = False
                        while not line_ok:
                            try:
                                line = lines[i][j * chunk_size + prev_offset:(j + 1) * chunk_size + offset]
                                line.decode('UTF-8', 'strict')
                                line_ok = True
                            except UnicodeDecodeError:
                                offset -= 1
                        prev_offset = offset
                        if not line.startswith('u8"'):
                            line = 'u8"' + line
                        if not line.endswith('"'):
                            line += '"'
                        chunked_lines.append(line)
                    if remainder != 0 or offset != 0:
                        chunked_lines.append('u8"' + lines[i][chunks * chunk_size + offset:])
            if k0 == 'zh':
                chunked_lines = map(escape_chars, chunked_lines)
            if len(v) < (1 << 13) and k0 != 'zh':
                chunked_lines = map(lambda x: x[3:-3], chunked_lines)
                lines = 'u8R"(' + '\n'.join(chunked_lines).replace('\\\\', '\\') + ')"'
                tailorings += single_tailoring_form.format(k, lines)
            elif len(v) < (1 << 15) and k0 != 'zh':
                lines = '\n'.join(chunked_lines)
                tailorings += single_tailoring_form.format(k, lines)
            else:
                lines = map(lambda x: '    str += {};'.format(x), chunked_lines)
                lines = '\n'.join(lines)
                tailorings += very_long_single_tailoring_form.format(k, lines)

        groups = []
        for match in reorder_regex.finditer(v):
            for g in match.group(1).strip().split(' '):
                groups.append(g)
        if 'private' not in k and 'zh' not in k0 and len(groups) and 'others' not in groups:
            groups += filter(lambda x: x not in groups, groups_in_ce_order)
            group_ordering_cps = 0
            cps_string = ''
            for group in groups:
                group_ordering_cps += len(group_cps[group])
                cps_string += '/* {} */ '.format(group) + ', '.join(map(lambda x: hex(x), group_cps[group])) + ', '
                if group == 'Hani':
                    group_ordering_cps += len(group_cps['implicit'])
                    cps_string += '/* implicit */ ' + ', '.join(map(lambda x: hex(x), group_cps['implicit'])) + ', '
            reordering_tailoring_tests += tailored_reordering_test_form.format(
                k0 == 'or' and 'or_' or k0, k, cps_string, group_ordering_cps
            )

        suppressions = []
        for match in suppress_regex.finditer(v):
            g = match.group(1)
            if g.startswith('['):
                g = g[1:]
            suppressions.append(g)

        if len(suppressions):
            if len(suppressions) != 1:
                raise Exception("I can't even.")
            if suppressions == ['\xd0\x98\xd0\xb8']:
                if not have_short_suppression_test:
                    suppression_tests += suppression_test(k0, k, suppressed_short_contractions)
                have_short_suppression_test = True
            else:
                if not have_long_suppression_test:
                    suppression_tests += suppression_test(k0, k, suppressed_long_contractions)
                have_long_suppression_test = True

        if 'private' not in k:
            tailoring_string_strings += tailoring_string_form.format(
                k0 == 'or' and 'or_' or k0, k
            )

    if args.tests:
        f = open('tailoring_reorderings.cpp', 'w')
        f.write(tailored_reordering_form.format(reordering_tailoring_tests))
        f = open('tailoring_rules_tests_main.cpp', 'w')
        f.write(tailoring_rules_tests_form.format(tailoring_string_strings))
        f = open('tailoring_suppressions.cpp', 'w')
        f.write(tailoring_suppression_tests_form.format(suppression_tests))
    else:
        f = open(k0 + '.hpp', 'w')
        f.write(header_form.format(k0.upper(), k0 == 'or' and 'or_' or k0, tailorings))
        f.close()
