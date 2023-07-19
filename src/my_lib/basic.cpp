#include "basic.h"

#include <chrono>
#include <iostream>
#include <thread>


void RefreshForecast(std::map<std::string, int> *forecast_map)
{
    using namespace std::chrono_literals;

    while(true)
    {   
        for(auto& item : *forecast_map)
        {
            item.second++;
            std::cout << item.first << " temperature is " << item.second << std::endl;
        }
        std::this_thread::sleep_for(2s);
    }
}

void function1(char symbol) {
    std::cout << "function1 thread id " << std::this_thread::get_id() <<std::endl;
  for (int i = 0; i < 500; i++) {
    std::cout << symbol;
  }
}

void function2() {
    std::cout << "function2 thread id " << std::this_thread::get_id() <<std::endl;
  for (int i = 0; i < 500; i++) {
    std::cout << "+";
  }
}