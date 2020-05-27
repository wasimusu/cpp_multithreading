/**
 * Build thread safe counters
 * Use atomic types for thread safe operations
 *
 *
 * Also demonstrates the concept of data race.
 * Data race is multiple threads trying to manipulating shared data at once.
 * */

#include <atomic>
#include <thread>
#include <cassert>
#include <iostream>
#include <mutex>

using namespace std;

std::atomic<int> counter(0);
int counter2 = 0; // to demonstrate data race
int counter3 = 0; // to demonstrate locks to prevent data race as an alternative to atomics
mutex mu;

void increment_counter() {
    for (int j = 0; j < 1000; j++) {
        this_thread::sleep_for(chrono::milliseconds(rand() % 10));
        ++counter;
    }
}

void increment_counter2() {
    for (size_t j = 0; j < 1000; j++) {
        this_thread::sleep_for(chrono::milliseconds(rand() % 10));
        ++counter2;
    }
}

// Using locks to avoid data race.
// if you don't lock the increment section of the code, there will be data race to increment
// and update the counter leading to false update of the counter
void increment_counter3() {
    for (size_t j = 0; j < 1000; j++) {
        this_thread::sleep_for(chrono::milliseconds(rand() % 10));
        unique_lock<mutex> lock(mu);
        ++counter3;
    }
}

void thread_safe_counter() {
    std::thread t1(increment_counter3);
    std::thread t2(increment_counter3);
    t1.join();
    t2.join();
    assert(counter == 2000);
    cout << "safe counter:\t" << counter << "\tTarget value 2000" << endl;
}

void thread_unsafe_counter() {
    std::thread t1(increment_counter2);
    std::thread t2(increment_counter2);
    t1.join();
    t2.join();
    assert(counter2 <= 2000);
    cout << "Unsafe counter:\t" << counter2 << "\tTarget value 2000" << endl;
}

int main() {
    thread_safe_counter();
    thread_unsafe_counter();
    return 0;
}