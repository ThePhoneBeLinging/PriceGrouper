//
// Created by eal on 23/02/25.
//

#ifndef SMALLPRICEGROUP_H
#define SMALLPRICEGROUP_H
#include <vector>


class SmallPriceGroup
{
public:
    SmallPriceGroup(int price, int hour);
    bool shouldAdd(int price);
    void addPrice(int price);
    int calcAveragePrice();
    int getEndTime();
private:
    int startHour_;
    std::vector<int> prices_;


};



#endif //SMALLPRICEGROUP_H
