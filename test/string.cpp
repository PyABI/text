// Copyright (C) 2020 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#define BOOST_TEXT_TESTING
#include <boost/text/string.hpp>

#include <boost/algorithm/cxx14/equal.hpp>

#include <gtest/gtest.h>

#include <list>


using namespace boost;

TEST(string, test_empty)
{
    text::string t;

    EXPECT_EQ(t.begin(), t.end());
    EXPECT_EQ(t.cbegin(), t.cend());
    EXPECT_EQ(t.rbegin(), t.rend());
    EXPECT_EQ(t.crbegin(), t.crend());

    EXPECT_EQ(t.begin(), t.cbegin());
    EXPECT_EQ(t.end(), t.cend());
    EXPECT_EQ(t.rbegin(), t.crbegin());
    EXPECT_EQ(t.rend(), t.crend());

    EXPECT_TRUE(t.empty());
    EXPECT_EQ(t.size(), 0);
    EXPECT_EQ(t.begin(), t.end());

    EXPECT_EQ(t.max_size(), INT_MAX / 2);

    EXPECT_EQ(t.compare(t), 0);
    EXPECT_TRUE(t == t);
    EXPECT_FALSE(t != t);
    EXPECT_FALSE(t < t);
    EXPECT_TRUE(t <= t);
    EXPECT_FALSE(t > t);
    EXPECT_TRUE(t >= t);

    t.swap(t);
    EXPECT_TRUE(t == t);

    EXPECT_EQ(t.begin(), begin(t));
    EXPECT_EQ(t.end(), end(t));
    EXPECT_EQ(t.cbegin(), cbegin(t));
    EXPECT_EQ(t.cend(), cend(t));

    EXPECT_EQ(t.rbegin(), rbegin(t));
    EXPECT_EQ(t.rend(), rend(t));
    EXPECT_EQ(t.crbegin(), crbegin(t));
    EXPECT_EQ(t.crend(), crend(t));

    t.clear();
    t.resize(0, 'c');
    t.shrink_to_fit();

    std::cout << "t=\"" << t << "\"\n";

    {
        using namespace text::literals;
        text::string t2 = ""_s;
        EXPECT_TRUE(t == t2);

        text::string t3 = u8""_s;
        EXPECT_TRUE(t == t3);
    }
}

