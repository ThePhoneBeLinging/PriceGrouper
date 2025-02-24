//
// Created by eal on 24/02/25.
//

#ifndef SMALLPRICEGROUPTEST_H
#define SMALLPRICEGROUPTEST_H
#include <gtest/gtest.h>
#include "../src/SmallPriceGroup.h"


class SmallPriceGroupTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {

    }
};

TEST_F(SmallPriceGroupTest, calcAverage)
{
    auto smallPriceGroup = std::make_shared<SmallPriceGroup>(50,0);
    smallPriceGroup->addPrice(100);

    // Average of 150 with 2 elements
    EXPECT_EQ(smallPriceGroup->calcAveragePrice(),75);

    smallPriceGroup->addPrice(150);

    // Average of 300 with 3 elements
    EXPECT_EQ(smallPriceGroup->calcAveragePrice(), 100);
    smallPriceGroup->addPrice(50);

    // Test that we round down one if it is not an integer.
    // Average of 350 with 4 elements
    EXPECT_EQ(smallPriceGroup->calcAveragePrice(),87);
}



#endif //SMALLPRICEGROUPTEST_H
