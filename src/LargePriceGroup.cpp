//
// Created by Elias Aggergaard Larsen on 25/02/2025.
//

#include "LargePriceGroup.h"

void LargePriceGroup::setSmallPriceGroup(const std::vector<std::shared_ptr<SmallPriceGroup>>& smallPriceGroups)
{
    smallPriceGroups_ = smallPriceGroups;
}
