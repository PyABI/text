#!/usr/bin/env python
# -*- coding: utf-8 -*-

prop_lookup_test_form = decls = '''\
// Warning! This file is autogenerated.
#include <boost/text/{0}_break.hpp>

#include <gtest/gtest.h>


TEST({0}, prop_lookups_{2})
{{{1}
}}
'''

prop_lookup_perf_test_form = decls = '''\
// Warning! This file is autogenerated.
#include <boost/text/{0}_break.hpp>

#include <benchmark/benchmark.h>

#include <iostream>


void BM_{0}_prop(benchmark::State & state)
{{
    while (state.KeepRunning()) {{
{1}
    }}
    std::cout << "Divide result by {2} to get mean time.\\n";
}}


BENCHMARK(BM_{0}_prop);

BENCHMARK_MAIN()
'''

break_test_form = decls = '''\
// Warning! This file is autogenerated.
#include <boost/text/{0}_break.hpp>

#include <gtest/gtest.h>

#include <algorithm>


TEST({0}, breaks_{2})
{{{1}
}}
'''

grapheme_iterator_test_form = decls = '''\
// Warning! This file is autogenerated.
#include <boost/text/grapheme_iterator.hpp>
#include <boost/text/utf8.hpp>

#include <gtest/gtest.h>

#include <algorithm>


{0}
'''


def extract_cps_and_breaks(filename, batch_size = 50):
    current_batch = []
    retval = []
    lines = open(filename, 'r').readlines()
    num_lines = 0
    for line in lines:
        if num_lines == batch_size:
            retval.append(current_batch)
            current_batch = []
            num_lines = 0
        line = line[:-1]
        if not line.startswith('#') and len(line) != 0:
            comment_start = line.find('#')
            comment = ''
            if comment_start != -1:
                comment = line[comment_start + 1:].strip()
                line = line[:comment_start]
            fields = line.split(' ')[1:-1]
            cps = []
            active_break = True
            for i in range(len(fields)):
                f = fields[i]
                if f[0] in '0123456789ABCDEF':
                    cps.append((f, active_break))
                else:
                    active_break = f == '÷'
            current_batch.append((cps, line, comment))
        num_lines += 1
    if len(current_batch):
        retval.append(current_batch)
    return retval

def generate_prop_lookup_tests(cps_and_breaks, prop_, prop_names):
    for i in range(len(cps_and_breaks)):
        prop_lookup_tests = ''
        chunk = cps_and_breaks[i]
        for elem in chunk:
            (cps, line, comment) = elem
            comment_fields = comment.split(' ')
            j = 0
            for f in comment_fields:
                if f.startswith('(') and f.endswith(')'):
                    prop_lookup_tests += \
                        '\n    EXPECT_EQ(boost::text::{0}_prop(0x{1}), {2});'.format(
                            prop_, cps[j][0], prop_names[f[1:-1]]
                        )
                    j += 1
        cpp_file = open('{}_prop_lookup_{:02}.cpp'.format(prop_, i), 'w')
        cpp_file.write(prop_lookup_test_form.format(prop_, prop_lookup_tests, i))

def generate_prop_lookup_perf_tests(cps_and_breaks, prop_):
    prop_lookup_perf_tests = ''
    lines = 0
    for i in range(len(cps_and_breaks)):
        chunk = cps_and_breaks[i]
        for elem in chunk:
            (cps, line, comment) = elem
            comment_fields = comment.split(' ')
            j = 0
            for f in comment_fields:
                if f.startswith('(') and f.endswith(')'):
                    prop_lookup_perf_tests += \
                        '        benchmark::DoNotOptimize(boost::text::{0}_prop(0x{1}));\n'.format(
                            prop_, cps[j][0]
                        )
                    j += 1
                    lines += 1
    cpp_file = open('{}_prop_lookup_perf.cpp'.format(prop_, i), 'w')
    cpp_file.write(prop_lookup_perf_test_form.format(prop_, prop_lookup_perf_tests, lines))

