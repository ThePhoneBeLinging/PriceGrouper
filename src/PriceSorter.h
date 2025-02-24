//
// Created by eal on 23/02/25.
//

#ifndef PRICESORTER_H
#define PRICESORTER_H
#include <memory>
#include <vector>
#include "SmallPriceGroup.h"


class PriceSorter
{
public:
    static std::vector<std::vector<std::shared_ptr<SmallPriceGroup>>> sortPrices(const std::vector<int>& prices);
    static std::shared_ptr<SmallPriceGroup> findSmallPriceGroup(int hour, const std::vector<int>& prices);
};



#endif //PRICESORTER_H
