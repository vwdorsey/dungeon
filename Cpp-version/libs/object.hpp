#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "dice.hpp"
#include <vector>
#include <string>
#include "obj_template.hpp"
#include "values.hpp"

class Object{
	public:
		Object(Obj_template* obj);
		~Object();
		char determine_sprite();
		std::string print_obj();
		
		std::string Name; 						//Name of the object
		std::vector<std::string> Description; 	//Must be no longer than 77 chars in width;
		uint32_t Type; 							//Object Type. Populated using a bitfield.
		char Sprite;							//Sprite used for drawing
		short Color; 						//Color the Object should be displayed as
		Dice* Damage; 							// Dice values for Damage/Attack Bonus
		int Hit; 								// Dice values for Hit Bonus
		int Dodge; 								// Dice values for Dodge/Evasion Bonus
		int Defense; 							// Dice values for Defense/Block Bonus given to Character
		int Weight; 							//Dice values for Weight of object.
		int Speed; 								//Dice values for Speed Bonus object gives to character
		int SpecAttr; 							//Dice values for A special attribute value for each object.
		int Value; 	     						//Dice values for Value of object in game in some currency.
		int pos[2];
};

#endif