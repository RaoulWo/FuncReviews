#include <iostream>
#include <tuple>

double square_root(const double x, const double epsilon, const int max_iterations);
std::tuple<double, double, double> calculate_area_and_radii(const double a, const double b, const double c);
double calculate_distance(const double inradius, const double circumradius);

int main() {
  std::tuple<double, double, double> tuple = calculate_area_and_radii(3, 4, 5);
  double area = std::get<0>(tuple);
  double inradius = std::get<1>(tuple);
  double circumradius = std::get<2>(tuple);
  double distance = calculate_distance(inradius, circumradius);
  std::cout << "Area: " << area << "\n";
  std::cout << "Inradius: " << inradius << "\n";
  std::cout << "Circumradius: " << circumradius << "\n";
  std::cout << "Distance between circumcenter and incenter: " << distance << "\n";
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

std::tuple<double, double, double> calculate_area_and_radii(const double a, const double b, const double c) {
  double s = (a + b + c) / 2;
  double area = square_root(s * (s - a) * (s - b) * (s - c));
  double inradius = area / s;
  double circumradius = (a * b * c) / (4 * area);
  
  return std::make_tuple(area, inradius, circumradius);
}

double calculate_distance(const double inradius, const double circumradius) {
  return square_root(circumradius * circumradius - 2 * circumradius * inradius);
}
