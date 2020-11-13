#include <iostream>
#include <string>

/* TERMINAL OPS */
const char * CLS = "CLS";
const char * PAUSE = "PAUSE";

/* SEPARATORS */
const char * SEPARATOR_1 = ": "; // title + artist -> artist + title
const char * SEPARATOR_2 = " - "; // title + artist -> title + artist
const char * SEPARATOR_3 = " by "; // title + artist -> artist + title

/* LABELS */
const char * TITLE_LABEL = "Title: ";
const char * ARTIST = "Artist: ";

const int MIN_INPUT_LENGHT = 5;

typedef struct {
	std::string title;
	std::string artist;
} playlist_info;

typedef struct {
	std::size_t from;
	std::size_t to;
} input_args_info;

void trim_by_pattern(const char * pattern, std::string & input, playlist_info * & info) {
	std::size_t pos = input.find(pattern);
	input_args_info * a = new input_args_info();
	input_args_info * b = new input_args_info();
	a->from = 0;
	a->to = pos;
	b->from = pos + std::strlen(pattern);
	b->to = input.length();
	info->title = pattern == SEPARATOR_1
		? input.substr(b->from, b->to)
		: input.substr(a->from, a->to);
	info->artist = pattern == SEPARATOR_1
		? input.substr(a->from, a->to)
		: input.substr(b->from, b->to);
}

playlist_info * get_playlist_info(std::string & input) {
	playlist_info * info = new playlist_info();
	bool sep_1 = input.find(SEPARATOR_1) == std::string::npos;
	bool sep_2 = input.find(SEPARATOR_2) == std::string::npos;
	bool sep_3 = input.find(SEPARATOR_3) == std::string::npos;
	if (sep_1 && sep_2 && sep_3)
		return NULL;

	const char * pattern = !sep_1
		? SEPARATOR_1
		: !sep_2
		? SEPARATOR_2
		: SEPARATOR_3;

	trim_by_pattern(pattern, input, info);
	return info;
}

int main(void)
{
	std::string full_name;
	while (true) {
		std::cout << "Enter a track or 'Q' to quit: " << std::flush;
		getline(std::cin, full_name);

		if (full_name == "Q" || full_name == "q") {
			std::system(CLS);
			break;
		}

		if (full_name.length() < MIN_INPUT_LENGHT) {
			std::cout << "Please enter a track with more than five characters." << std::endl << std::flush;
			std::system(PAUSE);
			std::system(CLS);
			continue;
		}

		playlist_info * info = get_playlist_info(full_name);
		if (info == NULL)
			std::cout << "Invalid input!" << std::endl << std::flush;
		else
			std::cout << std::endl
			<< TITLE_LABEL << info->title << std::endl
			<< ARTIST << info->artist << std::endl
			<< std::endl << std::flush;

		std::system(PAUSE);
		std::system(CLS);
	}

	std::cout << "Terminated." << std::endl << std::endl;

	return EXIT_SUCCESS;
}
