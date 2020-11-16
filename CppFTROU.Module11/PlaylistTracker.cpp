#include "PlaylistTracker.hpp"

#include <iostream>

using namespace playlist_tracker;

auto create_playlist(void) -> void {
	// to-do
	std::cout << std::endl << "auto create_playlist(void) -> void" << std::endl;
}

auto playlist_tracker(void) -> void {
	char op = '\0';
	while (op != constants::options::EXIT_OPTION) {
		std::cout << "Main Menu" << std::endl << std::endl << std::flush;
		std::cout << "- Press [" << constants::options::CREATE_PLAYLIST_OPTION << "] to create a new playlist." << std::endl << std::flush;
		std::cout << "- Press [" << constants::options::EXIT_OPTION << "] to exit program." << std::endl << std::endl << std::flush;
		std::cout << "Your choice: " << std::flush;
		std::cin >> op;
		std::cout << std::endl << op << std::endl;
		if (op == constants::options::EXIT_OPTION)
			break;
		else if (op == constants::options::CREATE_PLAYLIST_OPTION)
			create_playlist();
		else
			std::cout << std::endl << "Unknown option, try again..." << std::endl << std::endl;

		std::system(constants::terminal::PAUSE);
		std::system(constants::terminal::CLS);
	}
	std::cout << std::endl << "Farewell!" << std::endl;
}
