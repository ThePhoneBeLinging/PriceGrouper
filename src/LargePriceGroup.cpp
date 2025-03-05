//
// Created by Elias Aggergaard Larsen on 25/02/2025.
//

#include "include/PriceGrouper/LargePriceGroup.h"

void LargePriceGroup::addSmallPriceGroup(const std::shared_ptr<SmallPriceGroup>& smallPriceGroup)
{
    smallPriceGroups_.push_back(smallPriceGroup);
}

void LargePriceGroup::setSmallPriceGroup(const std::vector<std::shared_ptr<SmallPriceGroup>>& smallPriceGroups)
{
    smallPriceGroups_ = smallPriceGroups;
}

std::vector<std::shared_ptr<SmallPriceGroup>> LargePriceGroup::getSmallPriceGroups() const
{
    return smallPriceGroups_;
}
