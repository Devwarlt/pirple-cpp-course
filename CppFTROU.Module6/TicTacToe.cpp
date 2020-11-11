#include <iostream>
#include <string>

#include <stdlib.h>

const char * CLS = "CLS", *TOP = "top row", *MIDDLE = "middle", *BOTTOM = "bottom row",
*DIAGONAL = "diagonal", *LEFT = "left column", *RIGHT = "right column";
const char PLAYER_X = 'X', PLAYER_O = 'O', BOARD_DIV = '|', BOARD_LINE = '-', BOARD_INTERSECTION = '+';
const char INPUT_PLACEHOLDERS[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const int MAX_ATTEMPTS = 9, BOARD_WIDTH = 3;

typedef struct {
	unsigned int x;
	unsigned int y;
} board_pos;

board_pos * get_board_pos_by_input(int & index) {
	auto * pos = new board_pos();
	pos->x = index % BOARD_WIDTH;
	pos->y = (index - pos->x) / BOARD_WIDTH;
	return pos;
}

void relative_board_cell(std::string & output, char & placeholder, const bool & left_corner, const bool & right_corner) {
	if (left_corner) output += "  ";
	if (!left_corner && !right_corner) output += BOARD_DIV;

	output += " ";

	if (placeholder == PLAYER_X || placeholder == PLAYER_O) output += placeholder;
	else output += std::to_string((int)placeholder);

	output += " ";

	if (right_corner) output += "\n";
	if (!left_corner && !right_corner) output += BOARD_DIV;
}

void board_row_separator(std::string & output) {
	output += "  ", output.append(3, BOARD_LINE), output += BOARD_INTERSECTION, output.append(3, BOARD_LINE),
		output += BOARD_INTERSECTION, output.append(3, BOARD_LINE), output += "\n";
}

void relative_board_fmt(std::string & output, char(&placeholders)[3], const bool & is_mid_row) {
	// Board formatting pattern:
	//	1 | 2 | 3
	// ---+---+---
	//	4 | 5 | 6
	// ---+---+---
	//	7 | 8 | 9

	if (is_mid_row) board_row_separator(output);

	relative_board_cell(output, placeholders[0], true, false);
	relative_board_cell(output, placeholders[1], false, false);
	relative_board_cell(output, placeholders[2], false, true);

	if (is_mid_row) board_row_separator(output);
}

void board_init_placeholders(char(&board_inputs)[3][3]) {
	for (auto row = 0; row < 3; row++)
		for (auto col = 0; col < 3; col++)
			board_inputs[row][col] = 1 + col + row * 3;
}

void board_draw(std::string & output, char(&board_inputs)[3][3]) {
	for (auto row = 0; row < 3; row++)
		relative_board_fmt(output, board_inputs[row], row == 1);
}

bool board_check_horizontal(char(&board_inputs)[3][3], const int & row, const char & player) {
	return board_inputs[row][0] == player && board_inputs[row][1] == player && board_inputs[row][2] == player;
}

bool board_check_vertical(char(&board_inputs)[3][3], const int & col, const char & player) {
	return board_inputs[0][col] == player && board_inputs[1][col] == player && board_inputs[2][col] == player;
}

bool board_check_diagonal(char(&board_inputs)[3][3], const char & player) {
	return (board_inputs[0][0] == player && board_inputs[1][1] == player && board_inputs[2][2] == player)
		|| (board_inputs[0][2] == player && board_inputs[1][1] == player && board_inputs[2][0] == player);
}

void board_check_player(char(&board_inputs)[3][3], char & winner, const char * & condition, const char & player, std::string & condition_fmt) {
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

void board_checks(char(&board_inputs)[3][3], char & winner, const char * & condition, std::string & condition_fmt) {
	board_check_player(board_inputs, winner, condition, PLAYER_X, condition_fmt);
	if (winner != PLAYER_X) board_check_player(board_inputs, winner, condition, PLAYER_O, condition_fmt);
}

int main(void)
{
	auto last_player = PLAYER_O, current_player = PLAYER_X, winner = ' ';
	auto attempts = 0, op = -1, index = 0;
	auto is_occupied = false;
	char board_inputs[3][3] = {};
	const char * condition;
	std::string output, condition_fmt;

	board_init_placeholders(board_inputs);

	condition_fmt.clear();

	while (true) {
		output.clear();
		output += "Current board state:\n";

		if (op != 0 && op != -1) {
			index = op - 1;
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

		board_draw(output, board_inputs);

		if (op == 0) output += "\nNot a valid choice. Try again.\n";
		if (is_occupied) {
			is_occupied = false;
			output += "\nThat square is not available. Try again.\n";
		}

		board_checks(board_inputs, winner, condition, condition_fmt);

		if (winner != ' ' || attempts == MAX_ATTEMPTS) break;

		output += "\nPlayer ", output += current_player, output += ", enter a number between 1 and 9: ";
		std::cout << output << std::flush;
		std::cin >> op;
		std::system(CLS);

		if (op < 1 || op > 9) op = 0;
	}

	if (winner != ' ') output += "\nPlayer ", output += winner, output += " wins on the ", output += condition, output += "!";
	else output += "\nDraw. Nobody wins.";

	std::cout << output << std::endl << std::endl;
	return EXIT_SUCCESS;
}
