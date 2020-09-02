/**
 * Objective: Demonstrate data race.
 *
 * Definition: Data race is multiple threads trying to manipulate shared data at the same time.
 * For instance, if two threads are trying to increment the same counter the counter may be incremented by 1 or 2
 * which is not a desirable outcome when in fact the counter should be incremented by 2.
 *
 * To resolve this see: thread_safe_counters.cpp
 *
 * */

#include <thread>
#include <cassert>
#include <iostream>
#include <mutex>

using namespace std;

int counter2 = 0; // to demonstrate data race
mutex mu;

void unsafe_increment() {
  // Does not use atomic counter or locks
  // The value of counter2 could be changed from multiple threads leading to data race and unsafe increment

  for (size_t j = 0; j < 1000000; j++) {
    ++counter2;
  }
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
  thread_unsafe_counter();
  return 0;
}