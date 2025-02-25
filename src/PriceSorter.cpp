//
// Created by eal on 23/02/25.
//

#include "PriceSorter.h"

#include <iostream>

#include "Utility/ConfigController.h"

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
