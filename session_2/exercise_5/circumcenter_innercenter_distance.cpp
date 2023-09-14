#include <functional>
#include <iostream>
#include <tuple>

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

auto calculate_area_and_radii = [](const double a, const double b, const double c) -> std::tuple<double, double, double>
{
    double s = (a + b + c) / 2;
    double area = curry3(square_root)(s * (s - a) * (s - b) * (s - c))(1e-10)(1000);
    double inradius = area / s;
    double circumradius = (a * b * c) / (4 * area);

    return std::make_tuple(area, inradius, circumradius);
};

auto calculate_distance = [](const double inradius, const double circumradius) -> double 
{
    return curry3(square_root)(circumradius * circumradius - 2 * circumradius * inradius)(1e-10)(1000);
};

int main()
{
    std::tuple<double, double, double> tuple = curry3(calculate_area_and_radii)(3)(4)(5);
    double area = std::get<0>(tuple);
    double inradius = std::get<1>(tuple);
    double circumradius = std::get<2>(tuple);
    double distance = curry2(calculate_distance)(inradius)(circumradius);

    std::cout << "Area: " << area << "\n";
    std::cout << "Inradius: " << inradius << "\n";
    std::cout << "Circumradius: " << circumradius << "\n";
    std::cout << "Distance between circumcenter and incenter: " << distance << "\n";
}
