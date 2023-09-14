#include <functional>
#include <iostream>

auto simpleCurry2 = [](const auto func)
{
	return [func](const auto param)
	{
		return std::bind(func, param, std::placeholders::_1);
	};
};

auto curry2 = [](const auto func)
{
	return simpleCurry2(func);
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

auto pythagoras = [](const double x, const double y) -> double 
{
	return square_root(square(x) + square(y));
};

auto curried_pythagoras = [](const double x) -> std::function<double(double)>
{
	return [x](const double y)
	{
		return square_root(square(x) + square(y));
	};
};

auto partial_application_curried_pythagoras = [](const double x)
{
	return std::bind(pythagoras, x, std::placeholders::_1);
};

int main()
{
	int hypothenuse = curry2(pythagoras)(3)(4);

	std::cout << "Length of the hypothenuse: " << hypothenuse << "\n";
}
