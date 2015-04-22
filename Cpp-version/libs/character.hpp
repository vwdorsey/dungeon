#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "dice.hpp"
#include "char_template.hpp"

class Character {
	public:
		Character();
		Character(Char_template* mon);
		~Character();
		void kill_character();
		int is_alive();
		std::string Name; //Name of the character
		char Sprite; //Character Sprite
		int Color; //Color the character should be displayed as
		std::vector<std::string> Description; //Must be no longer than 77 chars in width;
		uint16_t Attribs; //Attributes that the character has
		int Speed; // Dice values for Speed
		int HP; // Dice values for HP
		Dice* Damage; // Dice values for Damage/Attack
};

#endif