//
// Created by eal on 24/02/25.
//

#ifndef PRICESORTERTESTS_H
#define PRICESORTERTESTS_H
#include <gtest/gtest.h>

#include "../src/PriceSorter.h"
#include "Utility/ConfigController.h"

class PriceSorterTests : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {

    }
};

TEST(PriceSorterTests, findSmallGroupTest1)
{
    ConfigController::TESTsetConfigInt("PercentageGapInGroups",5);
    ConfigController::TESTsetConfigInt("MinimumGapInGroupsCents",15);
    std::vector<int> testData;
    for (int i = 0; i < 15; i++)
    {
        testData.push_back(i);
    }
    auto result = PriceSorter::findSmallPriceGroup(0,testData);
    EXPECT_EQ(result->getEndTime(),15);
}

TEST(PriceSorterTests, findSmallGroupTest2)
{
    ConfigController::TESTsetConfigInt("PercentageGapInGroups",5);
    ConfigController::TESTsetConfigInt("MinimumGapInGroupsCents",15);
    std::vector<int> testData;
    int x = 0;
    for (int i = 0; i < 15; i++)
    {
        testData.push_back(x);
        x += 15;
    }
    auto result = PriceSorter::findSmallPriceGroup(0,testData);
    EXPECT_EQ(result->getEndTime(),2);
}

TEST(PriceSorterTests, findSmallGroupTest3)
{
    ConfigController::TESTsetConfigInt("PercentageGapInGroups",5);
    ConfigController::TESTsetConfigInt("MinimumGapInGroupsCents",15);
    std::vector<int> testData;
    for (int i = 1000; i < 1100; i++)
    {
        testData.push_back(i);
    }
    auto result = PriceSorter::findSmallPriceGroup(0,testData);
    EXPECT_EQ(result->getEndTime(),50);
}

TEST(PriceSorterTests, findSmallGroupTest4)
{
    ConfigController::TESTsetConfigInt("PercentageGapInGroups",5);
    ConfigController::TESTsetConfigInt("MinimumGapInGroupsCents",15);
    ConfigController::TESTsetConfigInt("MaximumGapInGroupsCents",9001);
    std::vector<int> testData;
    testData.push_back(1000);
    testData.push_back(10000);
    testData.push_back(1049);
    auto result = PriceSorter::findSmallPriceGroup(0,testData);
    EXPECT_EQ(result->getEndTime(),3);
}


#endif //PRICESORTERTESTS_H
