#include <iostream>

int num_guessing(int & l, int & h) { return l + ((h - l) * 0.5); }

int main()
{
	auto highest = 100, lowest = 0, attempts = 0, guess = 0;
	auto op = ' ';

	std::cout << "Think of a number between 1 and 100." << std::endl;

	while (true) {
		attempts++;

		std::cout
			<< std::endl
			<< "I guess '" << (guess = num_guessing(lowest, highest)) << "'. Am I right?" << std::endl
			<< "'q' to quit, 'y' if correct, 'h' if too high and 'l' if too low" << std::endl
			<< std::endl;
		std::cin >> op;
		std::cout << std::endl;

		if (op == 'y' || op == 'Y') {
			std::cout << "I guess it in " << attempts << " attempts." << std::endl;
			break;
		}
		else if (op == 'h' || op == 'H') highest = guess;
		else if (op == 'l' || op == 'L') lowest = guess;
		else if (op == 'q' || op == 'Q') {
			std::cout << "You quit. Bye." << std::endl;
			break;
		}
		else std::cout << "I didn't understand that response." << std::endl;
	}

	return attempts;
}
