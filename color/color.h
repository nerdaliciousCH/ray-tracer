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
  void print();
};

#endif