TEST(string, test_non_empty_const_interface)
{
    text::string t_a("a");
    text::string t_ab("ab");

    EXPECT_EQ(t_a.begin() + t_a.size(), t_a.end());
    EXPECT_EQ(t_a.cbegin() + t_a.size(), t_a.cend());
    EXPECT_EQ(t_a.rbegin() + t_a.size(), t_a.rend());
    EXPECT_EQ(t_a.crbegin() + t_a.size(), t_a.crend());

    EXPECT_EQ(t_a.begin(), t_a.cbegin());
    EXPECT_EQ(t_a.end(), t_a.cend());
    EXPECT_EQ(t_a.rbegin(), t_a.crbegin());
    EXPECT_EQ(t_a.rend(), t_a.crend());

    EXPECT_EQ(t_ab.begin(), t_ab.cbegin());
    EXPECT_EQ(t_ab.end(), t_ab.cend());
    EXPECT_EQ(t_ab.rbegin(), t_ab.crbegin());
    EXPECT_EQ(t_ab.rend(), t_ab.crend());

    EXPECT_FALSE(t_a.empty());
    EXPECT_EQ(t_a.size(), 1);
    EXPECT_GT(t_a.capacity(), t_a.size());
    EXPECT_NE(t_a.begin(), nullptr);

    text::string_view tv_a = t_a;
    EXPECT_EQ(tv_a, t_a);

    EXPECT_EQ(t_a, t_a(0, 1));
    EXPECT_EQ(t_a, t_a(1));
    EXPECT_EQ(t_a, t_a(-1));

    EXPECT_EQ("", t_a(1, 1));
    EXPECT_EQ("", t_a(-1, -1));

    EXPECT_FALSE(t_ab.empty());
    EXPECT_EQ(t_ab.size(), 2);
    EXPECT_GT(t_ab.capacity(), t_ab.size());
    EXPECT_NE(t_ab.begin(), nullptr);

    text::string_view tv_ab = t_ab;
    EXPECT_EQ(tv_ab, t_ab);

    EXPECT_EQ(t_ab, t_ab(0, 2));
    EXPECT_EQ(t_ab, t_ab(2));
    EXPECT_EQ(t_ab, t_ab(-2));

    EXPECT_EQ(t_ab[1], 'b');

    EXPECT_EQ(t_a.max_size(), INT_MAX / 2);
    EXPECT_EQ(t_ab.max_size(), INT_MAX / 2);

    EXPECT_EQ(t_a.compare(t_ab), -1);
    EXPECT_FALSE(t_a == t_ab);
    EXPECT_TRUE(t_a != t_ab);
    EXPECT_TRUE(t_a < t_ab);
    EXPECT_TRUE(t_a <= t_ab);
    EXPECT_FALSE(t_a > t_ab);
    EXPECT_FALSE(t_a >= t_ab);

    EXPECT_FALSE(t_a == t_ab(2));
    EXPECT_TRUE(t_a != t_ab(2));
    EXPECT_TRUE(t_a < t_ab(2));
    EXPECT_TRUE(t_a <= t_ab(2));
    EXPECT_FALSE(t_a > t_ab(2));
    EXPECT_FALSE(t_a >= t_ab(2));

    EXPECT_FALSE(t_a(1) == t_ab);
    EXPECT_TRUE(t_a(1) != t_ab);
    EXPECT_TRUE(t_a(1) < t_ab);
    EXPECT_TRUE(t_a(1) <= t_ab);
    EXPECT_FALSE(t_a(1) > t_ab);
    EXPECT_FALSE(t_a(1) >= t_ab);

    EXPECT_FALSE(t_a == "ab");
    EXPECT_TRUE(t_a != "ab");
    EXPECT_TRUE(t_a < "ab");
    EXPECT_TRUE(t_a <= "ab");
    EXPECT_FALSE(t_a > "ab");
    EXPECT_FALSE(t_a >= "ab");

    EXPECT_FALSE("a" == t_ab);
    EXPECT_TRUE("a" != t_ab);
    EXPECT_TRUE("a" < t_ab);
    EXPECT_TRUE("a" <= t_ab);
    EXPECT_FALSE("a" > t_ab);
    EXPECT_FALSE("a" >= t_ab);

    EXPECT_EQ(t_a.compare("ab"), -1);
    EXPECT_EQ(t_a, "a");

    text::string const old_t_a(t_a);
    text::string const old_t_ab(t_ab);
    t_a.swap(t_ab);
    EXPECT_EQ(t_a, old_t_ab);
    EXPECT_EQ(t_ab, old_t_a);
    t_a.swap(t_ab);

    EXPECT_EQ(t_a.begin(), begin(t_a));
    EXPECT_EQ(t_a.end(), end(t_a));
    EXPECT_EQ(t_a.cbegin(), cbegin(t_a));
    EXPECT_EQ(t_a.cend(), cend(t_a));

    EXPECT_EQ(t_a.rbegin(), rbegin(t_a));
    EXPECT_EQ(t_a.rend(), rend(t_a));
    EXPECT_EQ(t_a.crbegin(), crbegin(t_a));
    EXPECT_EQ(t_a.crend(), crend(t_a));

    {
        using namespace text::literals;
        EXPECT_EQ(t_a, "a"_s);
        EXPECT_EQ(t_ab, "ab"_s);
    }
}

TEST(string, test_ctors)
{
    text::string t;
    EXPECT_EQ(t, "");
    EXPECT_EQ("", t);

    text::string t2("A nonemtpy string");
    EXPECT_EQ(t2, "A nonemtpy string");
    EXPECT_EQ("A nonemtpy string", t2);
    EXPECT_EQ(t2[t2.size()], '\0');

    text::string t3(t2);
    EXPECT_EQ(t3, "A nonemtpy string");
    EXPECT_EQ("A nonemtpy string", t3);
    EXPECT_EQ(t3[t3.size()], '\0');

    text::string t4(std::move(t2));
    EXPECT_EQ(t4, "A nonemtpy string");
    EXPECT_EQ("A nonemtpy string", t4);
    EXPECT_EQ(t2, "");
    EXPECT_EQ("", t2);
    EXPECT_EQ(t4[t4.size()], '\0');

    std::string const s("An old-school string");
    text::string t5(s);
    EXPECT_EQ(t5, "An old-school string");
    EXPECT_EQ("An old-school string", t5);
    EXPECT_EQ(t5[t5.size()], '\0');

    text::string_view const tv("a view ");
    text::string t6(tv);
    EXPECT_EQ(t6, "a view ");
    EXPECT_EQ("a view ", t6);
    EXPECT_EQ(t6[t6.size()], '\0');

    text::repeated_string_view const rtv(tv, 3);
    text::string t7(rtv);
    EXPECT_EQ(t7, "a view a view a view ");
    EXPECT_EQ("a view a view a view ", t7);
    EXPECT_EQ(t7[t7.size()], '\0');

    std::list<char> const char_list = {'a', ' ', 'l', 'i', 's', 't'};
    text::string t8(char_list.begin(), char_list.end());
    EXPECT_EQ(t8, "a list");
    EXPECT_EQ("a list", t8);
    EXPECT_EQ(t8[t8.size()], '\0');
}

