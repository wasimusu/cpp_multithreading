/**
 * Problem: You've stereo cameras and need to captures images simulatenously.
 * Hell, you might as well have many cameras like the smartphones do and need to sync them.
 *
 * Solution: Synchronize the capture_image function
 * Method: Use condition_variable for sync
 *
 * Two ways to go about it.
 * Sync using yield or condition variable
 *
 * Result: Without sync, the difference between start time is 6-7 digits.
 * With sync, the difference between start time is 5-6 digits.
 * */

#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>

using namespace std;

bool capture(false);
condition_variable cv;
std::mutex mu;

void capture_image(const int device_id) {
    std::unique_lock<std::mutex> lock(mu);

    while (!capture) cv.wait(lock);

    std::cout << "Camera " << device_id << " clicked at " << chrono::system_clock::now().time_since_epoch().count()
              << std::endl;
    lock.unlock();

    // Pretend to do some work (capture image)
    this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
}

int main() {
    // Syncing two cameras. We can sync multiple cameras as well.
    thread t1(capture_image, 1);
    thread t2(capture_image, 2);

    {
        std::unique_lock<std::mutex> lock(mu);
        capture = true;
        cv.notify_all();
    }

    t1.join();
    t2.join();

    return 0;
}