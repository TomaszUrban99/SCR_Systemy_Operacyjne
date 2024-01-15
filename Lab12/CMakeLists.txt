cmake_minimum_required(VERSION 3.20)
project(task_scheduling CXX)

add_library(record src/record.cpp)
target_include_directories(record PUBLIC inc)

add_library(log src/log.cpp)
target_include_directories(log PUBLIC inc)
target_link_libraries( log PUBLIC record )

add_executable(task_scheduling src/main.cpp )
target_link_libraries(task_scheduling PRIVATE log)


