cmake_minimum_required(VERSION 2.8.8)

project(secondary_indexer)

add_definitions("--std=c++11")

add_executable(build-car-owner-index build_car_owner_index.cxx)
add_executable(query-car-owner query_car_owner.cxx)

