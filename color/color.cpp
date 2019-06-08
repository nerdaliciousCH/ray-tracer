#include "color.h"

Color::Color(int r, int g, int b) :
r(r),
g(g),
b(b){

}

void Color::print() {
    std::cout << "red: " << r << "\tgreen: " << g << "\tblue: " << b << std::endl;
}
