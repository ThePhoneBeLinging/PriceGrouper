//
// Created by Elias Aggergaard Larsen on 25/02/2025.
//

#ifndef PRICEGROUPCOLUMN_H
#define PRICEGROUPCOLUMN_H
#include "SmallPriceGroup.h"


class PriceGroupColumn
{
public:
    explicit PriceGroupColumn(std::shared_ptr<SmallPriceGroup> smallPriceGroup);
private:
    int lowestValue_;
    std::vector<std::shared_ptr<SmallPriceGroup>> smallPriceGroups_;
};



#endif //PRICEGROUPCOLUMN_H
