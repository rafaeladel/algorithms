#include <iostream>
#include <math.h>

int multiply(int x, int y);
int get_length(int val);

int main()
{
  int x = 0, y = 0;
  long int result = 0;

  std::cout << "Enter x: ";
  std::cin >> x;
  std::cout << "Enter y: ";
  std::cin >> y;

  result = multiply(x, y);
  std::cout << "Result: " << result << std::endl;
  return 0;
}

int multiply(int x, int y)
{
  if(x < 10 || y < 10) {
    return x * y;
  }

  int x_len = get_length(x);
  int y_len = get_length(y);

  int z0 = 0 , z1 = 0, z2 = 0;
  int a = 0, b = 0, c = 0, d = 0;

  a = x / pow(10, x_len/2);
  b = x - (a * pow(10, x_len/2));
  c = y / pow(10, y_len/2);
  d = y - (c * pow(10, y_len/2));

  z0 = multiply(a, c);
  z1 = multiply(b, d);
  z2 = multiply(a+b, c+d);

  return (pow(10, x_len) * z0) + (pow(10, x_len/2) * (z2 - z1 - z0)) + z1;
}

int get_length(int val)
{
  int count = 0;
  while(val > 0) {
    count++;
    val /= 10;
  }
  return count;
}
