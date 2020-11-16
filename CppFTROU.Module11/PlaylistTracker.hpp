#ifndef PLAYLIST_TRACKER_HPP_
#define PLAYLIST_TRACKER_HPP_
namespace playlist_tracker {
	namespace constants {
		namespace terminal {
			const char * CLS = "CLS";
			const char * PAUSE = "PAUSE";
		}

		namespace options {
			const char CREATE_PLAYLIST_OPTION = 'c';
			const char EXIT_OPTION = 'x';
		}
	}

	auto display_main_menu(void) -> void;
	auto display_create_playlist_menu(void) -> void;
}
#endif
