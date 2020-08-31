/**
 * https://web.stanford.edu/~ouster/cgi-bin/cs140-spring14/lecture.php?topic=locks
 * Description of a simple Producer Consumer Pattern
 *
 * You're capturing images from a camera. It takes about 10ms.
 * You can store the images in a queue.
 * You run facial recognition on each of the frames which is compute intensive and takes about 30ms.
 * The results of the facial recognition function can be used by another function which is also a consumer.
 * Thus there can be multiple consumers stacked together.
 * The consumers have to wait until there are items in the queue to process.
 * Each consumer consumes data from separate queue.
 * In some cases, the inputs and outputs need to be serialized.
 *
 * Keep in mind that queues may exhaust the memory if the program runs long enough and consumers are not able to keep up
 * with the producers.
 * */

#include <iostream>
#include <thread>
#include <condition_variable>
#include <queue>
#include <chrono>

using namespace std;

queue<int> images;
queue<int> grayscale_images;
queue<int> results;
bool done = false; // are we done capturing images?

/**
 * Captures image from camera with camera_id
 * Stores it in consumer
 * */
void capture_image(int device_id) {
    while (!done) {
        this_thread::sleep_for(chrono::milliseconds(rand() % 10));

        // Actually capture the image from a camera.
        int image = rand() % 1000;

        images.push(image);
    }
}


/**
 * Consumes the images from queue and converts them into grayscale image.
 * Stores the results into queue called grayscale_images
 * */
void to_grayscale() {
    // Wait until there are images to process
    while (images.empty()) this_thread::yield();

    this_thread::sleep_for(chrono::milliseconds(rand() % 5));

    // Consume image and convert them into grayscale
    int image = images.front();
    images.pop();
    int grayscale = image % 20;
    grayscale_images.push(grayscale);
}

/**
 * Consumes grayscale image and runs facial recognition on them.
 * Stores the results into results queue
 * */
void face_recognition() {
    // Wait until there are images to process
    while (!grayscale_images.empty()) this_thread::yield();

    this_thread::sleep_for(chrono::milliseconds(rand() % 5));

    // Consume grayscale image and run facial recognition
    int grayscale = grayscale_images.front();
    grayscale_images.pop();
    int people_detected = (grayscale % 5) * 2 + 1;
    results.push(grayscale);
}

int main() {
    return 0;
}