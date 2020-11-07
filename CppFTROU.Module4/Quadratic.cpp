#include <iostream>
#include <cmath>

typedef struct {
	float x1;
	float x2;
} x_vals;

x_vals * calculate_x_values(float & a, float & b, float & c) {
	auto * vals = new x_vals();
	auto pw = _CMATH_::powf(b, 2.F);
	auto rts = _CMATH_::sqrtf(pw - (4.F * a * c));
	auto divsr = 2.F * a;
	vals->x1 = ((rts + b) / divsr) * -1.F;
	vals->x2 = (rts - b) / divsr;
	return vals;
}

int main()
{
	auto a = 0.0F, b = 0.0F, c = 0.0F, x1 = 0.0F, x2 = 0.0F;

	std::cout << "Enter value of 'a': ";
	std::cin >> a;

	std::cout << "Enter value of 'b': ";
	std::cin >> b;

	std::cout << "Enter value of 'c': ";
	std::cin >> c;

	std::cout << std::endl;

	auto vals = calculate_x_values(a, b, c);
	x1 = vals->x1;
	x2 = vals->x2;

	std::cout << "The first value of 'x' is " << x1 << std::endl;
	std::cout << "The second value of 'x' is " << x2 << std::endl;

	return EXIT_SUCCESS;
}
