#ifndef OBJ_TEMPLATE_HPP
#define OBJ_TEMPLATE_HPP

#include <string>
#include <vector>
#include <cstdint>
#include "dice.hpp"

class Obj_template{
	public:
		Obj_template();
		~Obj_template();
		void printout();
		short do_sanity_check();

		std::string Name; 						//Name of the object
		std::vector<std::string> Description; 	//Must be no longer than 77 chars in width;
		uint32_t Type; 							//Object Type. Populated using a bitfield.
		short Color; 						    //Color the Object should be displayed as
		Dice* Hit; 								// Dice values for Hit Bonus
		Dice* Damage; 							// Dice values for Damage/Attack Bonus
		Dice* Dodge; 							// Dice values for Dodge/Evasion Bonus
		Dice* Defense; 							// Dice values for Defense/Block Bonus given to Character
		Dice* Weight; 							// Dice values for Weight of object.
		Dice* Speed; 							// Dice values for Speed Bonus object gives to character
		Dice* SpecAttr; 						// Dice values for A special attribute value for each object.
		Dice* Value; 	     					// Dice values for Value of object in game in some currency.
};

#endif