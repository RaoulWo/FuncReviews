#include <iostream>

double square(const double x);
double square_root(const double x);
double pythagoras(const double x, const double y);

int main() {
	int hypothenuse = pythagoras(3, 4);	
	std::cout << "Length of the hypothenuse: " << hypothenuse << "\n";
}

double square(const double x) {
	double result = x;
	for (int i = 1; i < x; i++)
		result += x;

	return result;
}

double square_root(const double x) {
	if (x == 0) return 0;

	double upper_limit = x;
	double lower_limit = 0;
	double result = x / 2;

	while (abs(result * result - x) > 0.00001) {
		if (result * result > x)
			upper_limit = result;
		else
			lower_limit = result;

		result = (upper_limit + lower_limit) / 2;
	}

	return result;
}

double pythagoras(const double x, const double y) {
	return square_root(square(x) + square(y));
}