TEST(string, test_assignment)
{
    {
        text::string t;
        EXPECT_EQ(t, "");
        text::string t2("A nonemtpy string");
        EXPECT_EQ(t2, "A nonemtpy string");
        EXPECT_EQ(t2[t2.size()], '\0');

        t = t2;
        EXPECT_EQ(t, "A nonemtpy string");
        EXPECT_EQ(t[t.size()], '\0');
        EXPECT_EQ(t2, "A nonemtpy string");
        EXPECT_EQ(t[t2.size()], '\0');
    }

    {
        text::string t;
        EXPECT_EQ(t, "");
        text::string t2("A nonemtpy string");
        EXPECT_EQ(t2, "A nonemtpy string");
        EXPECT_EQ(t2[t2.size()], '\0');

        t2 = t;
        EXPECT_EQ(t, "");
        EXPECT_EQ(t2, "");
    }

    {
        text::string t("small");
        EXPECT_EQ(t, "small");
        text::string t2("A nonemtpy string");
        EXPECT_EQ(t2, "A nonemtpy string");
        EXPECT_EQ(t2[t2.size()], '\0');

        t = t2;
        EXPECT_EQ(t, "A nonemtpy string");
        EXPECT_EQ(t[t.size()], '\0');
        EXPECT_EQ(t2, "A nonemtpy string");
        EXPECT_EQ(t2[t2.size()], '\0');
    }

    {
        text::string t("small");
        EXPECT_EQ(t, "small");
        EXPECT_EQ(t[t.size()], '\0');
        text::string t2("A nonemtpy string");
        EXPECT_EQ(t2, "A nonemtpy string");
        EXPECT_EQ(t2[t2.size()], '\0');

        t2 = t;
        EXPECT_EQ(t, "small");
        EXPECT_EQ(t[t.size()], '\0');
        EXPECT_EQ(t2, "small");
        EXPECT_EQ(t2[t2.size()], '\0');
    }

    {
        text::string t;
        EXPECT_EQ(t, "");
        text::string t2;
        EXPECT_EQ(t2, "");

        t = t2;
        EXPECT_EQ(t, "");
        EXPECT_EQ(t2, "");
    }

    {
        text::string t;
        EXPECT_EQ(t, "");
        text::string t2;
        EXPECT_EQ(t2, "");

        t2 = t;
        EXPECT_EQ(t, "");
        EXPECT_EQ(t2, "");
    }

    {
        text::string t;
        EXPECT_EQ(t, "");
        text::string t2("A nonemtpy string");
        EXPECT_EQ(t2, "A nonemtpy string");
        EXPECT_EQ(t2[t2.size()], '\0');

        t = std::move(t2);
        EXPECT_EQ(t, "A nonemtpy string");
        EXPECT_EQ(t2, "");
        EXPECT_EQ(t[t.size()], '\0');
    }

    {
        text::string t;
        EXPECT_EQ(t, "");
        text::string t2("A nonemtpy string");
        EXPECT_EQ(t2, "A nonemtpy string");
        EXPECT_EQ(t2[t2.size()], '\0');

        t2 = std::move(t);
        EXPECT_EQ(t, "A nonemtpy string");
        EXPECT_EQ(t[t.size()], '\0');
        EXPECT_EQ(t2, "");
    }

    {
        std::string const s("An old-school string");
        text::string t;
        t = s;
        EXPECT_EQ(t, "An old-school string");
        EXPECT_EQ(t[t.size()], '\0');
    }

    {
        text::string_view const tv("a view ");
        text::string t;
        t = tv;
        EXPECT_EQ(t, "a view ");
        EXPECT_EQ(t[t.size()], '\0');

        text::repeated_string_view const rtv(tv, 3);
        text::string t2;
        t2 = rtv;
        EXPECT_EQ(t2, "a view a view a view ");
        EXPECT_EQ(t2[t2.size()], '\0');
    }

    {
        text::string t("small");
        EXPECT_EQ(t, "small");

        t = t(0, t.size());
        EXPECT_EQ(t, "small");
    }

    {
        text::string t("small");
        EXPECT_EQ(t, "small");

        t = t(2, t.size());
        EXPECT_EQ(t, "all");
    }

    {
        text::string t("small");
        EXPECT_EQ(t, "small");

        t = t(0, t.size() - 2);
        EXPECT_EQ(t, "sma");
    }

    {
        text::string t("small");
        EXPECT_EQ(t, "small");

        t = t(1, t.size() - 1);
        EXPECT_EQ(t, "mal");
    }
}

