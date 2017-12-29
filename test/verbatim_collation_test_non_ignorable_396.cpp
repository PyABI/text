// Warning! This file is autogenerated.
#include "collation_tests.hpp"

#include <boost/algorithm/cxx14/equal.hpp>

#include <gtest/gtest.h>



TEST(collation, non_ignorable_396_000)
{
    // 10FF04 003F;	
    // ('\U0010FF04') <private-use-10FF04>	[FBE1 FF04 0267 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FF04, 0x003F };
    uint32_t const ces[10] = { 0xFBE1, 0xFF04, 0x0267, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_001)
{
    // 10FF04 0061;	
    // ('\U0010FF04') <private-use-10FF04>	[FBE1 FF04 1CAD | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FF04, 0x0061 };
    uint32_t const ces[10] = { 0xFBE1, 0xFF04, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_002)
{
    // 10FF04 0041;	
    // ('\U0010FF04') <private-use-10FF04>	[FBE1 FF04 1CAD | 0020 0020 | 0002 0008 |]

    uint32_t cps[2] = { 0x10FF04, 0x0041 };
    uint32_t const ces[10] = { 0xFBE1, 0xFF04, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0008, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_003)
{
    // 10FF04 0062;	
    // ('\U0010FF04') <private-use-10FF04>	[FBE1 FF04 1CC6 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FF04, 0x0062 };
    uint32_t const ces[10] = { 0xFBE1, 0xFF04, 0x1CC6, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_004)
{
    // 10FF05 0021;	
    // ('\U0010FF05') <private-use-10FF05>	[FBE1 FF05 0261 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FF05, 0x0021 };
    uint32_t const ces[10] = { 0xFBE1, 0xFF05, 0x0261, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_005)
{
    // 10FF05 003F;	
    // ('\U0010FF05') <private-use-10FF05>	[FBE1 FF05 0267 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FF05, 0x003F };
    uint32_t const ces[10] = { 0xFBE1, 0xFF05, 0x0267, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_006)
{
    // 10FF05 0061;	
    // ('\U0010FF05') <private-use-10FF05>	[FBE1 FF05 1CAD | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FF05, 0x0061 };
    uint32_t const ces[10] = { 0xFBE1, 0xFF05, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_007)
{
    // 10FF05 0041;	
    // ('\U0010FF05') <private-use-10FF05>	[FBE1 FF05 1CAD | 0020 0020 | 0002 0008 |]

    uint32_t cps[2] = { 0x10FF05, 0x0041 };
    uint32_t const ces[10] = { 0xFBE1, 0xFF05, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0008, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_008)
{
    // 10FF05 0062;	
    // ('\U0010FF05') <private-use-10FF05>	[FBE1 FF05 1CC6 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FF05, 0x0062 };
    uint32_t const ces[10] = { 0xFBE1, 0xFF05, 0x1CC6, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_009)
{
    // 10FFF8 0021;	
    // ('\U0010FFF8') <private-use-10FFF8>	[FBE1 FFF8 0261 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFF8, 0x0021 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFF8, 0x0261, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_010)
{
    // 10FFF8 003F;	
    // ('\U0010FFF8') <private-use-10FFF8>	[FBE1 FFF8 0267 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFF8, 0x003F };
    uint32_t const ces[10] = { 0xFBE1, 0xFFF8, 0x0267, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_011)
{
    // 10FFF8 0061;	
    // ('\U0010FFF8') <private-use-10FFF8>	[FBE1 FFF8 1CAD | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFF8, 0x0061 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFF8, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_012)
{
    // 10FFF8 0041;	
    // ('\U0010FFF8') <private-use-10FFF8>	[FBE1 FFF8 1CAD | 0020 0020 | 0002 0008 |]

    uint32_t cps[2] = { 0x10FFF8, 0x0041 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFF8, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0008, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_013)
{
    // 10FFF8 0062;	
    // ('\U0010FFF8') <private-use-10FFF8>	[FBE1 FFF8 1CC6 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFF8, 0x0062 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFF8, 0x1CC6, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_014)
{
    // 10FFF9 0021;	
    // ('\U0010FFF9') <private-use-10FFF9>	[FBE1 FFF9 0261 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFF9, 0x0021 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFF9, 0x0261, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_015)
{
    // 10FFF9 003F;	
    // ('\U0010FFF9') <private-use-10FFF9>	[FBE1 FFF9 0267 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFF9, 0x003F };
    uint32_t const ces[10] = { 0xFBE1, 0xFFF9, 0x0267, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_016)
{
    // 10FFF9 0061;	
    // ('\U0010FFF9') <private-use-10FFF9>	[FBE1 FFF9 1CAD | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFF9, 0x0061 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFF9, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_017)
{
    // 10FFF9 0041;	
    // ('\U0010FFF9') <private-use-10FFF9>	[FBE1 FFF9 1CAD | 0020 0020 | 0002 0008 |]

    uint32_t cps[2] = { 0x10FFF9, 0x0041 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFF9, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0008, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_018)
{
    // 10FFF9 0062;	
    // ('\U0010FFF9') <private-use-10FFF9>	[FBE1 FFF9 1CC6 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFF9, 0x0062 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFF9, 0x1CC6, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_019)
{
    // 10FFFA 0021;	
    // ('\U0010FFFA') <private-use-10FFFA>	[FBE1 FFFA 0261 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFA, 0x0021 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFA, 0x0261, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_020)
{
    // 10FFFA 003F;	
    // ('\U0010FFFA') <private-use-10FFFA>	[FBE1 FFFA 0267 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFA, 0x003F };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFA, 0x0267, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_021)
{
    // 10FFFA 0061;	
    // ('\U0010FFFA') <private-use-10FFFA>	[FBE1 FFFA 1CAD | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFA, 0x0061 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFA, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_022)
{
    // 10FFFA 0041;	
    // ('\U0010FFFA') <private-use-10FFFA>	[FBE1 FFFA 1CAD | 0020 0020 | 0002 0008 |]

    uint32_t cps[2] = { 0x10FFFA, 0x0041 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFA, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0008, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_023)
{
    // 10FFFA 0062;	
    // ('\U0010FFFA') <private-use-10FFFA>	[FBE1 FFFA 1CC6 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFA, 0x0062 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFA, 0x1CC6, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_024)
{
    // 10FFFB 0021;	
    // ('\U0010FFFB') <private-use-10FFFB>	[FBE1 FFFB 0261 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFB, 0x0021 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFB, 0x0261, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_025)
{
    // 10FFFB 003F;	
    // ('\U0010FFFB') <private-use-10FFFB>	[FBE1 FFFB 0267 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFB, 0x003F };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFB, 0x0267, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_026)
{
    // 10FFFB 0061;	
    // ('\U0010FFFB') <private-use-10FFFB>	[FBE1 FFFB 1CAD | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFB, 0x0061 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFB, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_027)
{
    // 10FFFB 0041;	
    // ('\U0010FFFB') <private-use-10FFFB>	[FBE1 FFFB 1CAD | 0020 0020 | 0002 0008 |]

    uint32_t cps[2] = { 0x10FFFB, 0x0041 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFB, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0008, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_028)
{
    // 10FFFB 0062;	
    // ('\U0010FFFB') <private-use-10FFFB>	[FBE1 FFFB 1CC6 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFB, 0x0062 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFB, 0x1CC6, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_029)
{
    // 10FFFC 0021;	
    // ('\U0010FFFC') <private-use-10FFFC>	[FBE1 FFFC 0261 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFC, 0x0021 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFC, 0x0261, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_030)
{
    // 10FFFC 003F;	
    // ('\U0010FFFC') <private-use-10FFFC>	[FBE1 FFFC 0267 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFC, 0x003F };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFC, 0x0267, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_031)
{
    // 10FFFC 0061;	
    // ('\U0010FFFC') <private-use-10FFFC>	[FBE1 FFFC 1CAD | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFC, 0x0061 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFC, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_032)
{
    // 10FFFC 0041;	
    // ('\U0010FFFC') <private-use-10FFFC>	[FBE1 FFFC 1CAD | 0020 0020 | 0002 0008 |]

    uint32_t cps[2] = { 0x10FFFC, 0x0041 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFC, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0008, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_033)
{
    // 10FFFC 0062;	
    // ('\U0010FFFC') <private-use-10FFFC>	[FBE1 FFFC 1CC6 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFC, 0x0062 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFC, 0x1CC6, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_034)
{
    // 10FFFD 0021;	
    // ('\U0010FFFD') <private-use-10FFFD>	[FBE1 FFFD 0261 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFD, 0x0021 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFD, 0x0261, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_035)
{
    // 10FFFD 003F;	
    // ('\U0010FFFD') <private-use-10FFFD>	[FBE1 FFFD 0267 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFD, 0x003F };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFD, 0x0267, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_036)
{
    // 10FFFD 0061;	
    // ('\U0010FFFD') <private-use-10FFFD>	[FBE1 FFFD 1CAD | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFD, 0x0061 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFD, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_037)
{
    // 10FFFD 0041;	
    // ('\U0010FFFD') <private-use-10FFFD>	[FBE1 FFFD 1CAD | 0020 0020 | 0002 0008 |]

    uint32_t cps[2] = { 0x10FFFD, 0x0041 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFD, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0008, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_038)
{
    // 10FFFD 0062;	
    // ('\U0010FFFD') <private-use-10FFFD>	[FBE1 FFFD 1CC6 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFD, 0x0062 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFD, 0x1CC6, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_039)
{
    // 10FFFE 0021;	
    // ('\U0010FFFE') <noncharacter-10FFFE>	[FBE1 FFFE 0261 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFE, 0x0021 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFE, 0x0261, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_040)
{
    // 10FFFE 003F;	
    // ('\U0010FFFE') <noncharacter-10FFFE>	[FBE1 FFFE 0267 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFE, 0x003F };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFE, 0x0267, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_041)
{
    // 10FFFE 0061;	
    // ('\U0010FFFE') <noncharacter-10FFFE>	[FBE1 FFFE 1CAD | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFE, 0x0061 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFE, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_042)
{
    // 10FFFE 0041;	
    // ('\U0010FFFE') <noncharacter-10FFFE>	[FBE1 FFFE 1CAD | 0020 0020 | 0002 0008 |]

    uint32_t cps[2] = { 0x10FFFE, 0x0041 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFE, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0008, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_043)
{
    // 10FFFE 0062;	
    // ('\U0010FFFE') <noncharacter-10FFFE>	[FBE1 FFFE 1CC6 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFE, 0x0062 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFE, 0x1CC6, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_044)
{
    // 10FFFF 0021;	
    // ('\U0010FFFF') <noncharacter-10FFFF>	[FBE1 FFFF 0261 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFF, 0x0021 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFF, 0x0261, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_045)
{
    // 10FFFF 003F;	
    // ('\U0010FFFF') <noncharacter-10FFFF>	[FBE1 FFFF 0267 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFF, 0x003F };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFF, 0x0267, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_046)
{
    // 10FFFF 0061;	
    // ('\U0010FFFF') <noncharacter-10FFFF>	[FBE1 FFFF 1CAD | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFF, 0x0061 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFF, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_047)
{
    // 10FFFF 0041;	
    // ('\U0010FFFF') <noncharacter-10FFFF>	[FBE1 FFFF 1CAD | 0020 0020 | 0002 0008 |]

    uint32_t cps[2] = { 0x10FFFF, 0x0041 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFF, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0008, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_048)
{
    // 10FFFF 0062;	
    // ('\U0010FFFF') <noncharacter-10FFFF>	[FBE1 FFFF 1CC6 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0x10FFFF, 0x0062 };
    uint32_t const ces[10] = { 0xFBE1, 0xFFFF, 0x1CC6, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 10);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 10))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_049)
{
    // FFFD 0021;	
    // (�) REPLACEMENT CHARACTER	[FFFD 0261 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0xFFFD, 0x0021 };
    uint32_t const ces[9] = { 0xFFFD, 0x0261, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 9);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 9))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_050)
{
    // FFFD 003F;	
    // (�) REPLACEMENT CHARACTER	[FFFD 0267 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0xFFFD, 0x003F };
    uint32_t const ces[9] = { 0xFFFD, 0x0267, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 9);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 9))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_051)
{
    // FFFD 0061;	
    // (�) REPLACEMENT CHARACTER	[FFFD 1CAD | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0xFFFD, 0x0061 };
    uint32_t const ces[9] = { 0xFFFD, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 9);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 9))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_052)
{
    // FFFD 0041;	
    // (�) REPLACEMENT CHARACTER	[FFFD 1CAD | 0020 0020 | 0002 0008 |]

    uint32_t cps[2] = { 0xFFFD, 0x0041 };
    uint32_t const ces[9] = { 0xFFFD, 0x1CAD, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0008, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 9);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 9))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

TEST(collation, non_ignorable_396_053)
{
    // FFFD 0062;	
    // (�) REPLACEMENT CHARACTER	[FFFD 1CC6 | 0020 0020 | 0002 0002 |]

    uint32_t cps[2] = { 0xFFFD, 0x0062 };
    uint32_t const ces[9] = { 0xFFFD, 0x1CC6, 0x0000, 0x0020, 0x0020, 0x0000, 0x0002, 0x0002, 0x0000 };

    auto collation = collate_for_tests(
        cps, cps + 2, boost::text::variable_weighting::non_ignorable);

    EXPECT_EQ(collation.size(), 9);
    EXPECT_TRUE(boost::algorithm::equal(collation.begin(), collation.end(), ces, ces + 9))
        << "from:     " << ce_dumper(cps)
        << "expected: " << ce_dumper(ces)
        << "got:      " << ce_dumper(collation);
}

