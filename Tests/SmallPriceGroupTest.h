//
// Created by eal on 24/02/25.
//

#ifndef SMALLPRICEGROUPTEST_H
#define SMALLPRICEGROUPTEST_H
#include <gtest/gtest.h>
#include "../src/SmallPriceGroup.h"
#include "Utility/ConfigController.h"


class SmallPriceGroupTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        ConfigController::loadConfig("../../Resources/config.json");
    }

    void TearDown() override
    {

    }
};

TEST_F(SmallPriceGroupTest, calcAverage)
{
    auto smallPriceGroup = std::make_shared<SmallPriceGroup>(50,0);
    smallPriceGroup->addPrice(100);

    // Average of 150 with 2 elements
    EXPECT_EQ(smallPriceGroup->calcAveragePrice(),75);

    smallPriceGroup->addPrice(150);

    // Average of 300 with 3 elements
    EXPECT_EQ(smallPriceGroup->calcAveragePrice(), 100);
    smallPriceGroup->addPrice(50);

    // Test that we round down one if it is not an integer.
    // Average of 350 with 4 elements
    EXPECT_EQ(smallPriceGroup->calcAveragePrice(),87);
}

TEST_F(SmallPriceGroupTest, GetEndTime)
{
    auto smallPriceGroup = std::make_shared<SmallPriceGroup>(50,0);
    EXPECT_EQ(smallPriceGroup->getEndTime(), 1);
    smallPriceGroup->addPrice(50);
    EXPECT_EQ(smallPriceGroup->getEndTime(), 2);

    for (int i = 0; i < 50; i++)
    {
        smallPriceGroup->addPrice(i);
    }
    EXPECT_EQ(smallPriceGroup->getEndTime(), 52);
}

TEST_F(SmallPriceGroupTest, ShouldAdd1)
{
    ConfigController::TESTsetConfigInt("PercentageGapInGroups",5);
    ConfigController::TESTsetConfigInt("MinimumGapInGroups",15);
    auto smallPriceGroup = std::make_shared<SmallPriceGroup>(100,0);
    EXPECT_TRUE(smallPriceGroup->shouldAdd(104));
    EXPECT_FALSE(smallPriceGroup->shouldAdd(115));
    EXPECT_TRUE(smallPriceGroup->shouldAdd(114));
    EXPECT_TRUE(smallPriceGroup->shouldAdd(86));
    EXPECT_FALSE(smallPriceGroup->shouldAdd(85));
}

TEST_F(SmallPriceGroupTest, ShouldAdd2)
{
    ConfigController::TESTsetConfigInt("PercentageGapInGroups",5);
    ConfigController::TESTsetConfigInt("MinimumGapInGroups",15);
    auto smallPriceGroup = std::make_shared<SmallPriceGroup>(1000,0);

    EXPECT_TRUE(smallPriceGroup->shouldAdd(1049));
    EXPECT_FALSE(smallPriceGroup->shouldAdd(1050));
    EXPECT_TRUE(smallPriceGroup->shouldAdd(951));
    EXPECT_FALSE(smallPriceGroup->shouldAdd(950));
    EXPECT_TRUE(smallPriceGroup->shouldAdd(1000));
}




#endif //SMALLPRICEGROUPTEST_H
