#include <iostream>

double square_root(const double x, const double epsilon, const int max_iterations);
double calculate_circumradius(const double a, const double b, const double c);

int main() {
  double circumradius = calculate_circumradius(3, 4, 5);
  std::cout << "Circumradius: " << circumradius << "\n";
}

double square_root(const double x, const double epsilon = 1e-10, const int max_iterations = 1000) {
  if (x < 0) return - 1;
  if (x == 0) return 0;

  double upper_limit = x;
  double lower_limit = 0;
  double result;

  for (int i = 0; i < max_iterations; ++i) {
    result = (lower_limit + upper_limit) / 2.0;

    if (result * result > x)
      upper_limit = result;
    else if (result * result < x)
      lower_limit = result;

    if (upper_limit - lower_limit < epsilon)
      break;
  }

  return result;
}

double calculate_circumradius(const double a, const double b, const double c) {
  double s = (a + b + c) / 2;
  double area = square_root(s * (s - a) * (s - b) * (s - c));
  return (a * b * c) / (4 * area);
}