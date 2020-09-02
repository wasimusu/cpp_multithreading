/**
 * Description: Multi-threading is used to achieve full resource utilization that single-threaded applications cannot achieve.
 * For instance, if processing a single image at a time is only taking up on 20% of the CPU resource, then processing 4 or 5 images
 * simulatenously may lead to full utilization of the CPU resource and shorter wait time for users.
 *
 * Also, if your program has separate independent functions instead of waiting for function to finish to execute other
 * functions in a serial fashion, you can execute all of the functions in parallel using multi-threading.
 * */

#include <thread>
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