#include <iostream>
#include <iomanip>

int main(void)
{
	float price1 = 0.0F,
		price2 = 0.0F,
		price3 = 0.0F,
		total = 0.0F;

	std::cout << "Enter a price:" << std::endl;
	std::cin >> price1;

	std::cout << "Enter a price:" << std::endl;
	std::cin >> price2;

	std::cout << "Enter a price:" << std::endl;
	std::cin >> price3;

	total = price1 + price2 + price3;

	std::cout
		<< std::setiosflags(std::ios::fixed) << std::setprecision(2)
		<< std::endl
		<< "Price 1 is" << std::setw(9) << price1 << std::endl
		<< "Price 2 is" << std::setw(9) << price2 << std::endl
		<< "Price 3 is" << std::setw(9) << price3 << std::endl
		<< std::endl
		<< "Total price: " << std::setw(9) << total << std::endl;

	return EXIT_SUCCESS;
}
