#include <iostream>
#include <string>

#include <stdlib.h>

const char * CLS = "CLS",
*TOP = "top row",
*MIDDLE = "middle",
*BOTTOM = "bottom row",
*DIAGONAL = "diagonal",
*LEFT = "left column",
*RIGHT = "right column";

const char PLAYER_X = 'X',
PLAYER_O = 'O',
BOARD_DIV = '|',
BOARD_LINE = '-',
BOARD_INTERSECTION = '+';

const char INPUT_PLACEHOLDERS[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

const int MAX_ATTEMPTS = 9,
BOARD_WIDTH = 3;

typedef struct { unsigned int x, y; } board_pos;

board_pos * get_board_pos_by_input(int & index) {
	auto * pos = new board_pos();
	pos->x = index % BOARD_WIDTH;
	pos->y = (index - pos->x) / BOARD_WIDTH;
	return pos;
}

void relative_board_cell(
	std::string & output, char & placeholder,
	const bool & left_corner, const bool & right_corner
) {
	if (left_corner)
		output += "  ";

	if (!left_corner && !right_corner)
		output += BOARD_DIV;

	output += " ";

	if (placeholder == PLAYER_X || placeholder == PLAYER_O)
		output += placeholder;
	else
		output += std::to_string((int)placeholder);

	output += " ";

	if (right_corner)
		output += "\n";

	if (!left_corner && !right_corner)
		output += BOARD_DIV;
}

void board_row_separator(std::string & output) {
	output += "  ";
	output.append(3, BOARD_LINE);
	output += BOARD_INTERSECTION;
	output.append(3, BOARD_LINE);
	output += BOARD_INTERSECTION;
	output.append(3, BOARD_LINE);
	output += "\n";
}

bool board_check_horizontal(
	char(&board_inputs)[BOARD_WIDTH][BOARD_WIDTH],
	const int & row, const char & player
) {
	return board_inputs[row][0] == player
		&& board_inputs[row][1] == player
		&& board_inputs[row][2] == player;
}

bool board_check_vertical(
	char(&board_inputs)[BOARD_WIDTH][BOARD_WIDTH],
	const int & col, const char & player
) {
	return board_inputs[0][col] == player
		&& board_inputs[1][col] == player
		&& board_inputs[2][col] == player;
}

bool board_check_diagonal(
	char(&board_inputs)[BOARD_WIDTH][BOARD_WIDTH],
	const char & player
) {
	return (board_inputs[0][0] == player
		&& board_inputs[1][1] == player
		&& board_inputs[2][2] == player)
		|| (board_inputs[0][2] == player
			&& board_inputs[1][1] == player
			&& board_inputs[2][0] == player);
}

void board_check_player(
	char(&board_inputs)[BOARD_WIDTH][BOARD_WIDTH],
	char & winner, const char * & condition,
	const char & player, std::string & condition_fmt
) {
	if (board_check_horizontal(board_inputs, 0, player)) {
		condition = TOP;
		winner = player;
		return;
	}

	if (board_check_horizontal(board_inputs, 1, player)) {
		condition_fmt += MIDDLE;
		condition_fmt += " row";
		condition = condition_fmt.c_str();
		winner = player;
		return;
	}

	if (board_check_horizontal(board_inputs, 2, player)) {
		condition = BOTTOM;
		winner = player;
		return;
	}

	if (board_check_vertical(board_inputs, 0, player)) {
		condition = LEFT;
		winner = player;
		return;
	}

	if (board_check_vertical(board_inputs, 1, player)) {
		condition_fmt += MIDDLE;
		condition_fmt += " column";
		condition = condition_fmt.c_str();
		winner = player;
		return;
	}

	if (board_check_vertical(board_inputs, 2, player)) {
		condition = RIGHT;
		winner = player;
		return;
	}

	if (board_check_diagonal(board_inputs, player)) {
		condition = DIAGONAL;
		winner = player;
		return;
	}
}

void get_player_choice(
	int & choice, int & index, char(&board_inputs)[BOARD_WIDTH][BOARD_WIDTH],
	bool & is_occupied, char & current_player, char & last_player, int & attempts
) {
	if (choice != 0 && choice != -1) {
		index = choice - 1;

		auto * pos = get_board_pos_by_input(index);
		auto * cell = &board_inputs[pos->y][pos->x];

		is_occupied = *cell == PLAYER_X || *cell == PLAYER_O;
		if (!is_occupied) {
			*cell = current_player;
			last_player = current_player;
			current_player = current_player == PLAYER_X ? PLAYER_O : PLAYER_X;
			attempts++;
		}
	}
}

bool check_for_end_game(int & attempts, char & winner) {
	return winner != ' ' || attempts == MAX_ATTEMPTS;
}

void display_board(void) {
	auto last_player = PLAYER_O,
		current_player = PLAYER_X,
		winner = ' ';

	auto attempts = 0,
		choice = -1,
		index = 0;

	auto is_occupied = false, is_game_over = false;
	char board_inputs[BOARD_WIDTH][BOARD_WIDTH] = {};
	const char * condition;
	std::string output, condition_fmt;

	for (auto row = 0; row < BOARD_WIDTH; row++)
		for (auto col = 0; col < BOARD_WIDTH; col++)
			board_inputs[row][col] = 1 + col + row * BOARD_WIDTH;

	condition_fmt.clear();

	while (true) {
		output.clear();
		output += "Current board state:\n";

		get_player_choice(
			choice, index, board_inputs, is_occupied,
			current_player, last_player, attempts
		);

		for (index = 0; index < BOARD_WIDTH; index++)
		{
			// Board formatting pattern:
			//	1 | 2 | 3
			// ---+---+---
			//	4 | 5 | 6
			// ---+---+---
			//	7 | 8 | 9

			auto is_mid_row = index == 1;
			if (is_mid_row)
				board_row_separator(output);

			relative_board_cell(output, board_inputs[index][0], true, false);
			relative_board_cell(output, board_inputs[index][1], false, false);
			relative_board_cell(output, board_inputs[index][2], false, true);

			if (is_mid_row)
				board_row_separator(output);
		}

		if (choice == 0)
			output += "\nNot a valid choice. Try again.\n";

		if (is_occupied) {
			output += "\nThat square is not available. Try again.\n";
			is_occupied = false;
		}

		board_check_player(board_inputs, winner, condition, PLAYER_X, condition_fmt);

		if (winner != PLAYER_X)
			board_check_player(board_inputs, winner, condition, PLAYER_O, condition_fmt);

		if (check_for_end_game(attempts, winner))
			break;

		output += "\nPlayer ";
		output += current_player;
		output += ", enter a number between 1 and 9: ";
		std::cout << output << std::flush;
		std::cin >> choice;
		std::system(CLS);

		if (choice < 1 || choice > 9)
			choice = 0;
	}

	if (winner != ' ') {
		output += "\nPlayer ";
		output += winner;
		output += " wins on the ";
		output += condition;
		output += "!";
	}
	else
		output += "\nDraw. Nobody wins.";

	std::cout << output << std::endl << std::endl;
}

int main(void)
{
	/*
		[Module 8] - Application Structure:
			This is a refactored version of TicTacToe.cpp from module 6.

			Contains code organisation, virtualization and more changes
			for ease logic and code concept understanding.
	*/
	display_board();

	return EXIT_SUCCESS;
}
