#include <iostream>

int main(void)
{
	int greenBottles = 10;
	std::cout << "There were " << greenBottles-- << " green bottles." << std::endl;
	std::cout << "There were " << greenBottles << " green bottles." << std::endl;

	return EXIT_SUCCESS;
}
