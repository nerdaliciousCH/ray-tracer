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

Color Color::operator+(const Color& other){
    Color new_color(
        r + other.r,
        g + other.g,
        b + other.b
    );
    return new_color;
}

Color Color::operator*(const float factor){
    Color new_color(
        (int)(r*factor),
        (int)(g*factor),
        (int)(b*factor)
    );
    return new_color;
}

Color Color::operator/(const float factor){
    Color new_color(
        (int)(r/factor),
        (int)(g/factor),
        (int)(b/factor)
    );
    return new_color;
}

Color& Color::operator/=(const float factor){
    this->r = (int)(this->r / factor);
    this->g = (int)(this->g / factor);
    this->b = (int)(this->b / factor);
    return *this;
}

void Color::print() {
    std::cout << "red: " << r << "\tgreen: " << g << "\tblue: " << b << std::endl;
}
