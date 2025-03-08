//
// Created by eal on 23/02/25.
//

#include "include/PriceGrouper/SmallPriceGroup.h"

#include "Utility/ConfigController.h"

SmallPriceGroup::SmallPriceGroup(int price, int hour)
{
    startHour_ = hour;
    prices_.push_back(price);
}

bool SmallPriceGroup::shouldAdd(int price) const
{
    int percentage = ConfigController::getConfigInt("PercentageGapInGroups");
    int minGap = ConfigController::getConfigInt("MinimumGapInGroupsCents");
    int maxGap = ConfigController::getConfigInt("MaximumGapInGroupsCents");
    bool useFirstPrice = ConfigController::getConfigBool("SmallGroupsUseFirstValueInsteadOfAvg");

    int valToCompareTo;
    if (useFirstPrice)
    {
        valToCompareTo = prices_[0];
    }
    else
    {
        valToCompareTo = calcAveragePrice();
    }

    if (std::max(valToCompareTo,price) - std::min(valToCompareTo,price) > maxGap)
    {
        return false;
    }
    if (prices_.size() == 1)
    {
        return true;
    }
    float multiplier = static_cast<float>(percentage) / 100.0f;
    int minMaxValue = static_cast<double>(valToCompareTo) * multiplier;
    minMaxValue = std::max(minMaxValue, minGap);
    int minVal = valToCompareTo - minMaxValue;
    int maxVal = valToCompareTo + minMaxValue;
    return minVal < price && price < maxVal;
}

void SmallPriceGroup::addPrice(int price)
{
    prices_.push_back(price);
}

int SmallPriceGroup::calcAveragePrice() const
{
    int sum = 0;
    for (auto val : prices_)
    {
        sum += val;
    }
    return sum / prices_.size();
}

int SmallPriceGroup::getStartTime() const
{
    return startHour_;
}

int SmallPriceGroup::getEndTime() const
{
    return startHour_ + prices_.size();
}
