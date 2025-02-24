//
// Created by eal on 23/02/25.
//

#include "SmallPriceGroup.h"

#include "Utility/ConfigController.h"

SmallPriceGroup::SmallPriceGroup(int price, int hour)
{
    startHour_ = hour;
    prices_.push_back(price);
}

bool SmallPriceGroup::shouldAdd(int price)
{
    int percentage = ConfigController::getConfigInt("PercentageGapInGroups");
    int minGap = ConfigController::getConfigInt("MinimumGapInGroupsCents");
    int maxGap = ConfigController::getConfigInt("MaximumGapInGroupsCents");

    if (std::max(prices_[0],price) - std::min(prices_[0],price) > maxGap)
    {
        return false;
    }
    if (prices_.size() == 1)
    {
        return true;
    }
    float multiplier = static_cast<float>(percentage) / 100.0f;
    int minMaxValue = prices_[0] * multiplier;
    minMaxValue = std::max(minMaxValue, minGap);
    int minVal = prices_[0] - minMaxValue;
    int maxVal = prices_[0] + minMaxValue;
    return minVal < price && price < maxVal;
}

void SmallPriceGroup::addPrice(int price)
{
    prices_.push_back(price);
}

int SmallPriceGroup::calcAveragePrice()
{
    int sum = 0;
    for (auto val : prices_)
    {
        sum += val;
    }
    return sum / prices_.size();
}

int SmallPriceGroup::getEndTime()
{
    return startHour_ + prices_.size();
}
