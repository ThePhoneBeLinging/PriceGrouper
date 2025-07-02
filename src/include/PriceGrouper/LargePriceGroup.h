//
// Created by Elias Aggergaard Larsen on 25/02/2025.
//

#ifndef LARGEPRICEGROUP_H
#define LARGEPRICEGROUP_H
#include <memory>

#include "SmallPriceGroup.h"


class LargePriceGroup
{
public:
    LargePriceGroup() = default;
    void addSmallPriceGroup(const std::shared_ptr<SmallPriceGroup>& smallPriceGroup, bool toAppendExtendedTimePeriods);
    void setSmallPriceGroup(std::vector<std::shared_ptr<SmallPriceGroup>>& smallPriceGroups);
    [[nodiscard]] std::vector<std::shared_ptr<SmallPriceGroup>> getSmallPriceGroups() const;

private:
    std::vector<std::shared_ptr<SmallPriceGroup>> smallPriceGroups_;
};


#endif //LARGEPRICEGROUP_H
