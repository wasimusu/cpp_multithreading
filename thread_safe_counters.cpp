/**
 * Objective: Build thread safe counters
 * Method: Use atomic types for thread safe operations
 *
 *
 * Also demonstrates the concept of data race.
 * Data race is multiple threads trying to manipulating shared data at once.
 *
 * If we reduce the value to which we are counting, both thread safe and unsafe methods may be able to achieve the
 * intended result. This makes it harder to debug multi-threaded applications.
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

void unsafe_increment() {
  // Does not use atomic counter or locks
  // The value of counter2 could be changed from multiple threads leading to data race and unsafe increment

  for (size_t j = 0; j < 1000000; j++) {
    ++counter2;
  }
}

void safe_increment_atomic() {
  // uses atomic counter to count

  for (int j = 0; j < 1000000; j++) {
    ++counter;
  }
}

// Using locks to avoid data race.
// if you don't lock the increment section of the code, there will be data race to increment
// and update the counter leading to false update of the counter
void safe_increment_lock() {
  for (size_t j = 0; j < 1000000; j++) {
    unique_lock<mutex> lock(mu);
    ++counter3;
  }
}

void thread_safe_counter() {
  // Uses thread safe increment method to count

  // using safe_increment_lock will also work
  std::thread t1(safe_increment_atomic);
  std::thread t2(safe_increment_atomic);
  t1.join();
  t2.join();
  assert(counter == 2 * 1000000);
  cout << "safe counter:\t" << counter << "\tTarget value 2000000" << endl;
}

void thread_unsafe_counter() {
  // Uses thread unsafe increment method to count

  std::thread t1(unsafe_increment);
  std::thread t2(unsafe_increment);
  t1.join();
  t2.join();
  assert(counter2 <= 2 * 1000000);
  cout << "Unsafe counter:\t" << counter2 << "\tTarget value 2000000" << endl;
}

int main() {
  thread_safe_counter();
  thread_unsafe_counter();
  return 0;
}