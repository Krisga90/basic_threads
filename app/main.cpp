#include <iostream>
#include <thread>

#include <chrono>
#include <map>
#include <string>

#include "basic.h"

void example1();
void example2();
void example3();

int main() {
  using namespace std::chrono;
  // start counting time
  auto start = high_resolution_clock::now();

  // your code here

  example3();

  // end your code;

  // finish counting time3
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << "\ntime elapsed: " << duration.count() << " micro s"
            << std::endl;
  return 0;
}

void example1() {
  std::cout << "main thread id " << std::this_thread::get_id() << std::endl;
  std::thread worker1(function1, 'O');
  std::thread worker2(function2);

  worker1.join();
  worker2.join();
}

void example2() {
  std::map<std::string, int> forecast_map = {
      {"New York", 15}, {"Mumbai", 20}, {"Berlin", 11}};

  std::thread bg_worker(RefreshForecast, &forecast_map);

  std::cin.get();
  bg_worker.detach();
}

void example3() {
  Base b;
  int value = 7000;

  // using lambda
  std::thread worker1([value]() {
    int i = 0;
    for (; i < value; i++) {
    }
    std::cout << i << "\n";
  });

  // using functor
  std::thread worker2(b, value);

  // using object function
  std::thread worker3(&Base::run, &b, value);

  // using class function
  std::thread worker4(&Base::staticRun, value);

  worker1.join();
  worker2.join();
  worker3.join();
  worker4.join();
}
