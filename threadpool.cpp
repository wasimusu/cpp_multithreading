/**
 * Suppose we have thousands of jobs and just four threads.
 * We want to use just those threads to do some work.
 * How to synchronize and wait ?
 *
 * */

#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int some_op(int value) {
    int result = value * value;
    // Act like a compute intensive function
    this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
    return result;
}

int main() {
    vector<int> tasks;
    for (int i = 0; i <)
}
