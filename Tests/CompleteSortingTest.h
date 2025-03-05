//
// Created by eal on 01/03/25.
//

#ifndef COMPLETESORTINGTEST_H
#define COMPLETESORTINGTEST_H

#include "../src/include/PriceGrouper/PriceSorter.h"
#include "gtest/gtest.h"
#include "Utility/ConfigController.h"

class CompleteSortingTest : public ::testing::Test
{
public:
    // The prices below is real data from Radius Elnet + Andel from the 28/02-2025
    static std::vector<int> getPricesFrom25_02_2025()
    {
        std::vector<int> prices;
        prices.push_back(24000);
        prices.push_back(23500);
        prices.push_back(23400);
        prices.push_back(23200);
        prices.push_back(23700);
        prices.push_back(23700);
        prices.push_back(28300);
        prices.push_back(29600);
        prices.push_back(30700);
        prices.push_back(29200);
        prices.push_back(27500);
        prices.push_back(26400);
        prices.push_back(25800);
        prices.push_back(25700);
        prices.push_back(26000);
        prices.push_back(27300);
        prices.push_back(28200);
        prices.push_back(37300);
        prices.push_back(38000);
        prices.push_back(37800);
        prices.push_back(36400);
        prices.push_back(28000);
        prices.push_back(27500);
        prices.push_back(26700);
        return std::move(prices);
    }
};


TEST(CompleteSortingTest, CompleteTest1)
{
    ConfigController::TESTsetConfigInt("PercentageGapInGroups",5);
    ConfigController::TESTsetConfigInt("MinimumGapInGroupsCents",1500);
    ConfigController::TESTsetConfigInt("MaximumGapInGroupsCents",5000);
    ConfigController::TESTsetConfigInt("PercentageGapBetweenGroups",5);
    ConfigController::TESTsetConfigInt("MinimumGapBetweenGroups",2500);

    auto prices = CompleteSortingTest::getPricesFrom25_02_2025();
    auto priceGroups = PriceSorter::findLargePriceGroups(prices);

    EXPECT_EQ(priceGroups.size(), 4);
}



#endif //COMPLETESORTINGTEST_H
