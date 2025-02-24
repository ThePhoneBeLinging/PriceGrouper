cmake_minimum_required(VERSION 3.25)
project(PriceGrouper)


add_library(PriceGrouper STATIC
        PriceSorter.cpp
        PriceSorter.h
        SmallPriceGroup.cpp
        SmallPriceGroup.h
        )

target_link_libraries(PriceGrouper PUBLIC Utility)