#include <iostream>
#include <thread>

#include <chrono>
#include <map>
#include <mutex>
#include <string>

#include "basic.h"

int value = 0;
std::mutex m;

void example1();
void example2();
void example3();
void example4();

void add(int times);
void addWithMutex(int times);

int main() {
  using namespace std::chrono;
  // start counting time
  auto start = high_resolution_clock::now();

  // your code here

  example4();

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

  worker4.detach();

  // use when you are not sure if you can join
  if (worker4.joinable()) {
    worker4.join();
    std::cout << "\n\njoin4() \n\n";
  }
  worker1.join();
  worker2.join();
  worker3.join();
}

void example4() {

  // no mutex
  std::thread t1(add, 100000);
  std::thread t2(add, 100000);

  t1.join();
  t2.join();

  std::cout << value << std::endl;
  // end no mutex;

  //   with mutex
  value = 0;
  std::thread t3(addWithMutex, 100000);
  std::thread t4(addWithMutex, 100000);

  t3.join();
  t4.join();

  std::cout << value << std::endl;
}

void add(int times) {
  for (int i = 0; i < times; i++)
    value++;
}

void addWithMutex(int times) {
  for (int i = 0; i < times; i++) {
    m.lock();
    value++;
    m.unlock();
  }
}