def generate_break_tests(cps_and_breaks, prop_):
    for i in range(len(cps_and_breaks)):
        break_tests = ''
        chunk = cps_and_breaks[i]
        for elem in chunk:
            (cps, line, comment) = elem
            comment_fields = comment.split(' ')
            break_tests += '''
    // {0}
    // {1}
    {{
        boost::text::{2}_break_t prev_break;
'''.format(line, comment, prop_)
            if 'word' in prop_:
                break_tests += '\n        prev_break.prop_ = boost::text::{}_prop(0x{});\n'.format(
                    prop_, cps[0][0]
                )
            for j in range(len(cps)):
                cp = cps[j]
                if 'word' in prop_:
                    next_cp = j == len(cps) - 1 and '0' or cps[j + 1][0]
                    break_tests += '''
        prev_break = boost::text::{}_break(prev_break.fsm_, prev_break.prev_prop_, prev_break.prop_, 0x{});
        EXPECT_EQ(prev_break.break_, {});'''.format(prop_, next_cp, cp[1] and 'true' or 'false')
                else:
                    break_tests += '''
        prev_break = boost::text::{}_break(prev_break.fsm_, prev_break.prop_, 0x{});
        EXPECT_EQ(prev_break.break_, {});'''.format(prop_, cp[0], cp[1] and 'true' or 'false')
            break_tests += '\n    }\n'
        cpp_file = open('{}_break_{:02}.cpp'.format(prop_, i), 'w')
        cpp_file.write(break_test_form.format(prop_, break_tests, i))

def generate_break_tests_2(cps_and_breaks, prop_, prop_prefix = ''):
    for i in range(len(cps_and_breaks)):
        break_tests = ''
        chunk = cps_and_breaks[i]
        for elem in chunk:
            (cps, line, comment) = elem
            comment_fields = comment.split(' ')
            break_tests += '''
    // {0}
    // {1}
    {{
        std::array<uint32_t, {3}> cps = {{{{ {2} }}}};
'''.format(line, comment, ', '.join(map(lambda x: hex(int(x[0], 16)), cps)), len(cps))
            for j in range(len(cps) + 1):
                prev_break = j
                while prev_break == len(cps) or prev_break != 0 and not cps[prev_break][1]:
                    prev_break -= 1
                next_break = min(j + 1, len(cps))
                while next_break != len(cps) and not cps[next_break][1]:
                    next_break += 1
                break_tests += '''\
        EXPECT_EQ(boost::text::prev_{4}{3}_break(cps.begin(), cps.begin() + {0}, cps.end()) - cps.begin(), {1});
        EXPECT_EQ(boost::text::next_{4}{3}_break(cps.begin() + {1}, cps.end()) - cps.begin(), {2});
'''.format(j, prev_break, next_break, prop_, prop_prefix)
            break_tests += '    }\n\n'
        cpp_file = open('{}_break_{:02}.cpp'.format(prop_, i), 'w')
        cpp_file.write(break_test_form.format(prop_, break_tests, i))

def contains_surrogate(cps):
    for cp in cps:
        if int(cp[0], 16) == 0xD800:
            return True
    return False

