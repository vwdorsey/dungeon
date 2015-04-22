#ifndef CHAR_TEMPLATE_HPP
#define CHAR_TEMPLATE_HPP

#include <string>
#include <vector>
#include <cstdint>
#include "dice.hpp"

class Char_template{
	public:
		Char_template();
		~Char_template();
		void printout();
		short do_sanity_check();

		std::string Name; //Name of the monster
		char Sprite; //Monster Sprite
		short Color; //Color the monster should be displayed as
		std::vector<std::string> Description; //Must be no longer than 77 chars in width;
		uint16_t Attribs; //Attributes that the monster has
		Dice* Speed; // Dice values for Speed
		Dice* HP; // Dice values for HP
		Dice* Damage; // Dice values for Damage/Attack
};

#endif