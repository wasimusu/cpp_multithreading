/**
 * Description: Run multiple instance of an expensive function simultaneously
 *
 * Usage: Run expensive functions simultaneously.
 *
 * If processing two images are independent, then you can process them simultaneously. You do not have to wait until
 * processing one image is over to process another image. It reduces the total runtime.
 * */

#include <thread>
#include <chrono>
#include <future>
#include <iostream>

using namespace std;
mutex mu;

void compute_factorial(int number) {
  long long result = 1;
  for (size_t i = 2; i <= number; i++) result *= i;

  // Lock resources that are shared between threads.
  // This is not the best way to lock. See readme.
  mu.lock();
  std::cout << "Factorial of " << number << " : " << result << std::endl;
  mu.unlock();
}

int main() {
  int num1 = 5;
  int num2 = 6;

  // Compute factorial of two numbers simultaneously
  thread t1(compute_factorial, num1);
  thread t2(compute_factorial, num2);

  t1.join();
  t2.join();

  return 0;
}