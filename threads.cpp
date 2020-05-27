/**
 * Collecting returns from functions
 * You don't have to change your function to collect the value returned by the function
 *
 * Use future to collect the value.
 * */
#include <iostream>
#include <thread>
#include <future>

using namespace std;

int some_op(int value) {
    // Pretend to do some compute intensive task
    this_thread::sleep_for(chrono::milliseconds(rand() % 1000));

    // Don't worry about overflow here.
    return value * value;
}


int main() {
    int x1 = 4, x2 = 5;
    future<int> f1 = async(launch::async, some_op, x1);
    auto f2 = async(launch::async, some_op, x2);
    cout << "Square of " << x1 << ": " << f1.get() << endl;
    cout << "Square of " << x2 << ": " << f2.get() << endl;
    return 0;
}