TEST(string, test_iterators_and_index)
{
    text::string empty;
    int size = 0;
    for (auto c : empty) {
        (void)c;
        ++size;
    }
    EXPECT_EQ(size, 0);

    {
        text::string::iterator first = empty.begin();
        text::string::iterator last = empty.end();
        while (first != last) {
            ++size;
            ++first;
        }
        EXPECT_EQ(size, 0);
    }

    {
        text::string::const_iterator first = empty.cbegin();
        text::string::const_iterator last = empty.cend();
        while (first != last) {
            ++size;
            ++first;
        }
        EXPECT_EQ(size, 0);
    }

    EXPECT_EQ(empty.begin(), empty.cbegin());
    EXPECT_EQ(empty.end(), empty.cend());

    {
        text::string::reverse_iterator first = empty.rbegin();
        text::string::reverse_iterator last = empty.rend();
        while (first != last) {
            ++size;
            ++first;
        }
        EXPECT_EQ(size, 0);
    }

    {
        text::string::const_reverse_iterator first = empty.crbegin();
        text::string::const_reverse_iterator last = empty.crend();
        while (first != last) {
            ++size;
            ++first;
        }
        EXPECT_EQ(size, 0);
    }

    EXPECT_EQ(empty.rbegin(), empty.crbegin());
    EXPECT_EQ(empty.rend(), empty.crend());

    text::string non_empty("non-empty");

    {
        text::string::iterator it = non_empty.begin();
        text::string::const_iterator c_it = non_empty.cbegin();

        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, 'n');
        ++it;
        ++c_it;
        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, 'o');
        ++it;
        ++c_it;
        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, 'n');
        ++it;
        ++c_it;
        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, '-');
        ++it;
        ++c_it;
        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, 'e');
        ++it;
        ++c_it;
        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, 'm');
        ++it;
        ++c_it;
        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, 'p');
        ++it;
        ++c_it;
        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, 't');
        ++it;
        ++c_it;
        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, 'y');
        ++it;
        ++c_it;

        EXPECT_EQ(it, c_it);
        EXPECT_EQ(it, non_empty.end());
        EXPECT_EQ(c_it, non_empty.cend());
    }

    {
        text::string::reverse_iterator it = non_empty.rbegin();
        text::string::const_reverse_iterator c_it = non_empty.crbegin();

        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, 'y');
        ++it;
        ++c_it;
        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, 't');
        ++it;
        ++c_it;
        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, 'p');
        ++it;
        ++c_it;
        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, 'm');
        ++it;
        ++c_it;
        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, 'e');
        ++it;
        ++c_it;
        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, '-');
        ++it;
        ++c_it;
        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, 'n');
        ++it;
        ++c_it;
        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, 'o');
        ++it;
        ++c_it;
        EXPECT_EQ(it, c_it);
        EXPECT_EQ(*it, 'n');
        ++it;
        ++c_it;

        EXPECT_EQ(it, c_it);
        EXPECT_EQ(it, non_empty.rend());
        EXPECT_EQ(c_it, non_empty.crend());
    }

    {
        std::vector<char> vec;

        text::string::reverse_iterator const r_it_begin = non_empty.rbegin();
        text::string::reverse_iterator const r_it_end = non_empty.rend();

        text::string::reverse_iterator r_it = r_it_begin;
        while (r_it != r_it_end) {
            vec.push_back(*r_it);
            ++r_it;
        }

        std::reverse(vec.begin(), vec.end());
        EXPECT_TRUE(algorithm::equal(
            r_it_end.base(), r_it_begin.base(), vec.begin(), vec.end()));
    }
}

