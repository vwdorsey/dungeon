#include "dice.hpp"
#include <sstream>

Dice::Dice(){}

Dice::Dice(int b, int n, int s){
	base = b;
	num_dice = n;
	sides = s;
}

Dice::Dice(Dice* original){
	base = original->base;
	num_dice = original->num_dice;
	sides = original->sides;
}

Dice::Dice(std::string in_string, int init_offset){
	std::string base_s = in_string.substr(init_offset, in_string.find_first_of('+')-3);
	std::string num_s = in_string.substr(in_string.find("+")+1, in_string.find("d")- in_string.find("+")-1);
	std::string sides_s = in_string.substr(in_string.find("d")+1);
	
	base = atoi(base_s.c_str());
	num_dice = atoi(num_s.c_str());
	sides = atoi(sides_s.c_str());
}

Dice::~Dice(){}

int Dice::roll(){
	int total = base;
	if(num_dice != 0 && sides != 0){
		for(int i = 0; i < num_dice; i++){
			total += (rand()%sides);
		}
	}
	return total;
}

std::string Dice::report_data(){
	std::stringstream in;
	in << base << "+" << num_dice << "d" << sides;
	return in.str();
}
