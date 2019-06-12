#ifndef COLOR_H
#define COLOR_H

#include <iostream>

class Color {
public:
  int r;
  int g;
  int b;
  Color(int r, int g, int b);
  Color(int grayscale);
  Color operator+(const Color& other);
  Color operator/(const float factor);
  Color& operator/=(const float factor);
  void print();
};

#endif
