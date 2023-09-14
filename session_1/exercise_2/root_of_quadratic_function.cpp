#include <complex>
#include <iostream>
#include <utility>

typedef std::complex<double> complex;

double square(const double x);
float square_root(const float x);
std::pair<complex, complex> solve_quadratic_equation(const double a, const double b, const double c);

int main() {
	std::pair<complex, complex> result = solve_quadratic_equation(3, 4, 5);
	std::cout << result.first << ", " << result.second << "\n";
}

double square(const double x) {
	double result = x;
	for (int i = 1; i < x; i++)
		result += x;

	return result;
}

inline float square_root(const float x) {
	union Conv {
			float    f;
			uint32_t i;
	};

	Conv conv;
	conv.f = x;
	conv.i = 0x5f3759df - (conv.i >> 1);
	conv.f *= 1.5F - (x * 0.5F * conv.f * conv.f);

	return 1 / conv.f;
}

std::pair<complex, complex> solve_quadratic_equation(const double a, const double b, const double c) {
	double p = b / a;
	double q = c / a;
	double discriminant = square(p) - 4 * q;

	if (discriminant < 0)
		return std::make_pair(complex(-p / 2, square_root(-discriminant) / 2), 
			complex(-p / 2, -square_root(-discriminant) / 2));

	double root = std::sqrt(discriminant);
	double solution = (p > 0) ? (-p - root) / 2 : (-p + root) / 2;

	return std::make_pair(solution, q / solution);
}
