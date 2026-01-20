#include <iostream>

double celsius_to_fahrenheit(double const c) { return (c * 9.0 / 5.0) + 32.0; }

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

int sum_array(int arr[], int size) {
  int sum = 0;
  for (auto n = 0; n < size; ++n) {
    sum += arr[n];
  }
  return sum;
}

int sum_array_ptr(int *arr, int size) {
  int sum = 0;
  for (auto n = 0; n < size; ++n) {
    sum += *(arr + n);
  }
  return sum;
}

int count_char(const char *str, char c) {
  int count = 0;
  while (*str) {
    if (*str == c) {
      count++;
    }
    str++;
  }
  return count;
}

constexpr int factorial(int i){
  if (i==0) {return 1;}
  return i * factorial(i-1);
}

int max(int x, int y){
  if (x>=y) return x;
  return y;
}

double max(double x, double y){
  if (x>=y) return x;
  return y;
}

void mini_calculator() {
  std::cout << "\nMini Calculator\n";
  std::cout << "Enter expression (e.g., 10 + 5): ";
  double a, b;
  char op;
  std::cin >> a >> op >> b;

  switch (op) {
    case '+':
      std::cout << a << " + " << b << " = " << a + b << "\n";
      break;
    case '-':
      std::cout << a << " - " << b << " = " << a - b << "\n";
      break;
    case '*':
      std::cout << a << " * " << b << " = " << a * b << "\n";
      break;
    case '/':
      if (b == 0) {
        std::cout << "Error: division by zero\n";
      } else {
        std::cout << a << " / " << b << " = " << a / b << "\n";
      }
      break;
    default:
      std::cout << "Error: invalid operator '" << op << "'\n";
      break;
  }
}

int main() {
  std::cout << "Temperature Converter\n";
  double celsius;
  std::cout << "Enter temperature in Celsius: ";
  std::cin >> celsius;
  double fahrenheit = celsius_to_fahrenheit(celsius);
  std::cout << celsius << " Celsius is " << fahrenheit << " Fahrenheit.\n";

  int x = 5, y = 10;
  std::cout << "Before swap: x = " << x << ", y = " << y << "\n";
  swap(x, y);
  std::cout << "After swap: x = " << x << ", y = " << y << "\n";

  int arr[] = {1, 2, 3, 4, 5};
  int size = sizeof(arr) / sizeof(arr[0]);
  std::cout << "Sum of array elements: " << sum_array(arr, size) << "\n";

  std::cout << "Sum of array elements using pointer: "
            << sum_array_ptr(arr, size) << "\n";

  const char *myString = "hello world";
  std::cout << "Number of 'l' in \"" << myString
            << "\": " << count_char(myString, 'l') << "\n";
  
  int num = 5;
  constexpr int num_const = 5;
  constexpr int fact = factorial(num_const);
  std::cout << "Factorial of " << num << " is " << factorial(num) << "\n";  

  int c = {7}, d = {10};
  double a = 5.5, b = 3.3;
  std::cout << "Max of " << c << " and " << d << " is " << max(c, d) << "\n";
  std::cout << "Max of " << a << " and " << b << " is " << max(a, b) << "\n";

  int array[] = {1,2,3,4,5};
  for (auto& i:array){
    i=i*2;
    std::cout << i << "\n";
  }

  mini_calculator();

  return 0;
}
