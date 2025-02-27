//
// Created by Elias Aggergaard Larsen on 25/02/2025.
//

#ifndef LARGEPRICEGROUP_H
#define LARGEPRICEGROUP_H
#include "SmallPriceGroup.h"


class LargePriceGroup
{
public:
    LargePriceGroup() = default;
    void addSmallPriceGroup(const std::shared_ptr<SmallPriceGroup>& smallPriceGroup);
    void setSmallPriceGroup(const std::vector<std::shared_ptr<SmallPriceGroup>>& smallPriceGroups);
private:
    std::vector<std::shared_ptr<SmallPriceGroup>> smallPriceGroups_;
};



#endif //LARGEPRICEGROUP_H
