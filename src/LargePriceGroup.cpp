//
// Created by Elias Aggergaard Larsen on 25/02/2025.
//

#include "include/PriceGrouper/LargePriceGroup.h"

void LargePriceGroup::addSmallPriceGroup(const std::shared_ptr<SmallPriceGroup>& smallPriceGroup)
{
    if (not smallPriceGroups_.empty())
    {
        if (smallPriceGroup->getStartTime() == smallPriceGroups_.back()->getEndTime() && smallPriceGroups_.back()->
            getStartTime() != -1)
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
        addSmallPriceGroup(price);
    }
}

std::vector<std::shared_ptr<SmallPriceGroup>> LargePriceGroup::getSmallPriceGroups() const
{
    return smallPriceGroups_;
}
