#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <ratio>
#include <ctime>
#include <thread>

using namespace std::chrono;

void print_address(void *obj, int bytes, std::string type);

void print_values(int value);

void sleep(unsigned int millis);

void print_time_spent(duration<double> time_spent, std::string label);
