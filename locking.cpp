/**
 * Objective: Demonstrate different types of locking.
 *
 * Why do we require locking?
 *
 * 1. If there are multiple threads doing console output, the output would be gibberish
 * because multiple threads are writing to the console at the same time.
 *
 * 2. If multiple threads are incrementing the same value without locking, there will be data race.
 * It means the value may be incremented just once after being called by multiple threads which is not desirable.
 *
 * Tips:
 * 1. Lock resources that you're going to change/write.
 * 2. Read-only resources do not need to be locked.
 * */

#include <thread>
#include <iostream>
#include <mutex>

using namespace std;

// Mutex must be global
mutex m1;

void some_op_1() {
  // do some task
  this_thread::sleep_for(chrono::milliseconds(rand() % 100));

  m1.lock();

  // do some more task
  cout << "Resource locked" << endl;

  // If any code before unlocking throws exception, then mutex is never unlocked.
  m1.unlock();

  // If you forget to unlock the mutex or an exception is thrown, other threads can't access the resource.
}

// Using lock_guard, unique_lock or scoped_lock is preferred over using mutex lock and unlock.
void some_op_2() {

  unique_lock<mutex> lock(m1);

  // do some more task
  cout << "Resource locked" << endl;

  // All of these work: lock_guard, scoped_lock, unique_lock
  // The locks are unlocked automatically when they go out of scope.
}

int main() {
  thread t1(some_op_1);
  thread t2(some_op_2);
  t1.join();
  t2.join();
  return 0;
}