#ifndef BASIC_H
#define BASIC_H

#include <iostream>
#include <map>
#include <string>

class Base
{
  public:
    void operator() (int x)
    {
      int i = 0;
      for (; i<x; i++)
      {
      }
        std::cout << i << "\n";
    }

    void run(int x)
    {
      int i = 0;
      for (; i<x; i++)
      {
      }
        std::cout << i << "\n";
    }

    static void staticRun(int x)
    {
      int i = 0;
      for (; i<x; i++)
      {
      }
        std::cout << i << "\n";
    }
};


void function1(char symbol);
void function2();

void RefreshForecast(std::map<std::string, int>* forecast_map);

#endif // BASIC_H