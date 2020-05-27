# Multithreading in CPP

This repository has two objectives:
* Demonstrate the concepts of multiple threading through code samples.
* Demonstrate the C++ multi-threading concepts through code samples.

### Some of the concepts demonstrated
* Simple usage of threads to do tasks simulatenously: threads.cpp
* Data race and counters: thread_safe_counters.cpp
* Consumer producer (upcoming): consumer_producer.cpp
* Different types of locking mechanisms: locking.cpp
* Syncing cameras to take pictures simulatenously: sync_devices.cpp, sync_devices_2.cpp
* Check if a function completes within stipulated time or not (upcoming): timeouts.cpp

### Some common threading mistakes and notes
* Trying to join a detached thread or thread that has already been joined. Under uncertainty, use thread member "joinable" to check if thread can be joined or not.
* Trying to acquire a mutex twice.
* Everything is passed by value. Use std::ref to pass argument by reference.
* Unlocked shared data members cause data race if their value is manipulated by threads.
* When using mutex::lock() and mutex::unlock(), forgetting to unlock will cause the resource to not be released.
  