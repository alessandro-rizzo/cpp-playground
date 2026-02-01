#include <iostream>

// Chapter 2: User-Defined Types exercises and examples

// Exercis 1
struct Rectangle {
  int width;
  int height;
};

void rectangle_init(Rectangle& r, int width, int height) {
  r.width = width;
  r.height = height;
};

int area(Rectangle& r) {
  return r.height * r.width;
};
int perimeter(Rectangle& r) {
  return 2 * r.height + 2 * r.width;
};

class RRectangle {
public:
  RRectangle(int height, int width) : h{height}, w{width} {};
  int area() {
    return h * w;
  };
  int perimeter() {
    return 2 * w + 2 * h;
  };
  bool square() {
    return h == w;
  };

private:
  int h;
  int w;
};

class Complex {
public:
  Complex(float real, float imaginary) : r{real}, i{imaginary} {};
  Complex operator+(Complex& o) {
    return Complex(r + o.r, i + o.i);
  };
  void print() const {
    cout << real;
    if (imag >= 0)
      cout << " + " << imag << "i";
    else
      cout << " - " << -imag << "i";
    cout << endl;
  }

private:
  float r;
  float i;
};

int main() {
  std::cout << "Chapter 2: User-Defined Types\n";
  std::cout << "===============================\n\n";

  Rectangle r;
  rectangle_init(r, 2, 3);
  std::cout << area(r) << '\n';
  std::cout << perimeter(r) << '\n';

  RRectangle rr(2, 3);
  std::cout << rr.area() << '\n';
  std::cout << rr.perimeter() << '\n';
  std::cout << rr.square();

    return 0;
}