TEST(string, test_misc)
{
    {
        text::string t("some text");
        EXPECT_EQ(t[t.size()], '\0');
        int const cap = t.capacity();
        t.clear();
        EXPECT_EQ(t.size(), 0);
        EXPECT_EQ(t.capacity(), cap);
    }

    {
        text::string t("some text");
        EXPECT_EQ(t[t.size()], '\0');
        int const cap = t.capacity();
        t.resize(0, 'c');
        EXPECT_EQ(t.size(), 0);
        EXPECT_EQ(t.capacity(), cap);
    }

    {
        text::string t("some text");
        EXPECT_EQ(t[t.size()], '\0');
        int const cap = t.capacity();
        t.resize(4, 'c');
        EXPECT_EQ(t.size(), 4);
        EXPECT_EQ(t.capacity(), cap);
        EXPECT_EQ(t[t.size()], '\0');
    }

    {
        text::string t("some text");
        EXPECT_EQ(t[t.size()], '\0');
        t.resize(12, 'c');
        EXPECT_EQ(t.size(), 12);
        EXPECT_EQ(t, "some textccc");
        EXPECT_EQ(t[t.size()], '\0');
    }

    {
        text::string t("some text");
        EXPECT_EQ(t[t.size()], '\0');
        t.reserve(153);
        EXPECT_EQ(t.capacity(), 153);
        EXPECT_EQ(t, "some text");
        EXPECT_EQ(t[t.size()], '\0');
    }

    {
        text::string t("some text");
        EXPECT_EQ(t[t.size()], '\0');
        t.reserve(153);
        EXPECT_EQ(t.capacity(), 153);
        EXPECT_EQ(t, "some text");
        EXPECT_EQ(t[t.size()], '\0');
        t.shrink_to_fit();
        EXPECT_EQ(t.capacity(), 9);
        EXPECT_EQ(t, "some text");
        EXPECT_EQ(t[t.size()], '\0');
    }

    {
        text::string t1("some");
        EXPECT_EQ(t1[t1.size()], '\0');
        text::string t2("text");
        EXPECT_EQ(t2[t2.size()], '\0');
        t1.swap(t2);
        EXPECT_EQ(t1, "text");
        EXPECT_EQ(t1[t1.size()], '\0');
        EXPECT_EQ(t2, "some");
        EXPECT_EQ(t2[t2.size()], '\0');
    }
}


