//
// Created by eal on 23/02/25.
//

#include "PriceSorter.h"

#include <iostream>

#include "Utility/ConfigController.h"

std::vector<std::vector<std::shared_ptr<SmallPriceGroup>>> PriceSorter::sortPrices(const std::vector<int>& prices)
{
    if (prices.size() % 24 != 0)
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

    int min = INT_MAX;
    for (const auto& smallPriceGroup : smallPriceGroups)
    {
        int average = smallPriceGroup->calcAveragePrice();
        if (average < min)
        {
            min = average;
        }
    }


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
