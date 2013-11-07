cmake_minimum_required(VERSION 2.8.8)

project(secondary_indexer)

add_definitions("--std=c++11")

add_executable(build-secondary-index build_secondary_index.cxx)
add_executable(query query_secondary_index.cxx)

