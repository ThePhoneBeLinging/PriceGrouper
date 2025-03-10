//
// Created by eal on 23/02/25.
//

#ifndef SMALLPRICEGROUP_H
#define SMALLPRICEGROUP_H
#include <memory>
#include <vector>


class SmallPriceGroup
{
public:
    SmallPriceGroup(int price, int hour);
    void setPrice(int price);
    void appendSmallPriceGroup(const std::shared_ptr<SmallPriceGroup>& smallPriceGroup);
    std::vector<int> getPrices();
    [[nodiscard]] bool shouldAdd(int price) const;
    void addPrice(int price);
    [[nodiscard]] int calcAveragePrice() const;
    [[nodiscard]] int getStartTime() const;
    [[nodiscard]] int getEndTime() const;
private:
    int startHour_;
    std::vector<int> prices_;


};



#endif //SMALLPRICEGROUP_H
