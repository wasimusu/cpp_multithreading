/**
 * Description: Deadlock occurs when two threads are waiting each other to release resources.
 *
 * Cause: If two thread acquire mutexes in different order, they cause deadlock.
 *
 * Solution1: Acquire mutexes in same order.
 *
 * */

#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>

using namespace std;

mutex mu1, mu2;

void some_op() {
  mu1.lock();
  mu2.lock();

  // Do some work
  this_thread::sleep_for(chrono::milliseconds(rand() % 100));

  mu1.unlock();
  mu2.unlock();
}

void some_other_op() {
  mu2.lock();
  mu1.lock();

  // Do some work
  this_thread::sleep_for(chrono::milliseconds(rand() % 100));

  // This order is irrelevant to the deadlock
  mu1.unlock();
  mu2.unlock();
}

int main() {
  return 0;
}