TEST(string, test_insert)
{
    text::string_view const tv("a view ");
    text::repeated_string_view const rtv(tv, 3);

    int const sbo_capacity = sizeof(char *) == 8 ? 15 : 7;

    {
        text::string const ct("string");

        text::string t0 = ct;
        EXPECT_EQ(t0.capacity(), sbo_capacity);
        t0.insert(0, tv);
        EXPECT_EQ(t0, "a view string");
        EXPECT_EQ(t0[t0.size()], '\0');

        text::string t1 = ct;
        EXPECT_EQ(t1.capacity(), sbo_capacity);
        t1.insert(1, tv);
        EXPECT_EQ(t1, "sa view tring");
        EXPECT_EQ(t1[t1.size()], '\0');

        text::string t2 = ct;
        EXPECT_EQ(t2.capacity(), sbo_capacity);
        t2.insert(2, tv);
        EXPECT_EQ(t2, "sta view ring");
        EXPECT_EQ(t2[t2.size()], '\0');

        text::string t3 = ct;
        EXPECT_EQ(t3.capacity(), sbo_capacity);
        t3.insert(3, tv);
        EXPECT_EQ(t3, "stra view ing");
        EXPECT_EQ(t3[t3.size()], '\0');

        text::string t4 = ct;
        EXPECT_EQ(t4.capacity(), sbo_capacity);
        t4.insert(4, tv);
        EXPECT_EQ(t4, "stria view ng");
        EXPECT_EQ(t4[t4.size()], '\0');

        text::string t5 = ct;
        EXPECT_EQ(t5.capacity(), sbo_capacity);
        t5.insert(5, tv);
        EXPECT_EQ(t5, "strina view g");
        EXPECT_EQ(t5[t5.size()], '\0');

        text::string t6 = ct;
        EXPECT_EQ(t6.capacity(), sbo_capacity);
        t6.insert(6, tv);
        EXPECT_EQ(t6, "stringa view ");
        EXPECT_EQ(t6[t6.size()], '\0');

        text::string t7 = ct;
        EXPECT_EQ(t7.capacity(), sbo_capacity);
        t7.insert(6, t7(0, 3));
        EXPECT_EQ(t7, "stringstr");
        EXPECT_EQ(t7[t7.size()], '\0');

        text::string t8 = ct;
        EXPECT_EQ(t8.capacity(), sbo_capacity);
        t8.insert(2, t8(0, 3));
        EXPECT_EQ(t8, "ststrring");
        EXPECT_EQ(t8[t8.size()], '\0');

        text::string t9 = ct;
        EXPECT_EQ(t9.capacity(), sbo_capacity);
        t9.insert(6, t9(3, 6));
        EXPECT_EQ(t9, "stringing");
        EXPECT_EQ(t9[t9.size()], '\0');
    }

    {
        text::string const ct("string");

        text::string t0 = ct;
        EXPECT_EQ(t0.capacity(), sbo_capacity);
        t0.insert(0, rtv);
        EXPECT_EQ(t0, "a view a view a view string");
        EXPECT_EQ(t0[t0.size()], '\0');

        text::string t1 = ct;
        EXPECT_EQ(t1.capacity(), sbo_capacity);
        t1.insert(1, rtv);
        EXPECT_EQ(t1, "sa view a view a view tring");
        EXPECT_EQ(t1[t1.size()], '\0');

        text::string t2 = ct;
        EXPECT_EQ(t2.capacity(), sbo_capacity);
        t2.insert(2, rtv);
        EXPECT_EQ(t2, "sta view a view a view ring");
        EXPECT_EQ(t2[t2.size()], '\0');

        text::string t3 = ct;
        EXPECT_EQ(t3.capacity(), sbo_capacity);
        t3.insert(3, rtv);
        EXPECT_EQ(t3, "stra view a view a view ing");
        EXPECT_EQ(t3[t3.size()], '\0');

        text::string t4 = ct;
        EXPECT_EQ(t4.capacity(), sbo_capacity);
        t4.insert(4, rtv);
        EXPECT_EQ(t4, "stria view a view a view ng");
        EXPECT_EQ(t4[t4.size()], '\0');

        text::string t5 = ct;
        EXPECT_EQ(t5.capacity(), sbo_capacity);
        t5.insert(5, rtv);
        EXPECT_EQ(t5, "strina view a view a view g");
        EXPECT_EQ(t5[t5.size()], '\0');

        text::string t6 = ct;
        EXPECT_EQ(t6.capacity(), sbo_capacity);
        t6.insert(6, rtv);
        EXPECT_EQ(t6, "stringa view a view a view ");
        EXPECT_EQ(t6[t6.size()], '\0');

        text::string t7 = ct;
        EXPECT_EQ(t7.capacity(), sbo_capacity);
        t7.insert(6, text::repeated_string_view(t7(0, 3), 2));
        EXPECT_EQ(t7, "stringstrstr");
        EXPECT_EQ(t7[t7.size()], '\0');

        text::string t8 = ct;
        EXPECT_EQ(t8.capacity(), sbo_capacity);
        t8.insert(2, text::repeated_string_view(t8(0, 3), 2));
        EXPECT_EQ(t8, "ststrstrring");
        EXPECT_EQ(t8[t8.size()], '\0');

        text::string t9 = ct;
        EXPECT_EQ(t9.capacity(), sbo_capacity);
        t9.insert(6, text::repeated_string_view(t9(3, 6), 2));
        EXPECT_EQ(t9, "stringinging");
        EXPECT_EQ(t9[t9.size()], '\0');
    }

    // Unicode 9, 3.9/D90
    uint32_t const utf32[] = {0x004d, 0x0430, 0x4e8c, 0x10302};

    {
        text::string const ct("string");
        auto const first = text::utf_32_to_8_iterator<uint32_t const *>(
            utf32, utf32, utf32 + 4);
        auto const last = text::utf_32_to_8_iterator<uint32_t const *>(
            utf32, utf32 + 4, utf32 + 4);

        text::string t0 = ct;
        EXPECT_EQ(t0.capacity(), sbo_capacity);
        t0.insert(0, first, last);
        EXPECT_EQ(t0, "\x4d\xd0\xb0\xe4\xba\x8c\xf0\x90\x8c\x82string");
        EXPECT_EQ(t0[t0.size()], '\0');

        text::string t1 = ct;
        EXPECT_EQ(t1.capacity(), sbo_capacity);
        t1.insert(1, first, last);
        EXPECT_EQ(t1, "s\x4d\xd0\xb0\xe4\xba\x8c\xf0\x90\x8c\x82tring");
        EXPECT_EQ(t1[t1.size()], '\0');

        text::string t2 = ct;
        EXPECT_EQ(t2.capacity(), sbo_capacity);
        t2.insert(2, first, last);
        EXPECT_EQ(t2, "st\x4d\xd0\xb0\xe4\xba\x8c\xf0\x90\x8c\x82ring");
        EXPECT_EQ(t2[t2.size()], '\0');

        text::string t3 = ct;
        EXPECT_EQ(t3.capacity(), sbo_capacity);
        t3.insert(3, first, last);
        EXPECT_EQ(t3, "str\x4d\xd0\xb0\xe4\xba\x8c\xf0\x90\x8c\x82ing");
        EXPECT_EQ(t3[t3.size()], '\0');

        text::string t4 = ct;
        EXPECT_EQ(t4.capacity(), sbo_capacity);
        t4.insert(4, first, last);
        EXPECT_EQ(t4, "stri\x4d\xd0\xb0\xe4\xba\x8c\xf0\x90\x8c\x82ng");
        EXPECT_EQ(t4[t4.size()], '\0');

        text::string t5 = ct;
        EXPECT_EQ(t5.capacity(), sbo_capacity);
        t5.insert(5, first, last);
        EXPECT_EQ(t5, "strin\x4d\xd0\xb0\xe4\xba\x8c\xf0\x90\x8c\x82g");
        EXPECT_EQ(t5[t5.size()], '\0');

        text::string t6 = ct;
        EXPECT_EQ(t6.capacity(), sbo_capacity);
        t6.insert(6, first, last);
        EXPECT_EQ(t6, "string\x4d\xd0\xb0\xe4\xba\x8c\xf0\x90\x8c\x82");
        EXPECT_EQ(t6[t6.size()], '\0');
    }

    {
        char const * str = "";
        text::string_view const tv(str, 1); // explicitly null-terminated
        text::repeated_string_view const rtv(tv, 3);

        {
            text::string t("text");
            t.insert(2, tv);
            EXPECT_EQ(t, "text"); // no null in the middle
            EXPECT_EQ(t[t.size()], '\0');
        }

        {
            text::string t("text");
            t.insert(2, rtv);
            EXPECT_EQ(t, "text"); // no nulls in the middle
            EXPECT_EQ(t[t.size()], '\0');
        }
    }
}

