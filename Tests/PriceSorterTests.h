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

TEST(PriceSorterTests, SortPrices1)
{
    ConfigController::TESTsetConfigInt("PercentageGapInGroups",5);
    ConfigController::TESTsetConfigInt("MinimumGapInGroupsCents",15);
    ConfigController::TESTsetConfigInt("MaximumGapInGroupsCents",9000);
    std::vector<int> testData;
    testData.reserve(24);
    for (int i = 1; i < 25; i++)
    {
        testData.push_back(i * 7);
    }
    auto smallPriceGroups = PriceSorter::sortPrices(testData);
    EXPECT_EQ(smallPriceGroups.size(), 8);
}

TEST(PriceSorterTests, SortPrices2)
{
    ConfigController::TESTsetConfigInt("PercentageGapInGroups",5);
    ConfigController::TESTsetConfigInt("MinimumGapInGroupsCents",15);
    ConfigController::TESTsetConfigInt("MaximumGapInGroupsCents",9000);
    std::vector<int> testData;
    testData.reserve(24);
    for (int i = 1; i < 25; i++)
    {
        testData.push_back(i * 7.5);
    }
    auto smallPriceGroups = PriceSorter::sortPrices(testData);
    EXPECT_EQ(smallPriceGroups.size(), 12);
}

TEST(PriceSorterTests, SortPrices3)
{
    ConfigController::TESTsetConfigInt("PercentageGapInGroups",5);
    ConfigController::TESTsetConfigInt("MinimumGapInGroupsCents",15);
    ConfigController::TESTsetConfigInt("MaximumGapInGroupsCents",9000);
    std::vector<int> testData;
    testData.reserve(24);
    for (int i = 1; i < 25; i++)
    {
        testData.push_back(i * 8);
    }
    auto smallPriceGroups = PriceSorter::sortPrices(testData);
    EXPECT_EQ(smallPriceGroups.size(), 12);
}

TEST(PriceSorterTests, SortPrices4)
{
    ConfigController::TESTsetConfigInt("PercentageGapInGroups",5);
    ConfigController::TESTsetConfigInt("MinimumGapInGroupsCents",15);
    ConfigController::TESTsetConfigInt("MaximumGapInGroupsCents",16);
    std::vector<int> testData;
    testData.reserve(24);
    for (int i = 1; i < 25; i++)
    {
        testData.push_back(i * 17);
    }
    auto smallPriceGroups = PriceSorter::sortPrices(testData);
    EXPECT_EQ(smallPriceGroups.size(), 24);
}
TEST(PriceSorterTests, SortPrices5)
{
    ConfigController::TESTsetConfigInt("PercentageGapInGroups",5);
    ConfigController::TESTsetConfigInt("MinimumGapInGroupsCents",15);
    ConfigController::TESTsetConfigInt("MaximumGapInGroupsCents",16);
    std::vector<int> testData;
    testData.reserve(24);
    for (int i = 1; i < 25; i++)
    {
        testData.push_back(i * 17);
    }
    auto smallPriceGroups = PriceSorter::sortPrices(testData);
    EXPECT_EQ(smallPriceGroups.size(), 24);
}


#endif //PRICESORTERTESTS_H
