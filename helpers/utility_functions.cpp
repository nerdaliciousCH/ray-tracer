#include "utility_functions.h"

void print_address(void *obj, int bytes, std::string type){
	std::cout << "addr: " << obj << "\tbytes: " << bytes << "\ttype: " << type << std::endl;
}

void print_values(int value) {
	std::cout << "got value: " << value << " at addr: " << &value << std::endl;
}

void sleep(unsigned int millis) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

void print_time_spent(duration<double> time_spent, std::string label) {
	std::cout << label << ": ";
	std::cout << std::fixed << std::setprecision(6) << time_spent.count() * 1000.0f << " ms" << std::endl;
}
