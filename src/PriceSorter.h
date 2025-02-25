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
    /**
     * 
     * @param prices Should be a vector of all prices in a day, e.g. it should consist of 24 elements
     * @return Returns 4 vectors of vectors of smallGroups.
     */
    static std::vector<std::vector<std::shared_ptr<SmallPriceGroup>>> sortPrices(const std::vector<int>& prices);
    static std::shared_ptr<SmallPriceGroup> findSmallPriceGroup(int hour, const std::vector<int>& prices);
};



#endif //PRICESORTER_H
