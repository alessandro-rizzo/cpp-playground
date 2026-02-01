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

int main() {
  std::cout << "Chapter 2: User-Defined Types\n";
  std::cout << "===============================\n\n";

  Rectangle r;
  rectangle_init(r, 2, 3);
  std::cout << area(r) << '\n';
  std::cout << perimeter(r) << '\n';
  m return 0;
}
