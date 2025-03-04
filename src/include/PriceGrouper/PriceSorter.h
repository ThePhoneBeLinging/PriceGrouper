//
// Created by eal on 23/02/25.
//

#ifndef PRICESORTER_H
#define PRICESORTER_H
#include <memory>
#include <vector>

#include "LargePriceGroup.h"
#include "SmallPriceGroup.h"


class PriceSorter
{
public:
    /**
     * 
     * @param prices Should be a vector of all prices in either one or two days. Therefore, 24 or 48 elements.
     * @return Returns vector of LargePriceGroups
     */
    static std::vector<std::shared_ptr<LargePriceGroup>> findLargePriceGroups(const std::vector<int>& prices);
    static std::vector<std::shared_ptr<SmallPriceGroup>> sortPrices(const std::vector<int>& prices);
    static std::shared_ptr<SmallPriceGroup> findSmallPriceGroup(int hour, const std::vector<int>& prices);
    static std::vector<std::shared_ptr<SmallPriceGroup>> findSmallPriceGroupsInsidePriceRange(int price, const std::vector<std::shared_ptr<SmallPriceGroup>>& smallPriceGroups);
private:
    static int calcStartValOfNextRange(int highestPrice, const std::vector<std::shared_ptr<SmallPriceGroup>>& smallPriceGroups);
};



#endif //PRICESORTER_H
