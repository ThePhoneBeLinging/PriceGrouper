cmake_minimum_required(VERSION 3.25)
project(PriceGrouper)


add_library(PriceGrouper STATIC
        PriceSorter.cpp
        SmallPriceGroup.cpp
        LargePriceGroup.cpp
)
target_include_directories(PriceGrouper PUBLIC include)
target_link_libraries(PriceGrouper PUBLIC Utility)