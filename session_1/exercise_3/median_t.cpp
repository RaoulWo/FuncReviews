#include <iostream>

double square(const double x);
double square_root(const double x, const double epsilon, const int max_iterations);
double calculate_median(const double a, const double b, const double c);

int main() {
  double median_a = calculate_median(3, 4, 5);
  double median_b = calculate_median(4, 3, 5);
  double median_c = calculate_median(5, 3, 4);
  std::cout << "Median from vertex A: " << median_a << "\n";
  std::cout << "Median from vertex B: " << median_b << "\n";
  std::cout << "Median from vertex C: " << median_c << "\n";
}

double square(const double x) {
  double result = x;
	for (int i = 1; i < x; i++)
		result += x;

	return result;
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

double calculate_median(const double a, const double b, const double c) {
  return 0.5 * square_root(2 * square(b) + 2 * square(c) - square(a));
}