TEST(string, test_erase)
{
    {
        text::string t("string");
        text::string_view const ctv(
            t.begin(), t.size() + 1); // Explicitly null-terminated.
        t.erase(ctv);
        EXPECT_EQ(t, "");
        EXPECT_EQ(t[t.size()], '\0');
    }

    text::string const ct("string");

    for (int j = 0; j <= ct.size(); ++j) {
        for (int i = 0; i <= j; ++i) {
            text::string t = ct;
            text::string_view const before = t(0, i);
            text::string_view const substr = t(i, j);
            text::string_view const after = t(j, t.size());

            text::string expected(before);
            expected += after;

            t.erase(substr);
            EXPECT_EQ(t[t.size()], '\0')
                << "i=" << i << " j=" << j << " erasing '" << substr << "'";
            EXPECT_EQ(t, expected)
                << "i=" << i << " j=" << j << " erasing '" << substr << "'";
        }
    }
}

TEST(string, test_replace)
{
    text::string_view const replacement("REP");
    // Explicitly null-terminated.
    text::string_view const replacement_with_null(
        replacement.begin(), replacement.size() + 1);

    {
        text::string t("string");
        text::string_view const ctv(
            t.begin(), t.size() + 1); // Explicitly null-terminated.
        t.replace(ctv, replacement_with_null);
        EXPECT_EQ(t, "REP");
        EXPECT_EQ(t[t.size()], '\0');
    }

    {
        text::string t("string");
        text::string_view const ctv(
            t.begin(), t.size() + 1); // Explicitly null-terminated.
        t.replace(ctv, replacement);
        EXPECT_EQ(t, "REP");
        EXPECT_EQ(t[t.size()], '\0');
    }

    {
        text::string t("string");
        t.replace(t, replacement);
        EXPECT_EQ(t, "REP");
        EXPECT_EQ(t[t.size()], '\0');
    }

    {
        text::string t("string");
        t.replace(t(0, 3), t(2, 6));
        EXPECT_EQ(t, "ringing");
        EXPECT_EQ(t[t.size()], '\0');
    }

    {
        text::string t("string");
        t.replace(t(3, 6), t(0, 3));
        EXPECT_EQ(t, "strstr");
        EXPECT_EQ(t[t.size()], '\0');
    }

    text::string const ct("string");

    for (int j = 0; j <= ct.size(); ++j) {
        for (int i = 0; i <= j; ++i) {
            text::string t = ct;
            text::string_view const before = t(0, i);
            text::string_view const substr = t(i, j);
            text::string_view const after = t(j, t.size());

            text::string expected(before);
            expected += replacement;
            expected += after;

            t.replace(substr, replacement);
            EXPECT_EQ(t[t.size()], '\0')
                << "i=" << i << " j=" << j << " erasing '" << substr << "'";
            EXPECT_EQ(t, expected)
                << "i=" << i << " j=" << j << " erasing '" << substr << "'";
        }
    }

    text::repeated_string_view const really_long_replacement(replacement, 10);

    for (int j = 0; j <= ct.size(); ++j) {
        for (int i = 0; i <= j; ++i) {
            text::string t = ct;
            text::string_view const before = t(0, i);
            text::string_view const substr = t(i, j);
            text::string_view const after = t(j, t.size());

            text::string expected(before);
            expected += really_long_replacement;
            expected += after;

            t.replace(substr, really_long_replacement);
            EXPECT_EQ(t[t.size()], '\0')
                << "i=" << i << " j=" << j << " erasing '" << substr << "'";
            EXPECT_EQ(t, expected)
                << "i=" << i << " j=" << j << " erasing '" << substr << "'";
        }
    }
}

