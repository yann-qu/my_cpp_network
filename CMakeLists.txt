cmake_minimum_required(VERSION 3.0.0)
project(my_cpp_network VERSION 0.1.0)

add_subdirectory(my_cpp_network_lib)

add_executable(main1 main1.cpp)
add_executable(main2 main2.cpp)

target_link_libraries(main1 my_cpp_network_lib)
target_link_libraries(main2 my_cpp_network_lib)
