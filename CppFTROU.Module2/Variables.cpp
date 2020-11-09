#include <iostream>
#include <ctime>
#include <random>

const unsigned int MINUTES_PER_HOUR = 60;
const unsigned int MAX_HOURS_RANGE = 24;

int main(void)
{
	std::srand(time(0));

	auto numHours = (std::rand() % MAX_HOURS_RANGE) + 1;

	// MINUTES_PER_HOUR++;
	numHours++;

	auto numMins = numHours * MINUTES_PER_HOUR;

	std::cout << "There are " << numMins << " minutes in " << numHours << " hours." << std::endl;

	unsigned int zeroHour = 0;
	zeroHour--;

	std::cout << "1 hour before zero hour is " << zeroHour << std::endl;

	return EXIT_SUCCESS;
}
