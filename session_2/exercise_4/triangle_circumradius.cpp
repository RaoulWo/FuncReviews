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

auto calculate_circumradius = [](const double a, const double b, const double c) -> double
{
    double s = (a + b + c) / 2;
    double area = curry3(square_root)(s * (s - a) * (s - b) * (s - c))(1e-10)(1000);
    return (a * b * c) / (4 * area);
};

int main()
{
    double circumradius = curry3(calculate_circumradius)(3)(4)(5);

    std::cout << "Circumradius: " << circumradius << "\n";
}
