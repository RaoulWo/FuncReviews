#include <complex>
#include <functional>
#include <iostream>
#include <utility>

typedef std::complex<double> complex;

auto simpleCurry2 = [](const auto func)
{
	return [func](const auto param)
	{
		return std::bind(func, param, std::placeholders::_1);
	};
};

auto simpleCurry3 = [](const auto func)
{
	return [func](const auto param1, const auto param2)
	{
		return std::bind(func, param1, param2, std::placeholders::_1);
	};
};

auto curry2 = [](const auto func)
{
	return simpleCurry2(func);
};

auto curry3 = [](const auto func)
{
	return curry2(simpleCurry3(func));
};

auto square = [](const double x) -> double
{
	return x * x;
};

auto square_root = [](const double x) -> double
{
	if (x < 0)
	{
		return -1;
	}

	if (x == 0)
	{
		return 0;
	}

	double upper_limit = x;
	double lower_limit = 0;
	double result = x / 2;

	while (abs(result * result - x) > 0.00001)
	{
		if (result * result > x)
		{
			upper_limit = result;
		}
		else
		{
			lower_limit = result;
		}

		result = (upper_limit + lower_limit) / 2;
	}

	return result;
};

auto solve_quadratic_equation = [](const double a, const double b, const double c) -> std::pair<complex, complex>
{
	double p = b / a;
	double q = c / a;
	double discriminant = square(p) - 4 * q;

	if (discriminant < 0)
	{
		return std::make_pair(complex(-p / 2, square_root(-discriminant) / 2),
							  complex(-p / 2, -square_root(-discriminant) / 2));
	}

	double root = std::sqrt(discriminant);
	double solution = (p > 0) ? (-p - root) / 2 : (-p + root) / 2;

	return std::make_pair(solution, q / solution);
};

int main()
{
	std::pair<complex, complex> result = curry3(solve_quadratic_equation)(3)(4)(5);

	std::cout << result.first << ", " << result.second << "\n";
}