def generate_iterator_tests(cps_and_breaks, prop_):
    for i in range(len(cps_and_breaks)):
        iterator_tests = ''
        chunk = cps_and_breaks[i]
        elem_index = -1
        for elem in chunk:
            elem_index += 1
            (cps, line, comment) = elem
            comment_fields = comment.split(' ')

            break_cp_indices = []
            for j in range(len(cps)):
                if cps[j][1]: # if break
                    break_cp_indices.append(j)

            graphemes_and_end = []
            code_unit_graphemes_and_end = []
            for j in range(len(break_cp_indices)):
                last_cp = j == len(break_cp_indices) - 1
                first = break_cp_indices[j]
                last = last_cp and len(cps) or break_cp_indices[j + 1]

                graphemes_and_end.append('''\
        EXPECT_EQ(it.base(), cps + {0});
        EXPECT_EQ((*it).begin(), cps + {0});
        EXPECT_EQ((*it).end(), cps + {1});'''.format(first, last))

                code_unit_grapheme = '''\
        EXPECT_EQ(*it.base(), cps[{0}]);
        EXPECT_EQ(*it->begin(), cps[{0}]);'''.format(first)
                if not last_cp:
                    code_unit_grapheme += '''
        EXPECT_EQ(*it->end(), cps[{0}]);'''.format(last)
                code_unit_grapheme += '''
        EXPECT_EQ(it.base().base(), cus + cp_indices[{0}]);
        EXPECT_EQ(it->begin().base(), cus + cp_indices[{0}]);
        EXPECT_EQ(it->end().base(), cus + cp_indices[{1}]);'''.format(first, last)
                code_unit_graphemes_and_end.append(code_unit_grapheme)

            graphemes_and_end.append('''\
        EXPECT_EQ(it.base(), cps + {});
        EXPECT_EQ((*it).begin(), (*it).end());'''.format(len(cps)))
            code_unit_graphemes_and_end.append('''\
        EXPECT_EQ(it.base().base(), cus + cp_indices[{}]);
        EXPECT_EQ(it->begin(), (*it).end());'''.format(len(cps)))

            # forward
            iterator_tests += '''
TEST({3}, iterator_{5:02}_{6}_fwd)
{{
    // {0}
    // {1}
    {{
        uint32_t const cps[] = {{ {2} }};
        boost::text::{3}_iterator<uint32_t const *> it(cps, cps, cps + {4});

'''.format(line, comment, '0x' + ', 0x'.join(map(lambda x: x[0], cps)), prop_, len(cps), i, elem_index)
            iterator_tests += '\n\n        ++it;\n\n'.join(graphemes_and_end)
            iterator_tests += '\n    }\n}\n'

            # reverse
            iterator_tests += '''\
TEST({1}, iterator_{3:02}_{4}_rev)
{{
    {{
        // reverse
        uint32_t const cps[] = {{ {0} }};
        boost::text::{1}_iterator<uint32_t const *> it(cps, cps + {2}, cps + {2});

'''.format('0x' + ', 0x'.join(map(lambda x: x[0], cps)), prop_, len(cps), i, elem_index)
            iterator_tests += '\n\n        --it;\n\n'.join(reversed(graphemes_and_end))
            iterator_tests += '\n    }\n}\n'

            # forth and back
            iterator_tests += '''\
TEST({1}, iterator_{3:02}_{4}_fab)
{{
    {{
        // forth and back
        uint32_t const cps[] = {{ {0} }};
        boost::text::{1}_iterator<uint32_t const *> it(cps, cps, cps + {2});

'''.format('0x' + ', 0x'.join(map(lambda x: x[0], cps)), prop_, len(cps), i, elem_index)
            idx = 0
            iterator_tests += graphemes_and_end[idx]
            for j in range(len(graphemes_and_end)):
                for k in range(j):
                    iterator_tests += '\n\n        ++it;\n\n'
                    idx += 1
                    iterator_tests += graphemes_and_end[idx]
                for k in range(j):
                    iterator_tests += '\n\n        --it;\n\n'
                    idx -= 1
                    iterator_tests += graphemes_and_end[idx]
            iterator_tests += '\n    }\n}\n'

            # back and forth
            iterator_tests += '''\
TEST({1}, iterator_{3:02}_{4}_baf)
{{
    {{
        // back and forth
        uint32_t const cps[] = {{ {0} }};
        boost::text::{1}_iterator<uint32_t const *> it(cps, cps + {2}, cps + {2});

'''.format('0x' + ', 0x'.join(map(lambda x: x[0], cps)), prop_, len(cps), i, elem_index)
            idx = len(graphemes_and_end) - 1
            iterator_tests += graphemes_and_end[idx]
            for j in range(len(graphemes_and_end)):
                for k in range(j):
                    iterator_tests += '\n\n        --it;\n\n'
                    idx -= 1
                    iterator_tests += graphemes_and_end[idx]
                for k in range(j):
                    iterator_tests += '\n\n        ++it;\n\n'
                    idx += 1
                    iterator_tests += graphemes_and_end[idx]
            iterator_tests += '\n    }\n}\n'

            # from UTF8
            if contains_surrogate(cps):
                iterator_tests += \
                  '// Skipping from-utf8 test due to presence of surrogate code point.\n'
            else:
                iterator_tests += '''\
TEST({1}, iterator_{3:02}_{4}_utf8)
{{
    {{
        // from UTF8
        uint32_t const cps[] = {{ {0} }};
        char cus[1024] = {{ 0 }};
        int cp_indices[1024] = {{ 0 }};

        std::copy(
            boost::text::utf8::from_utf32_iterator<uint32_t const *>(cps, cps, cps + {2}),
            boost::text::utf8::from_utf32_iterator<uint32_t const *>(cps, cps + {2}, cps + {2}),
            cus);

        boost::text::utf8::null_sentinel sentinel;
        int * index_it = cp_indices;
        for (boost::text::utf8::to_utf32_iterator<char const *, boost::text::utf8::null_sentinel> it(cus, cus, boost::text::utf8::null_sentinel{{}}); ; ++it) {{
            *index_it++ = it.base() - cus;
            if (it == sentinel)
                break;
        }}

        using iter_t = boost::text::utf8::to_utf32_iterator<char const *, boost::text::utf8::null_sentinel>;
        boost::text::{1}_iterator<iter_t, boost::text::utf8::null_sentinel> it(
            iter_t{{cus, cus, boost::text::utf8::null_sentinel{{}}}}, iter_t{{cus, cus, boost::text::utf8::null_sentinel{{}}}}, sentinel);

'''.format('0x' + ', 0x'.join(map(lambda x: x[0], cps)), prop_, len(cps), i, elem_index)
                iterator_tests += '\n\n        ++it;\n\n'.join(code_unit_graphemes_and_end)
                iterator_tests += '\n    }\n}\n'

        cpp_file = open('{}_iterator_{:02}.cpp'.format(prop_, i), 'w')
        cpp_file.write(grapheme_iterator_test_form.format(iterator_tests, i))


