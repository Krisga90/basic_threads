#include <iostream>
#include <thread>

#include <chrono>
#include <map>
#include <mutex>
#include <string>

#include "basic.h"

int value = 0;
std::mutex m;
std::timed_mutex tm;
std::recursive_mutex rm;

void example1();
void example2();
void example3();
void example4(void (*fun1)(int), void (*fun2)(int));
void example5(void (*fun1)(int, char), void (*fun2)(int, char));

void add(int times);
void addWithMutex(int times);
void addWithTry_lock(int times);
void addWithTry_lock_for(int times);
void printWithRecursiveMutex(int times, char ch);
void printWithoutMutex(int times, char ch);
void printLockGuard(int times, char ch);

int main() {
  using namespace std::chrono;
  // start counting time
  auto start = high_resolution_clock::now();

  // your code here

//     example4(addWithMutex, addWithMutex);

//   example4(addWithTry_lock, addWithTry_lock);
  
//   example5(printWithRecursiveMutex, printWithRecursiveMutex);
  example5(printLockGuard, printLockGuard);

  
  

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

void example4(void (*fun1)(int), void (*fun2)(int)) {
    int count_to = 1000000;
    value = 0;
  // no mutex
  std::thread t1(add, count_to);
  std::thread t2(add, count_to);

  t1.join();
  t2.join();

  std::cout << value << std::endl;
  // end no mutex;
  value = 0;
  //   with mutex
  std::thread t3(fun1, count_to);
  std::thread t4(fun2, count_to);

  t3.join();
  t4.join();

  std::cout << value << std::endl;
}

void example5(void (*fun1)(int, char), void (*fun2)(int, char))
{
    int times  = 100;
    std::thread t1(fun1, times, 'x');
    std::thread t2(fun2, times, 'o');

    t1.join();
    t2.join();
    std::cout << value <<std::endl;
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

void addWithTry_lock(int times) {
  for (int i = 0; i < times; i++) {
    if (m.try_lock()) {
      value++;
      m.unlock();
    }
  }
}

void addWithTry_lock_for(int times)
{
    for (int i = 0; i < times; i++) {
    if (tm.try_lock_for(std::chrono::nanoseconds(10))) {
    //   std::this_thread::sleep_for(std::chrono::nanoseconds(5));
      value++;
      tm.unlock();
    }
    }
}

void addWithRecursiveMutex(int times)
{
    times--;
    if(times>0)
        addWithRecursiveMutex(times);
    rm.lock();
    value++;
    rm.unlock();    //bad example, it could be changed with normal mutex
}


void printWithRecursiveMutex(int times, char ch)
{
    if(times==0)
    {   
        std::cout<<'\n';
        return;
    }
    rm.lock();
    value++;
    std::cout <<ch << ", ";
    printWithRecursiveMutex(--times, ch);
    rm.unlock();
}

void printWithoutMutex(int times, char ch)
{
    if(times==0)
    {   
        std::cout<<'\n';
        return;
    }
    value++;
    std::cout <<ch << ", ";
    printWithoutMutex(--times, ch);
}

void printLockGuard(int times, char ch)
{
    std::lock_guard<std::mutex> lg(m);
    for (; times > 0; times--)
    {   
        value++;
        std::cout <<ch << ", ";
    }
    std::cout<<'\n';
}