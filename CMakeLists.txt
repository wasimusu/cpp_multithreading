cmake_minimum_required(VERSION 3.10)
project(cpp_multithreading)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

add_executable(sync_devices sync_devices.cpp)
add_executable(sync_devices2 sync_devices_2.cpp)
add_executable(returnvalue threads.cpp)
add_executable(counter thread_safe_counters.cpp)
add_executable(consumer_producer consumer_producer.cpp)
add_executable(deadlock deadlock.cpp)
add_executable(locking locking.cpp)
add_executable(timeout timeouts.cpp)