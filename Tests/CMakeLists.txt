cmake_minimum_required(VERSION 3.25)
project(PriceGrouper_Tests)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
        ../src/PriceSorter.cpp
        ../src/PriceSorter.h
        ../src/SmallPriceGroup.cpp
        ../src/SmallPriceGroup.h
        SmallPriceGroupTest.cpp
        SmallPriceGroupTest.h
        PriceSorterTests.cpp
        PriceSorterTests.h
        ../src/LargePriceGroup.cpp
        )
add_executable(PriceGrouper_Tests ${SOURCES})

target_link_libraries(PriceGrouper_Tests PUBLIC
        GTest::gtest
        GTest::gtest_main
        Utility
)