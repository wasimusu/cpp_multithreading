# Multithreading in CPP

This repository has two objectives:
* Demonstrate the concepts of multiple threading/concurrency through code samples.
* Demonstrate the C++ multi-threading concepts through code samples.

### Some of the concepts demonstrated
* Simple usage of threads to do tasks simulatenously: [threads.cpp](threads.cpp)
* Collecting return values from threads: [return_from_function.cpp](return_from_function.cpp)
* Data race occurs when two or more threads are trying to manipulate same shared data at the same time: [data_race.cpp](data_race.cpp)
* Counters should work regardless of how many threads are accessing it. See [thread_safe_counters.cpp](thread_safe_counters.cpp)
* Check if a function completes within stipulated time or not: [timeouts.cpp](timeouts.cpp)
* Different types of locking mechanisms: [locking.cpp](locking.cpp)
* Syncing cameras to take pictures simulatenously: 
    * [sync_devices_yeild.cpp](sync_devices_yield.cpp)
    * [sync_devices_condition_variable.cpp](sync_devices_condition_variable.cpp)
* What are deadlocks and how do they happen? [deadlock.cpp](deadlock.cpp)

### Upcoming
* Consumer producer pattern for threads
* Using threadpool to avoid creating threads

### Some common threading mistakes and notes
* Trying to join a detached thread or thread that has already been joined. Under uncertainty, use thread member "joinable" to check if thread can be joined or not.
* Trying to acquire a mutex twice.
* Everything is passed by value. Use std::ref to pass argument by reference.
* Unlocked shared data members cause data race if their value is manipulated by threads.
* When using mutex::lock() and mutex::unlock(), forgetting to unlock will cause the resource to not be released.
  