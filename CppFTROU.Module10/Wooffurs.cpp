#include "BreedingConstraints.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>

const char * CLS = "CLS";
const char * PAUSE = "PAUSE";

auto get_breed_entry(
	std::unordered_map<char, breeding::breed_entry> * & schedule,
	char & breed_code) -> breeding::breed_entry * {
	return schedule->find(breed_code) == schedule->end()
		? nullptr
		: &schedule->operator[](breed_code);
}

auto init_schedule(void) -> std::unordered_map<char, breeding::breed_entry> * {
	auto schedule = new std::unordered_map<char, breeding::breed_entry>();
	schedule->operator[]('p') = breeding::breed_entry{ "Pitbull", 20, false, 30.20F, 35.15F };
	schedule->operator[]('d') = breeding::breed_entry{ "Doberman", 35, true, 28.16F, 30.00F };
	schedule->operator[]('r') = breeding::breed_entry{ "Rottweiler", 45, false, 28.00F, 29.75F };
	schedule->operator[]('g') = breeding::breed_entry{ "German Shepherd", 30, true, 27.50F, 29.75F };
	schedule->operator[]('c') = breeding::breed_entry{ "Chow Chow", 24, true, 25.10F, 27.50F };
	schedule->operator[]('t') = breeding::breed_entry{ "Great Dane", 55, true, 25.10F, 25.20F };
	schedule->operator[]('s') = breeding::breed_entry{ "Presa Canario", 45, false, 20.01F, 20.55F };
	schedule->operator[]('k') = breeding::breed_entry{ "Akita", NULL, false, 19.75F, 19.75F };
	schedule->operator[]('m') = breeding::breed_entry{ "Alaskan Malamute", 38, true, 15.50F, 18.15F };
	schedule->operator[]('h') = breeding::breed_entry{ "Husky", 20, true, 9.95F, 12.00F };
	schedule->operator[]('b') = breeding::breed_entry{ "Other Breed", 35, true, 4.95F, 8.95F };
	return schedule;
}

auto main(void) -> int
{
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);

	auto schedule = init_schedule();
	auto household = new std::unordered_map<const char *, breeding::dog *>();
	auto dog_count = 0;
	auto total_premium = 0.0F;

	std::string dog_name;
	int age;
	float weight;
	char breed_code;

	std::cout << "Please enter the number of dogs in your household: ";
	std::cin >> dog_count;
	std::cout << std::endl;

	for (auto i = 0; i < dog_count; i++) {
		std::cin.ignore();

		std::cout << "Enter the name of dog #" << i + 1 << ": " << std::flush;
		std::getline(std::cin, dog_name);

		auto name = dog_name.c_str();

		std::cout << "Enter the breed code for " << name << ": " << std::flush;
		std::cin >> breed_code;

		auto breed_entry = get_breed_entry(schedule, breed_code);
		if (breed_entry == nullptr) {
			std::cout << "Sorry. That is not a valid breed code. Please re-enter this dog's information." << std::flush;

			std::system(PAUSE);
			std::system(CLS);
			i--;
			continue;
		}

		auto has_prefix = breed_entry->breed[0] == 'A'
			|| breed_entry->breed[0] == 'E'
			|| breed_entry->breed[0] == 'I'
			|| breed_entry->breed[0] == 'O'
			|| breed_entry->breed[0] == 'U';
		std::cout << std::endl << name << " is a" << (has_prefix ? "n" : "") << " " << breed_entry->breed << "!"
			<< std::endl << std::endl << std::flush;

		std::cout << "Enter the current age for " << name << ": " << std::flush;
		std::cin >> age;

		std::cout << "Enter the weight for " << name << " (nearest kg): " << std::flush;
		std::cin >> weight;

		auto dog = breed_entry->breed != "Akita"
			? breeding::factory::get_dog(name, age, weight, *breed_entry)
			: breeding::factory::get_other_dog(name, age, weight, *breed_entry);
		household->operator[](name) = dog;

		std::cout << "The monthly premium for " << name << " is " << dog->get_premium() << "."
			<< std::endl << std::endl << std::flush;

		total_premium += dog->get_premium();

		std::system(PAUSE);
		std::system(CLS);
	}

	std::cout << "The total monthly premium for all dogs is " << total_premium << std::endl << std::endl;

	return EXIT_SUCCESS;
}
