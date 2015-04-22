#ifndef DICE_HPP
#define DICE_HPP

#include <string>

class Dice{
	public:
		Dice();
		Dice(int b, int n, int s);
		Dice(std::string in_string, int init_offset);
		~Dice();
		int roll();
		std::string report_data();
	private:
		int base; //Base Value
		int num_dice; //Number of Dice used
		int sides; //How many sides each die has.
};

#endif