grapheme_prop_names = {
    'Other': 'boost::text::grapheme_property::Other',
    'Prepend': 'boost::text::grapheme_property::Prepend',
    'CR': 'boost::text::grapheme_property::CR',
    'LF': 'boost::text::grapheme_property::LF',
    'Control': 'boost::text::grapheme_property::Control',
    'Extend': 'boost::text::grapheme_property::Extend',
    'RI': 'boost::text::grapheme_property::Regional_Indicator',
    'SpacingMark': 'boost::text::grapheme_property::SpacingMark',
    'L': 'boost::text::grapheme_property::L',
    'V': 'boost::text::grapheme_property::V',
    'T': 'boost::text::grapheme_property::T',
    'LV': 'boost::text::grapheme_property::LV',
    'LVT': 'boost::text::grapheme_property::LVT',
    'E_Base': 'boost::text::grapheme_property::E_Base',
    'E_Modifier': 'boost::text::grapheme_property::E_Modifier',
    'ZWJ': 'boost::text::grapheme_property::ZWJ',
    'Glue_After_Zwj': 'boost::text::grapheme_property::Glue_After_Zwj',
    'EBG': 'boost::text::grapheme_property::E_Base_GAZ'
}

import sys

grapheme_cps_and_breaks = extract_cps_and_breaks('GraphemeBreakTest.txt')
if '--perf' in sys.argv:
    generate_prop_lookup_perf_tests(grapheme_cps_and_breaks, 'grapheme')
    exit(0)
generate_break_tests_2(grapheme_cps_and_breaks, 'grapheme')
generate_iterator_tests(grapheme_cps_and_breaks, 'grapheme')

word_prop_names = {
    'Other': 'boost::text::word_property::Other',
    'Double_Quote': 'boost::text::word_property::Double_Quote',
    'Single_Quote': 'boost::text::word_property::Single_Quote',
    'Hebrew_Letter': 'boost::text::word_property::Hebrew_Letter',
    'CR': 'boost::text::word_property::CR',
    'LF': 'boost::text::word_property::LF',
    'Newline': 'boost::text::word_property::Newline',
    'Extend_FE': 'boost::text::word_property::Extend',
    'RI': 'boost::text::word_property::Regional_Indicator',
    'Format_FE': 'boost::text::word_property::Format',
    'Katakana': 'boost::text::word_property::Katakana',
    'ALetter': 'boost::text::word_property::ALetter',
    'MidLetter': 'boost::text::word_property::MidLetter',
    'MidNum': 'boost::text::word_property::MidNum',
    'MidNumLet': 'boost::text::word_property::MidNumLet',
    'Numeric': 'boost::text::word_property::Numeric',
    'ExtendNumLet': 'boost::text::word_property::ExtendNumLet',
    'E_Base': 'boost::text::word_property::E_Base',
    'E_Modifier': 'boost::text::word_property::E_Modifier',
    'ZWJ_FE': 'boost::text::word_property::ZWJ',
    'Glue_After_Zwj': 'boost::text::word_property::Glue_After_Zwj',
    'EBG': 'boost::text::word_property::E_Base_GAZ'
}

word_cps_and_breaks = extract_cps_and_breaks('WordBreakTest.txt')
generate_break_tests_2(word_cps_and_breaks, 'word')

sentence_cps_and_breaks = extract_cps_and_breaks('SentenceBreakTest.txt')
generate_break_tests_2(sentence_cps_and_breaks, 'sentence')

line_cps_and_breaks = extract_cps_and_breaks('LineBreakTest.txt', 100)
generate_break_tests_2(line_cps_and_breaks, 'line', 'possible_')
