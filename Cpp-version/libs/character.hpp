#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "dice.hpp"
#include "char_template.hpp"
#include "point.hpp"
#include "object.hpp"

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
		int Speed; // Base Speed Value
		int HP; // Base HP Value
		Dice* Damage; // Dice values for Damage/Attack
		int pos[2];
		int priority;
		int alive;
};

class PC: public Character {
	public:
		PC() : Character()
			{ }
		std::vector<Object*> backpack; //Must be soft-limited to 10
		struct equipment{
			Object* weapon;
			Object* offhand;
			Object* ranged;
			Object* armor;
			Object* helmet;
			Object* cloak;
			Object* gloves;
			Object* boots;
			Object* amulet;
			Object* light;
			Object* ring1;
			Object* ring2;
		};
		equipment equips;
		int cur_speed;
		void init_backpack();
};

class Monster: public Character {
	public:
		Monster(Char_template* mon) : Character(mon)
			{ attribs = mon -> Attribs; }

		uint16_t attribs; //Attributes that the monster has
		uint8_t last_pc_pos[2]; //y,x format
		point* path_to_player;
};

#endif
