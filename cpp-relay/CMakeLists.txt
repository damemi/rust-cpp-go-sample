cmake_minimum_required(VERSION 3.16)
project(micro_cpp_relay CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(relay src/main.cpp)
target_include_directories(relay PRIVATE ${CMAKE_SOURCE_DIR}/vendor/cpp-httplib)
target_link_libraries(relay PRIVATE pthread)
