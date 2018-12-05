#
# Copyright (c) 2018 Doyub Kim
#
# I am making my contributions/submissions to this project solely in my personal
# capacity and am not conveying any rights to any intellectual property of any
# third parties.
#

cmake_minimum_required(VERSION 2.8.9)
find_package(Pangolin  REQUIRED)


add_executable(wave_fluid_simulation  main.cpp)
target_link_libraries(wave_fluid_simulation -lboost_iostreams -lboost_system -lboost_filesystem)
