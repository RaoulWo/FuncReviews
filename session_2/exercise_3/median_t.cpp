#include <functional>
#include <iostream>

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

auto square_root = [](const double x, const double epsilon = 1e-10, const int max_iterations = 1000) -> double
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
    double result;

    for (int i = 0; i < max_iterations; ++i)
    {
        result = (lower_limit + upper_limit) / 2.0;

        if (result * result > x)
        {
            upper_limit = result;
        }
        else if (result * result < x)
        {
            lower_limit = result;
        }

        if (upper_limit - lower_limit < epsilon)
        {
            break;
        }
    }

    return result;
};

auto calculate_median = [](const double a, const double b, const double c) -> double
{
    return 0.5 * curry3(square_root)(2 * square(b) + 2 * square(c) - square(a))(1e-10)(1000);
};

int main()
{
    double median_a = curry3(calculate_median)(3)(4)(5);
    double median_b = curry3(calculate_median)(4)(3)(5);
    double median_c = curry3(calculate_median)(5)(3)(4);

    std::cout << "Median from vertex A: " << median_a << "\n";
    std::cout << "Median from vertex B: " << median_b << "\n";
    std::cout << "Median from vertex C: " << median_c << "\n";
}
