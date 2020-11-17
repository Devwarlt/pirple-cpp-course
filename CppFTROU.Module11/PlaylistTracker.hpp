#ifndef PLAYLIST_TRACKER_HPP_
#define PLAYLIST_TRACKER_HPP_
#include <string>
#include <vector>

namespace playlist_tracker {
	namespace constants {
		namespace terminal {
			static auto const CLS = "CLS";
			static auto const PAUSE = "PAUSE";
		}

		namespace options {
			auto const CREATE_PLAYLIST = "c";
			auto const DELETE_PLAYLIST = "d";
			auto const ADD_TRACK = "a";
			auto const EXIT = "x";
		}

		namespace separators {
			static auto const SEPARATOR_1 = ": "; // title + artist -> artist + title
			static auto const SEPARATOR_2 = " - "; // title + artist -> title + artist
			static auto const SEPARATOR_3 = " by "; // title + artist -> artist + title
		}

		namespace labels {
			static auto const TITLE_LABEL = "Title: ";
			static auto const ARTIST = "Artist: ";
		}

		static auto const FILE_EXTENSION = ".playlist";
		static auto const INTEGER_STR_VALUES = "0123456789";
		static auto const MIN_INPUT_LENGHT = 5;
	}

	namespace base {
		typedef struct {
			std::string title;
			std::string artist;
		} track;

		class playlist {
		public:
			playlist(std::string name);
			virtual ~playlist(void);
			auto get_name(void)->std::string;
			auto add_track(track * & track, const bool silent)->void;
			auto remove_track(int index)->void;
			auto display_tracks(void)->std::string;
			auto get_tracks(void)->std::vector<track>;
		private:
			std::string name;
			std::vector<track> tracks;
		};

		static std::vector<playlist *> * PLAYLISTS;

		namespace index {
			auto display_main_menu(void)->void;
			auto display_playlist_menu(std::string & input)->bool;
			auto display_create_playlist_menu(void)->void;
			auto display_track_menu(int & index)->void;
			auto display_create_track_menu(playlist * & playlist)->void;
		}

		namespace utils {
			typedef struct {
				std::size_t from;
				std::size_t to;
			} input_args_info;

			class tracker_parsing {
			public:
				static auto make_tracker(std::string & input)->track *;
			private:
				static auto trim_by_pattern(
					const char * & pattern, std::string & input,
					track * & track)->void;
			};

			namespace io {
				auto read_contents()->void;
				auto write_contents()->void;
			}

			auto is_number(std::string & str_num)->bool;
		}
	}
}
#endif
