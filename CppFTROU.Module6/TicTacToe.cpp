#include <iostream>
#include <string>
#include <stdlib.h>

const char * CLS = "CLS";
const char PLAYER_X = 'X', PLAYER_O = 'O';
const char BOARD_DIV = '|', BOARD_LINE = '-', BOARD_INTERSECTION = '+';
const char MAX_ATTEMPTS = 9;
const char BOARD_WIDTH = 3;
const char INPUT_PLACEHOLDERS[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

typedef struct {
	char x;
	char y;
} board_pos;

board_pos * get_board_pos_by_input(char & index) {
	auto * pos = new board_pos();
	pos->x = index % BOARD_WIDTH;
	pos->y = (index - pos->x) / BOARD_WIDTH;
	return pos;
}

void relative_board_cell(std::string & output, char & placeholder, const bool & left_corner, const bool & right_corner) {
	if (left_corner) output.append("  ");
	if (!left_corner && !right_corner) output.append(1, BOARD_DIV);

	output.append(" ");

	if (placeholder == PLAYER_X || placeholder == PLAYER_O) output.append(1, placeholder);
	else output.append(std::to_string((int)placeholder));

	output.append(" ");

	if (right_corner) output.append("\n");
	if (!left_corner && !right_corner) output.append(1, BOARD_DIV);
}

void board_row_separator(std::string & output) {
	output.append("  ");
	output.append(3, BOARD_LINE);
	output.append(1, BOARD_INTERSECTION);
	output.append(3, BOARD_LINE);
	output.append(1, BOARD_INTERSECTION);
	output.append(3, BOARD_LINE);
	output.append("\n");
}

void top_btm_board_fmt(std::string & output, char(&placeholders)[3]) {
	// Top & bottom board formatting pattern:
	//	0 | 1 | 2
	//	   ...
	//	6 | 7 | 8
	relative_board_cell(output, placeholders[0], true, false);
	relative_board_cell(output, placeholders[1], false, false);
	relative_board_cell(output, placeholders[2], false, true);
}

void mid_board_fmt(std::string & output, char(&placeholders)[3]) {
	// Middle board formatting pattern:
	//	   ...
	// ---+---+---
	//	3 | 4 | 5
	// ---+---+---
	//	   ...
	board_row_separator(output);
	relative_board_cell(output, placeholders[0], true, false);
	relative_board_cell(output, placeholders[1], false, false);
	relative_board_cell(output, placeholders[2], false, true);
	board_row_separator(output);
}

void board_draw(std::string & output, char(&board_inputs)[3][3], char(&top_inputs)[3], char(&mid_inputs)[3], char(&btm_inputs)[3]) {
	for (auto row = 0; row < 3; row++)
		for (auto col = 0; col < 3; col++) {
			auto board_input = board_inputs[row][col];
			if (board_input != PLAYER_X && board_input != PLAYER_O) board_input = INPUT_PLACEHOLDERS[col + row * 3];
			if (row == 0) top_inputs[col] = board_input;
			else if (row == 1) mid_inputs[col] = board_input;
			else btm_inputs[col] = board_input;
		}

	top_btm_board_fmt(output, top_inputs);
	mid_board_fmt(output, mid_inputs);
	top_btm_board_fmt(output, btm_inputs);
}

int main(void)
{
	auto last_player = PLAYER_X, current_player = PLAYER_O;
	auto attempts = 0;
	char board_inputs[3][3] = {};
	char top_inputs[3] = {}, mid_inputs[3] = {}, btm_inputs[3] = {};
	char op = NULL;
	std::string output;

	while (attempts != (int)MAX_ATTEMPTS) {
		/*if (op != NULL && ((int)op < 1 && (int)op > 9)) {
			continue;
		}*/

		if (attempts == 0 || op != NULL) {
			attempts++;

			for (auto j = 0; j < 3; j++) {
				top_inputs[j] = 0;
				mid_inputs[j] = 0;
				btm_inputs[j] = 0;
			}

			output.clear();
			output.append("Current board state:\n");

			board_draw(output, board_inputs, top_inputs, mid_inputs, btm_inputs);

			output.append("Player ");
			output.append(1, last_player);
			output.append(", enter a number between 1 and 9: ");
		}

		if (op == NULL)
			output.append("");

		std::cout << output.c_str() << std::endl;
		std::cin >> op;
	}

	return EXIT_SUCCESS;
}
