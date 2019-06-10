#include "color.h"

Color::Color(int r, int g, int b) :
r(r),
g(g),
b(b){

}

Color::Color(int grayscale) :
    r(grayscale),
    g(grayscale),
    b(grayscale) {

}

void Color::print() {
    std::cout << "red: " << r << "\tgreen: " << g << "\tblue: " << b << std::endl;
}
