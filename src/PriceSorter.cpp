//
// Created by eal on 23/02/25.
//

#include "PriceSorter.h"

#include <iostream>
#include <algorithm>

#include "Utility/ConfigController.h"

std::vector<std::shared_ptr<LargePriceGroup>> PriceSorter::findLargePriceGroups(const std::vector<int>& prices)
{
    std::vector<int> firstDay;
    std::vector<int> secondDay;
    if (prices.size() >= 24)
    {
        for (int i = 0; i < 24; i++)
        {
            firstDay.push_back(prices[i]);
        }
    }
    else if (prices.size() == 48)
    {
        for (int i = 24; i < 48; i++)
        secondDay.push_back(prices[i]);
    }

    auto firstDaySmallPrices = sortPrices(firstDay);
    auto secondDaySmallPrices = sortPrices(secondDay);
    auto allSmallPrices = firstDaySmallPrices;
    for (const auto& val : secondDaySmallPrices)
    {
        allSmallPrices.push_back(val);
    }
    auto comparator = [] (std::shared_ptr<SmallPriceGroup> a, std::shared_ptr<SmallPriceGroup> b) -> bool
    {
        return a->calcAveragePrice() < b->calcAveragePrice();
    };
    auto lowestPrice = *std::ranges::min_element(allSmallPrices,comparator);

    int startValOfNextRange = lowestPrice->calcAveragePrice();

    std::vector<std::shared_ptr<LargePriceGroup>> largePriceGroups;

    int maxAddedSoFar = 0;

    for (int i = 0; i < 3; i++)
    {
        auto largePriceGroup = std::make_shared<LargePriceGroup>();
        auto cheapestSmallPrices = findSmallPriceGroupsInsidePriceRange(startValOfNextRange,firstDaySmallPrices);
        startValOfNextRange = (*std::ranges::max_element(cheapestSmallPrices,comparator))->calcAveragePrice() + 1;
        largePriceGroup->setSmallPriceGroup(cheapestSmallPrices);
        largePriceGroups.push_back(largePriceGroup);
    }
    auto largePriceGroup = std::make_shared<LargePriceGroup>();
    for (const auto& value : allSmallPrices)
    {
        if (value->calcAveragePrice() > startValOfNextRange)
        {
            largePriceGroup->addSmallPriceGroup(value);
        }
    }
    largePriceGroups.push_back(largePriceGroup);

    return largePriceGroups;
}

std::vector<std::shared_ptr<SmallPriceGroup>> PriceSorter::sortPrices(const std::vector<int>& prices)
{
    if (prices.size() != 24)
    {
        std::cout << "Complete day was not used in PriceSorter, only receieved: " << prices.size() << std::endl;
    }
    std::vector<std::shared_ptr<SmallPriceGroup>> smallPriceGroups;
    int hour = 0;
    while (hour != prices.size())
    {
        auto val = findSmallPriceGroup(hour,prices);
        smallPriceGroups.push_back(val);
        hour = val->getEndTime();
    }
    return smallPriceGroups;
}

std::shared_ptr<SmallPriceGroup> PriceSorter::findSmallPriceGroup(int hour, const std::vector<int>& prices)
{
    int price = prices[hour];
    auto smallPriceGroup = std::make_shared<SmallPriceGroup>(price, hour);
    for (int i = hour + 1; i < prices.size(); i++)
    {
        if (not smallPriceGroup->shouldAdd(prices[i]))
        {
            break;
        }
        smallPriceGroup->addPrice(prices[i]);
    }
    return smallPriceGroup;
}

std::vector<std::shared_ptr<SmallPriceGroup>> PriceSorter::findSmallPriceGroupsInsidePriceRange(int price,
                                                                                                const std::vector<std::shared_ptr<SmallPriceGroup>>& smallPriceGroups)
{
    int gapBetweenGroups = ConfigController::getConfigInt("MinimumGapBetweenGroups");
    int percentageGap = ConfigController::getConfigInt("PercentageGapBetweenGroups");

    int percentagePriceGap = price * (percentageGap / 100.0);
    int maxGap = std::max(gapBetweenGroups, percentagePriceGap);

    std::vector<std::shared_ptr<SmallPriceGroup>> smallPriceGroupsToReturn;

    for (const auto& priceGroup : smallPriceGroups)
    {
        int averagePrice = priceGroup->calcAveragePrice();
        if (averagePrice >= price && averagePrice < price + maxGap)
        {
            smallPriceGroupsToReturn.push_back(priceGroup);
        }
    }

    return smallPriceGroupsToReturn;
}
