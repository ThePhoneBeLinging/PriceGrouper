//
// Created by eal on 23/02/25.
//

#include "include/PriceGrouper/PriceSorter.h"

#include <iostream>
#include <algorithm>

#include "Utility/ConfigController.h"
#include "Utility/TimeUtil.h"

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
    if (prices.size() == 48)
    {
        for (int i = 24; i < 48; i++)
            secondDay.push_back(prices[i]);
    }

    auto firstDaySmallPrices = sortPrices(firstDay);
    auto secondDaySmallPrices = sortPrices(secondDay);
    std::vector<std::shared_ptr<SmallPriceGroup>> allSmallPrices;
    auto dummySmallPrice = std::make_shared<SmallPriceGroup>(INT32_MAX, -1);
    int currentHour = TimeUtil::getCurrentTime().tm_hour;
    for (const auto& val : firstDaySmallPrices)
    {
        if (ConfigController::getConfigBool("OnlySortFuturePrices"))
        {
            if (val->getEndTime() > currentHour)
            {
                allSmallPrices.push_back(val);
            }
        }
        else
        {
            allSmallPrices.push_back(val);
        }
    }

    allSmallPrices.push_back(dummySmallPrice);

    for (const auto& val : secondDaySmallPrices)
    {
        allSmallPrices.push_back(val);
    }
    auto comparator = [](const std::shared_ptr<SmallPriceGroup>& a, const std::shared_ptr<SmallPriceGroup>& b) -> bool
    {
        return a->calcAveragePrice() < b->calcAveragePrice();
    };
    auto lowestPrice = *std::ranges::min_element(allSmallPrices, comparator);
    int startValOfNextRange = lowestPrice->calcAveragePrice();

    dummySmallPrice->setPrice(INT32_MIN);
    std::vector<std::shared_ptr<LargePriceGroup>> largePriceGroups;

    int maxAddedSoFar = 0;

    for (int i = 0; i < 3; i++)
    {
        auto largePriceGroup = std::make_shared<LargePriceGroup>();
        auto cheapestSmallPrices = findSmallPriceGroupsInsidePriceRange(startValOfNextRange, allSmallPrices);
        if (cheapestSmallPrices.size() == 1)
        {
            startValOfNextRange = INT_MAX;
            break;
        }

        int highestValueIncluded = (*std::ranges::max_element(cheapestSmallPrices, comparator))->calcAveragePrice();
        startValOfNextRange = calcStartValOfNextRange(highestValueIncluded, allSmallPrices);
        largePriceGroup->setSmallPriceGroup(cheapestSmallPrices);
        largePriceGroups.push_back(largePriceGroup);
    }
    auto largePriceGroup = std::make_shared<LargePriceGroup>();
    for (const auto& value : allSmallPrices)
    {
        if (value->calcAveragePrice() >= startValOfNextRange || value->getStartTime() == -1)
        {
            largePriceGroup->addSmallPriceGroup(value);
        }
    }
    largePriceGroups.push_back(largePriceGroup);
    while (largePriceGroups.size() < 4)
    {
        auto localLargeGrouå = std::make_shared<LargePriceGroup>();
        localLargeGrouå->addSmallPriceGroup(dummySmallPrice);
        largePriceGroups.push_back(localLargeGrouå);
    }

    return largePriceGroups;
}

std::vector<std::shared_ptr<SmallPriceGroup>> PriceSorter::sortPrices(const std::vector<int>& prices)
{
    std::vector<std::shared_ptr<SmallPriceGroup>> smallPriceGroups;
    int hour = 0;
    while (hour != prices.size())
    {
        auto val = findSmallPriceGroup(hour, prices);
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
        // We push the dummy smallgroup into the result. That way we know when we have passed the first 24.
        if (priceGroup->getStartTime() == -1)
        {
            smallPriceGroupsToReturn.push_back(priceGroup);
            continue;
        }
        if (averagePrice >= price && averagePrice < price + maxGap)
        {
            smallPriceGroupsToReturn.push_back(priceGroup);
        }
    }

    return smallPriceGroupsToReturn;
}

int PriceSorter::calcStartValOfNextRange(const int highestPrice,
                                         const std::vector<std::shared_ptr<SmallPriceGroup>>& smallPriceGroups)
{
    int minSoFar = INT_MAX;
    for (const auto& price : smallPriceGroups)
    {
        if (price->calcAveragePrice() < minSoFar && price->calcAveragePrice() > highestPrice)
        {
            minSoFar = price->calcAveragePrice();
        }
    }
    return minSoFar;
}
