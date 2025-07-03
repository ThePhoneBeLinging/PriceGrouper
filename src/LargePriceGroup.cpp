//
// Created by Elias Aggergaard Larsen on 25/02/2025.
//

#include "include/PriceGrouper/LargePriceGroup.h"

#include "Utility/ConfigController.h"

void LargePriceGroup::addSmallPriceGroup(const std::shared_ptr<SmallPriceGroup>& smallPriceGroup, bool toAppendExtendedTimePeriods)
{
    if (not smallPriceGroups_.empty())
    {
        if (smallPriceGroup->getStartTime() == smallPriceGroups_.back()->getEndTime() && smallPriceGroups_.back()->
            getStartTime() != -1 && (toAppendExtendedTimePeriods || std::abs(getAveragePrice() - smallPriceGroup->calcAveragePrice()) < ConfigController::getConfigInt("AllowedDistanceInRestColumn")))
        {
            smallPriceGroups_.back()->appendSmallPriceGroup(smallPriceGroup);
            return;
        }
    }
    smallPriceGroups_.push_back(smallPriceGroup);
}

void LargePriceGroup::setSmallPriceGroup(std::vector<std::shared_ptr<SmallPriceGroup>>& smallPriceGroups)
{
    for (const auto& price : smallPriceGroups)
    {
        addSmallPriceGroup(price,true);
    }
}

std::vector<std::shared_ptr<SmallPriceGroup>> LargePriceGroup::getSmallPriceGroups() const
{
    return smallPriceGroups_;
}

int LargePriceGroup::getAveragePrice() const
{
    double sum = 0;
    for (const auto& smallPriceGroup : smallPriceGroups_)
    {
        sum += smallPriceGroup->calcAveragePrice();
    }
    return sum / smallPriceGroups_.size();
}
