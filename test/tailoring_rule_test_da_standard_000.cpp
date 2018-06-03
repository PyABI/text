
// Warning! This file is autogenerated.
#include <boost/text/collation_table.hpp>
#include <boost/text/collate.hpp>
#include <boost/text/save_load_table.hpp>
#include <boost/text/data/all.hpp>

#include <boost/filesystem.hpp>

#include <gtest/gtest.h>

using namespace boost::text;

auto const error = [](string const & s) { std::cout << s; };
auto const warning = [](string const & s) {};

collation_table make_save_load_table()
{
    if (!exists(boost::filesystem::path("da_standard.table"))) {
        string const table_str(data::da::standard_collation_tailoring());
        collation_table table = tailored_collation_table(
            table_str,
            "da::standard_collation_tailoring()", error, warning);
        save_table(table, "da_standard.table.0");
        boost::filesystem::rename("da_standard.table.0", "da_standard.table");
    }
    return load_table("da_standard.table");
}
collation_table const & table()
{
    static collation_table retval = make_save_load_table();
    return retval;
}
TEST(tailoring, da_standard_000_001)
{
    // greater than (or equal to, for =) preceeding cps
    EXPECT_EQ(collate(
        std::vector<uint32_t>(1, 0x0044),
        std::vector<uint32_t>(1, 0x0111),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        std::vector<uint32_t>(1, 0x0044),
        std::vector<uint32_t>(1, 0x0111),
        table(), collation_strength::primary),
        0);
#if 0 // Now that caseFirst is implemented, this is too simplistic.
    // greater than (or equal to, for =) preceeding cps
    EXPECT_EQ(collate(
        std::vector<uint32_t>(1, 0x0111),
        std::vector<uint32_t>(1, 0x0110),
        table(), collation_strength::tertiary),
        -1);
#endif
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        std::vector<uint32_t>(1, 0x0111),
        std::vector<uint32_t>(1, 0x0110),
        table(), collation_strength::secondary),
        0);
    // greater than (or equal to, for =) preceeding cps
    EXPECT_EQ(collate(
        std::vector<uint32_t>(1, 0x0110),
        std::vector<uint32_t>(1, 0x00f0),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        std::vector<uint32_t>(1, 0x0110),
        std::vector<uint32_t>(1, 0x00f0),
        table(), collation_strength::primary),
        0);
#if 0 // Now that caseFirst is implemented, this is too simplistic.
    // greater than (or equal to, for =) preceeding cps
    EXPECT_EQ(collate(
        std::vector<uint32_t>(1, 0x00f0),
        std::vector<uint32_t>(1, 0x00d0),
        table(), collation_strength::tertiary),
        -1);
#endif
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        std::vector<uint32_t>(1, 0x00f0),
        std::vector<uint32_t>(1, 0x00d0),
        table(), collation_strength::secondary),
        0);
    // greater than (or equal to, for =) preceeding cps
    EXPECT_EQ(collate(
        std::vector<uint32_t>{0x0074, 0x0068},
        std::vector<uint32_t>(1, 0x00fe),
        table(), collation_strength::tertiary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        std::vector<uint32_t>{0x0074, 0x0068},
        std::vector<uint32_t>(1, 0x00fe),
        table(), collation_strength::secondary),
        0);
    // greater than (or equal to, for =) preceeding cps
    EXPECT_EQ(collate(
        std::vector<uint32_t>{0x0054, 0x0048},
        std::vector<uint32_t>(1, 0x00de),
        table(), collation_strength::tertiary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        std::vector<uint32_t>{0x0054, 0x0048},
        std::vector<uint32_t>(1, 0x00de),
        table(), collation_strength::secondary),
        0);
#if 0 // Now that caseFirst is implemented, this is too simplistic.
    // greater than (or equal to, for =) preceeding cps
    EXPECT_EQ(collate(
        std::vector<uint32_t>(1, 0x0059),
        std::vector<uint32_t>{0x0075, 0x0308},
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        std::vector<uint32_t>(1, 0x0059),
        std::vector<uint32_t>{0x0075, 0x0308},
        table(), collation_strength::primary),
        0);
    // greater than (or equal to, for =) preceeding cps
    EXPECT_EQ(collate(
        std::vector<uint32_t>{0x0075, 0x0308},
        std::vector<uint32_t>{0x0055, 0x0308},
        table(), collation_strength::tertiary),
        -1);
#endif
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        std::vector<uint32_t>{0x0075, 0x0308},
        std::vector<uint32_t>{0x0055, 0x0308},
        table(), collation_strength::secondary),
        0);
    // greater than (or equal to, for =) preceeding cps
    EXPECT_EQ(collate(
        std::vector<uint32_t>{0x0055, 0x0308},
        std::vector<uint32_t>{0x0075, 0x030b},
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        std::vector<uint32_t>{0x0055, 0x0308},
        std::vector<uint32_t>{0x0075, 0x030b},
        table(), collation_strength::primary),
        0);
#if 0 // Now that caseFirst is implemented, this is too simplistic.
    // greater than (or equal to, for =) preceeding cps
    EXPECT_EQ(collate(
        std::vector<uint32_t>{0x0075, 0x030b},
        std::vector<uint32_t>{0x0055, 0x030b},
        table(), collation_strength::tertiary),
        -1);
#endif
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        std::vector<uint32_t>{0x0075, 0x030b},
        std::vector<uint32_t>{0x0055, 0x030b},
        table(), collation_strength::secondary),
        0);
    // greater than (or equal to, for =) preceeding cps
    EXPECT_EQ(collate(
        std::vector<uint32_t>{0x006f, 0x0065},
        std::vector<uint32_t>(1, 0x0153),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        std::vector<uint32_t>{0x006f, 0x0065},
        std::vector<uint32_t>(1, 0x0153),
        table(), collation_strength::primary),
        0);
#if 0 // Now that caseFirst is implemented, this is too simplistic.
    // greater than (or equal to, for =) preceeding cps
    EXPECT_EQ(collate(
        std::vector<uint32_t>(1, 0x0153),
        std::vector<uint32_t>(1, 0x0152),
        table(), collation_strength::tertiary),
        -1);
#endif
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        std::vector<uint32_t>(1, 0x0153),
        std::vector<uint32_t>(1, 0x0152),
        table(), collation_strength::secondary),
        0);
}
