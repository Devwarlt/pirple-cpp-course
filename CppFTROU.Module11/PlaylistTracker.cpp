#include "PlaylistTracker.hpp"

#include <iostream>

using namespace playlist_tracker;

auto base::utils::tracker_parsing::trim_by_pattern(
	const char * & pattern, std::string & input, track * & track) -> void
{
	auto pos = input.find(pattern);
	auto a = new base::utils::input_args_info();
	auto b = new base::utils::input_args_info();
	a->from = 0;
	a->to = pos;
	b->from = pos + std::strlen(pattern);
	b->to = input.length();
	track->title = pattern == constants::separators::SEPARATOR_1
		? input.substr(b->from, b->to)
		: input.substr(a->from, a->to);
	track->artist = pattern == constants::separators::SEPARATOR_1
		? input.substr(a->from, a->to)
		: input.substr(b->from, b->to);
}

auto base::utils::tracker_parsing::make_tracker(std::string & input) -> track *
{
	auto track = new base::track();
	auto sep_1 = input.find(constants::separators::SEPARATOR_1) == std::string::npos;
	auto sep_2 = input.find(constants::separators::SEPARATOR_2) == std::string::npos;
	auto sep_3 = input.find(constants::separators::SEPARATOR_3) == std::string::npos;
	if (sep_1 && sep_2 && sep_3)
		return nullptr;

	auto pattern = !sep_1
		? constants::separators::SEPARATOR_1
		: !sep_2
		? constants::separators::SEPARATOR_2
		: constants::separators::SEPARATOR_3;
	base::utils::tracker_parsing::trim_by_pattern(pattern, input, track);
	return track;
}

auto base::utils::is_number(std::string & str_num)->bool
{
	return !str_num.empty()
		&& str_num.find_first_not_of(constants::INTEGER_STR_VALUES) == std::string::npos;
}

auto base::index::display_create_track_menu(
	playlist * & playlist, std::string & input)->void
{
	while (true) {
		std::cout << std::endl << "Enter a track or 'Q' to quit: " << std::flush;
		std::getline(std::cin, input);

		if (input == "q" || input == "Q")
			break;

		if (input.length() < constants::MIN_INPUT_LENGHT)
			std::cout << "Please enter a track with more than five characters."
			<< std::endl << std::flush;
		else {
			auto track = base::utils::tracker_parsing::make_tracker(input);
			if (track == nullptr)
				std::cout << "Invalid input!" << std::endl << std::flush;
			else {
				std::cout << std::endl
					<< constants::labels::TITLE_LABEL << track->title << std::endl
					<< constants::labels::ARTIST << track->artist << std::endl
					<< std::endl << std::flush;

				playlist->add_track(track);
			}
		}

		std::system(constants::terminal::PAUSE);
		std::system(constants::terminal::CLS);
	}
}

auto playlist_tracker::base::index::display_track_menu(
	int & index, std::string & input)->void
{
	while (true) {
		auto playlist = base::PLAYLISTS->operator[](index);
		std::cout << std::endl << "Playlist '" << playlist->get_name() << "' "
			<< "Menu:" << std::endl << std::endl
			<< "- Press [" << constants::options::ADD_TRACK
			<< "] to add track(s) to playlist." << std::endl << std::endl
			<< "- Press [" << constants::options::DELETE_PLAYLIST
			<< "] to delete this playlist." << std::endl << std::endl
			<< "- Press [" << constants::options::EXIT
			<< "] to exit to main menu." << std::endl << std::endl
			<< std::flush;

		if (input == constants::options::EXIT)
			break;
		else if (input == constants::options::DELETE_PLAYLIST) {
			base::PLAYLISTS->erase(base::PLAYLISTS->begin() + index);
			std::cout << std::endl << "Playlist successfully removed."
				<< std::endl << std::flush;
		}
		else if (input == constants::options::ADD_TRACK)
			base::index::display_create_track_menu(playlist, input);
		else
			std::cout << std::endl << "Unknown option, try again..."
			<< std::endl << std::endl;

		std::system(constants::terminal::PAUSE);
		std::system(constants::terminal::CLS);
	}
}

