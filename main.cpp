#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <ratio>
#include <ctime>
#include <thread>

using namespace std::chrono;

void sleep(unsigned int millis) {
	std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

void print_time_spent(duration<double> time_spent) {
	std::cout << std::fixed << std::setprecision(6) << time_spent.count() * 1000000.0f << " nanos" << std::endl;

}

int intGlobal = 42;

void print_address(void *obj, int bytes, std::string type){
	std::cout << "addr: " << obj << "\tbytes: " << bytes << "\ttype: " << type << std::endl;
}

void print_values(int value) {
	std::cout << "got value: " << value << " at addr: " << &value << std::endl;
}

void play_with_vars() {
	int intVar = 10;
        float floatVar = 12;
        print_address(&intVar, sizeof(intVar), "int (local)");
        print_address(&floatVar, sizeof(floatVar), "float (local)");
        print_address(&intGlobal, sizeof(intGlobal), "int (global)");
        print_values(intVar);
}

int main(int argc, char *argv[]) {

	int dim = std::stoi(argv[1]);
	int index = 0;
	typedef std::chrono::high_resolution_clock Clock;

	int *heap_array = (int *)malloc(dim*dim*sizeof(int));

	auto t1 = Clock::now();

	for(int i = 0; i < dim; i++){
               for(int j = 0; j < dim; j++){
		       index = i*dim+j;
                       heap_array[index] = index;
		}
        }

	auto t2 = Clock::now();
	auto time_spent = duration_cast<duration<double>>(t2 - t1);
	print_time_spent(time_spent);

	int *heap_array2 = (int *)malloc(dim*dim*sizeof(int));

	t1 = Clock::now();

	for(int i = 0; i < dim; i++) {
		for(int j = 0; j < dim; j++){
			index = j*dim+i;
			heap_array2[index] = index;
		}
	}

	t2 = Clock::now();

	auto time_spent2 = duration_cast<duration<double>>(t2 - t1);
	print_time_spent(time_spent2);

	return 0;
}
