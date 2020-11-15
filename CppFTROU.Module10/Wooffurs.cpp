#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>

const char * CLS = "CLS";
const char * PAUSE = "PAUSE";

typedef struct {
	const char * breed;
	int risk_weight;
	bool subject_to_senior_discount;
	float below_risk_weight;
	float high_risk_weight;
} breed_entry;

typedef struct {
	float base_premium;
	float actual_premium;
	int weight;
	int age;
	bool subject_to_discount;
	char breed_code;
	std::string dog_name;
} household_info;

auto get_breed_entry(std::unordered_map<char, breed_entry> * & schedule, char & breed_code) -> breed_entry * {
	return schedule->find(breed_code) == schedule->end()
		? nullptr
		: &schedule->operator[](breed_code);
}

auto init_schedule(void) -> std::unordered_map<char, breed_entry> * {
	auto schedule = new std::unordered_map<char, breed_entry>();
	schedule->operator[]('p') = breed_entry{ "Pitbull", 20, false, 30.20F, 35.15F };
	schedule->operator[]('d') = breed_entry{ "Doberman", 35, true, 28.16F, 30.00F };
	schedule->operator[]('r') = breed_entry{ "Rottweiler", 45, false, 28.00F, 29.75F };
	schedule->operator[]('g') = breed_entry{ "German Shepherd", 30, true, 27.50F, 29.75F };
	schedule->operator[]('c') = breed_entry{ "Chow Chow", 24, true, 25.10F, 27.50F };
	schedule->operator[]('t') = breed_entry{ "Great Dane", 55, true, 25.10F, 25.20F };
	schedule->operator[]('s') = breed_entry{ "Presa Canario", 45, false, 20.01F, 20.55F };
	schedule->operator[]('k') = breed_entry{ "Akita", NULL, false, 19.75F, 19.75F };
	schedule->operator[]('m') = breed_entry{ "Alaskan Malamute", 38, true, 15.50F, 18.15F };
	schedule->operator[]('h') = breed_entry{ "Husky", 20, true, 9.95F, 12.00F };
	schedule->operator[]('b') = breed_entry{ "Other Breed", 35, true, 4.95F, 8.95F };
	return schedule;
}

auto main(void) -> int
{
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);

	auto schedule = init_schedule();
	auto dog_count = 0;
	auto total_premium = 0.F;

	std::cout << "Please enter the number of dogs in your household: " << std::endl;
	std::cin >> dog_count;

	for (auto i = 0; i < dog_count; i++) {
		std::cin.ignore();

		auto * info = new household_info();

		std::cout << "Enter the name of dog #" << i + 1 << ": " << std::flush;
		std::getline(std::cin, info->dog_name);

		std::cout << "Enter the current age for " << info->dog_name << ":" << std::flush;
		std::cin >> info->age;

		std::cout << "Enter the weight for " << info->dog_name << ":" << std::flush;
		std::cin >> info->weight;

		std::cout << "Enter the breed code for " << info->dog_name << ":" << std::flush;
		std::cin >> info->breed_code;

		auto breed_entry = get_breed_entry(schedule, info->breed_code);
		if (breed_entry == nullptr) {
			std::cout << "Sorry. That is not a valid breed code. Please re-enter this dog's information." << std::flush;
			std::system(PAUSE);
			std::system(CLS);
			delete info;
			i--;
		}
	}

	return EXIT_SUCCESS;
}