auto base::index::display_create_playlist_menu(void)->void
{
	std::string&& name = "";
	std::cout << std::endl << "Please enter a name for your new playlist: "
		<< std::flush;
	std::getline(std::cin, name);

	auto playlist = new base::playlist(name);
	base::PLAYLISTS->push_back(playlist);

	std::cout << std::endl << "Playlist '" << name << "' successfully created!"
		<< std::endl << std::endl << std::flush;
}

auto base::index::display_playlist_menu(std::string & input)->bool
{
	// todo:
	//	- properly format tracks per playlist
	//	- figure out what's causing weird console output symbols.
	std::cout << std::endl << "Select Playlist #" << std::endl
		<< std::endl << std::flush;
	for (auto i = 0; i < base::PLAYLISTS->size(); i++) {
		auto playlist = base::PLAYLISTS->operator[](i);
		std::cout << (i + 1) << constants::separators::SEPARATOR_2
			<< playlist->get_name() << std::endl
			<< playlist->display_tracks()
			<< std::flush;
	}

	std::cout << std::endl << "Your choice: " << std::flush;
	std::getline(std::cin, input);

	if (input == constants::options::EXIT
		|| input == constants::options::CREATE_PLAYLIST)
		return true;

	if (!base::utils::is_number(input))
		return true;

	auto op = std::stoi(input);
	if (--op < 0 || op >= base::PLAYLISTS->size()) {
		std::cout << std::endl << "Playlist number not found."
			<< std::endl << std::flush;
		return false;
	}

	auto playlist = base::PLAYLISTS->operator[](op);
	base::index::display_create_track_menu(playlist, input);
	return true;
}

auto base::index::display_main_menu(void)->void
{
	if (base::PLAYLISTS == nullptr)
		base::PLAYLISTS = new std::vector<base::playlist *>();

	std::string op;
	while (true) {
		if (base::PLAYLISTS->size() == 0) {
			std::cout << "Main Menu" << std::endl
				<< std::endl << "There is no playlist yet."
				<< std::endl << std::flush;

			base::index::display_create_playlist_menu();
		}
		else {
			std::cout << "Main Menu" << std::endl
				<< std::endl
				<< "- Press [" << constants::options::CREATE_PLAYLIST
				<< "] to create a new playlist." << std::endl
				<< "- Press [" << constants::options::EXIT
				<< "] to exit program." << std::endl << std::endl
				<< std::flush;

			if (base::index::display_playlist_menu(op)) {
				if (op == constants::options::EXIT)
					break;
				else if (op == constants::options::CREATE_PLAYLIST)
					base::index::display_create_playlist_menu();
				else
					std::cout << std::endl << "Unknown option, try again..."
					<< std::endl << std::endl;
			}
		}

		std::system(constants::terminal::PAUSE);
		std::system(constants::terminal::CLS);
	}
	std::cout << std::endl << "Farewell!" << std::endl;
}

base::playlist::playlist(std::string name)
{
	this->name = name;
}

base::playlist::~playlist(void)
{
	delete &this->tracks;
}

auto base::playlist::get_name(void)->std::string
{
	return this->name;
}

auto base::playlist::add_track(track * & track) -> void
{
	this->tracks.push_back(*track);
	std::cout << std::endl << "Track successfully added!" << std::endl << std::flush;
}

auto base::playlist::remove_track(int index) -> void
{
	if (index < this->tracks.size()) {
		this->tracks.erase(this->tracks.begin() + index);
		std::cout << std::endl << "Track successfully removed." << std::endl
			<< std::flush;
	}
	else
		std::cout << std::endl << "Track not removed!" << std::endl << std::flush;
}

auto base::playlist::display_tracks(void)->const char *
{
	if (this->tracks.size() == 0)
		return "";

	std::string output;
	for (auto i = 0; i < this->tracks.size(); i++) {
		auto track = &this->tracks[i];
		output += "  ";
		output += constants::separators::SEPARATOR_2;
		output += constants::labels::TITLE_LABEL;
		output += track->title;
		output += "\n  ";
		output += constants::labels::ARTIST;
		output += track->artist;
		output += "\n";
	}
	return output.c_str();
}
