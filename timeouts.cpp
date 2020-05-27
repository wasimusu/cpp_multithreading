/**
 * You want to test whether the user code/function runs within stipulated time and want to timeout if it does not.
 *
 * Usage: All compettive coding platforms implement timeouts to indicate if a program was too slow.
 * */

#include <thread>
#include <chrono>
#include <future>
#include <iostream>

using namespace std;


void user_function() {
    // Act busy. Act like you're some compute intensive function
    this_thread::sleep_for(chrono::milliseconds(rand() % 500));
}

int main() {

    for (int i = 0; i < 10; i++) {

        auto f1 = async(std::launch::async, user_function);
        auto status = f1.wait_for(chrono::milliseconds(300));

        if (status == future_status::ready) {
            cout << "Completed in time" << endl;
        } else {
            cout << "Timelimit exceeded!" << endl;
        }
    }

    return 0;

}