cmake_minimum_required(VERSION 3.25)
project(PriceGrouper_Tests)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
        ../src/PriceSorter.cpp
        ../src/include/PriceGrouper/PriceSorter.h
        ../src/SmallPriceGroup.cpp
        ../src/include/PriceGrouper/SmallPriceGroup.h
        SmallPriceGroupTest.cpp
        SmallPriceGroupTest.h
        PriceSorterTests.cpp
        PriceSorterTests.h
        ../src/LargePriceGroup.cpp
        CompleteSortingTest.h
        CompleteSortingTest.cpp
        )
add_executable(PriceGrouper_Tests ${SOURCES})

target_link_libraries(PriceGrouper_Tests PUBLIC
        GTest::gtest
        GTest::gtest_main
        Utility
)