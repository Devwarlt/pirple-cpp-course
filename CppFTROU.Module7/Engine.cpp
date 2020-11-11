#include <iostream>
#include <string>
#include <bitset>
#include <thread>
#include <chrono>

#include <stdlib.h>

const char * CLS = "CLS", *PAUSE = "PAUSE";
const auto BITSET_SIZE = 5, BIT_OFFSET = 2;
const auto BLANK_LABEL = ' ';
const auto D1 = "     1        2        3        4   \n";
const auto D2 = "    ___      ___      ___      ___  \n";
const auto D3 = "  x|   |x  x|   |x  x|   |x  x|   |x\n";
const auto D4 = "   |   |    |   |    |   |    |   | \n";
const auto D5 = "    ---      ---      ---      ---  \n";
const auto D6 = "     ?        ?        ?        ?   \n";
//               .....5..2.....5..2.....5..2.....5..2
//                    ^[5]     ^[14]    ^[23]    ^[32]

const auto CYLINDER_1 = 0b01111; // PEIC
const auto CYLINDER_2 = 0b10111; // CPEI
const auto CYLINDER_3 = 0b11011; // ICPE
const auto CYLINDER_4 = 0b11101; // EICP
const auto ENGINE_SPEED_MS = 50;
const auto MAX_ENGINE_CYCLES = 100;

void bitwise_right_rotation(std::bitset<BITSET_SIZE> & bitset, int & offset) {
	bitset = (bitset >> offset) | (bitset << (BITSET_SIZE - offset));
}

void reverse_array(char(&arr)[BITSET_SIZE], int from, int to) {
	while (from < to) std::swap(arr[from++], arr[to--]);
}

void array_right_rotation(char(&arr)[BITSET_SIZE], int & offset) {
	reverse_array(arr, 0, BITSET_SIZE - 1);
	reverse_array(arr, 0, offset - 1);
	reverse_array(arr, offset, BITSET_SIZE - 1);
}

float get_engine_frequency() {
	// prevent negative values for ENGINE_SPEED_MS
	return 1000.0F / (float)(ENGINE_SPEED_MS <= 0 ? 1 : ENGINE_SPEED_MS);
}

void draw_piston(int & position, const char & piston, std::string & d3, std::string & d4) {
	std::string piston_d3, piston_d4;
	if (piston == 'P') piston_d3 = "x|*T*|x", piston_d4 = " |   | ";
	else if (piston == 'E') piston_d3 = "x|   |o", piston_d4 = " | T | ";
	else if (piston == 'I') piston_d3 = "o| T |x", piston_d4 = " |   | ";
	else piston_d3 = "x|   |x", piston_d4 = " | T | ";
	piston_d3 += " ", piston_d4 += " ";
	d3 += piston_d3, d4 += piston_d4;
}

void draw_valves(std::string & output, std::bitset<BITSET_SIZE> & valves) {
	auto piston_p = 0, piston_e = 0, piston_i = 0, piston_c = 0;
	auto cylinder = valves.to_ulong();
	if (cylinder == CYLINDER_1) piston_p = 1, piston_e = 2, piston_i = 3, piston_c = 4;
	else if (cylinder == CYLINDER_2) piston_p = 2, piston_e = 3, piston_i = 4, piston_c = 1;
	else if (cylinder == CYLINDER_3) piston_p = 3, piston_e = 4, piston_i = 1, piston_c = 2;
	else if (cylinder == CYLINDER_4) piston_p = 4, piston_e = 1, piston_i = 2, piston_c = 3;
	else {
		output += D3, output += D4;
		return;
	}

	std::string d3 = " ", d4 = " ";
	for (auto i = 1; i <= 4; i++) {
		d3 += " ", d4 += " ";
		if (i == piston_p) draw_piston(piston_p, 'P', d3, d4);
		if (i == piston_e) draw_piston(piston_e, 'E', d3, d4);
		if (i == piston_i) draw_piston(piston_i, 'I', d3, d4);
		if (i == piston_c) draw_piston(piston_c, 'C', d3, d4);
	}

	d3 += "\n", d4 += "\n", output += d3, output += d4;
}

void draw_stages(std::string & output, char(&stages)[BITSET_SIZE]) {
	std::string d6 = D6;
	auto next_d6_str_index = 5;
	for (auto i = 0; i < BITSET_SIZE; i++) {
		auto * stage = &stages[i];
		if (*stage == BLANK_LABEL) continue;
		d6[next_d6_str_index] = *stage;
		next_d6_str_index += 9;
	}
	output += d6;
}

void engine_draw(std::string & output, std::bitset<BITSET_SIZE> & valves, char(&stages)[BITSET_SIZE]) {
	output += D1, output += D2, draw_valves(output, valves); // D3, D4
	output += D5, draw_stages(output, stages); // D6
}

int main(void)
{
	std::cout << "C++ For the Rest Of Us - Module 7: Binary and Bits (Engine.cpp)\n\n" << std::flush << std::endl;
	std::system(PAUSE);
	std::bitset<BITSET_SIZE> valves(0b01111);
	char stages[BITSET_SIZE] = { BLANK_LABEL, 'P', 'E', 'I', 'C' };
	std::string output;
	auto offset = 0, cycles = 0;
	auto frequency = get_engine_frequency();
	while (cycles != MAX_ENGINE_CYCLES)
		for (auto i = 0; i < BITSET_SIZE; i++) {
			output.clear(), output += "C++ For the Rest Of Us - Module 7: Binary and Bits (Engine.cpp)\n\n",
				output += "Cycles:", output += std::to_string(cycles + 1), output += "/",
				output += std::to_string(MAX_ENGINE_CYCLES),
				output += "\tFrequency: ", output += std::to_string(frequency),
				output += "Hz (", output += std::to_string(ENGINE_SPEED_MS), output += "ms)\n\n";
			offset = BIT_OFFSET + (i == 1 ? 2 : 0);
			engine_draw(output, valves, stages);
			bitwise_right_rotation(valves, offset);
			array_right_rotation(stages, offset);
			output += "\n";
			std::cout << output.c_str() << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(ENGINE_SPEED_MS));
			if (++cycles < MAX_ENGINE_CYCLES) std::system(CLS);
		}

	return EXIT_SUCCESS;
}