TEST(string, test_replace_iter)
{
    // Unicode 9, 3.9/D90
    uint32_t const utf32[] = {0x004d, 0x0430, 0x4e8c, 0x10302};
    auto const first =
        text::utf_32_to_8_iterator<uint32_t const *>(utf32, utf32, utf32 + 4);
    auto const final_cp = text::utf_32_to_8_iterator<uint32_t const *>(
        utf32, utf32 + 3, utf32 + 4);
    auto const last = text::utf_32_to_8_iterator<uint32_t const *>(
        utf32, utf32 + 4, utf32 + 4);

    text::string const ct_string("string");
    text::string const ct_text("text");

    {
        text::string t = ct_string;
        t.replace(t, final_cp, last);
        EXPECT_EQ(t, "\xf0\x90\x8c\x82");
        EXPECT_EQ(t[t.size()], '\0');
    }

    {
        text::string t = ct_text;
        t.replace(t, final_cp, last);
        EXPECT_EQ(t, "\xf0\x90\x8c\x82");
        EXPECT_EQ(t[t.size()], '\0');
    }

    {
        text::string t = ct_string;
        t.replace(t, first, last);
        EXPECT_EQ(t, "\x4d\xd0\xb0\xe4\xba\x8c\xf0\x90\x8c\x82");
        EXPECT_EQ(t[t.size()], '\0');
    }

    for (int j = 0; j <= ct_string.size(); ++j) {
        for (int i = 0; i <= j; ++i) {
            {
                text::string t = ct_string;
                text::string_view const before = t(0, i);
                text::string_view const substr = t(i, j);
                text::string_view const after = t(j, t.size());

                text::string expected(before);
                expected.insert(expected.size(), final_cp, last);
                expected += after;

                t.replace(substr, final_cp, last);
                EXPECT_EQ(t[t.size()], '\0')
                    << "i=" << i << " j=" << j << " erasing '" << substr << "'";
                EXPECT_EQ(t, expected)
                    << "i=" << i << " j=" << j << " erasing '" << substr << "'";
            }

            {
                text::string t = ct_string;
                text::string_view const before = t(0, i);
                text::string_view const substr = t(i, j);
                text::string_view const after = t(j, t.size());

                text::string expected(before);
                expected.insert(expected.size(), first, last);
                expected += after;

                t.replace(substr, first, last);
                EXPECT_EQ(t[t.size()], '\0')
                    << "i=" << i << " j=" << j << " erasing '" << substr << "'";
                EXPECT_EQ(t, expected)
                    << "i=" << i << " j=" << j << " erasing '" << substr << "'";
            }
        }
    }
}

TEST(string, test_replace_iter_large_insertions)
{
    // Unicode 9, 3.9/D90
    uint32_t const utf32[] = {0x004d, 0x0430, 0x4e8c, 0x10302};

    std::vector<uint32_t> utf32_repeated;
    for (int i = 0; i < 5000; ++i) {
        utf32_repeated.insert(utf32_repeated.end(), utf32, utf32 + 4);
    }
    auto const first =
        text::utf_32_to_8_iterator<std::vector<uint32_t>::iterator>(
            utf32_repeated.begin(),
            utf32_repeated.begin(),
            utf32_repeated.end());
    auto const last =
        text::utf_32_to_8_iterator<std::vector<uint32_t>::iterator>(
            utf32_repeated.begin(), utf32_repeated.end(), utf32_repeated.end());

    {
        text::string t("string");
        t.replace(t, first, last);
        text::string const expected(first, last);
        EXPECT_EQ(t, expected);
    }

    {
        text::string t;
        t.replace(t, first, last);
        text::string const expected(first, last);
        EXPECT_EQ(t, expected);
    }
}

TEST(string, test_unformatted_output)
{
    {
        std::ostringstream oss;
        oss << std::setw(10) << text::string("abc");
        EXPECT_EQ(oss.str(), "abc");
    }

    {
        std::ostringstream oss;
        oss << std::setw(10) << std::left << std::setfill('*')
            << text::string("abc");
        EXPECT_EQ(oss.str(), "abc");
    }
}

TEST(string, test_sentinel_api)
{
    {
        char const * chars = "chars";
        text::string s(chars, text::null_sentinel{});
        EXPECT_EQ(s, chars);
    }
    {
        char const * chars = "chars";
        text::string s;
        s.insert(0, chars, text::null_sentinel{});
        EXPECT_EQ(s, chars);
    }
    {
        char const * chars = "chars";
        text::string s;
        s.insert(s.end(), chars, text::null_sentinel{});
        EXPECT_EQ(s, chars);
    }
    {
        char const * chars = "chars";
        text::string s;
        s.replace(s(0, 0), chars, text::null_sentinel{});
        EXPECT_EQ(s, chars);
    }
    {
        char const * chars = "chars";
        text::string s;
        s.replace(s.begin(), s.begin(), chars, text::null_sentinel{});
        EXPECT_EQ(s, chars);
    }
}
