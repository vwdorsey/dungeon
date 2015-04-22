#include "char_template.hpp"
#include <iostream>
#include "values.hpp"

Char_template::Char_template(){
	Name = "";
	Sprite = 'U';
	Color = 0;
	Attribs = 0;
}

Char_template::~Char_template(){
	delete(Speed);
	delete(HP);
	delete(Damage);
}

void Char_template::printout(){
	std::cout << "Name: " << Name << '\n';
	std::cout << "Sprite: " << Sprite << '\n';
	std::cout << "Color: " << Color << '\n';
	std::cout << "Description: \n";
	for(int k = 0; k < Description.size(); k++){
		std::cout << Description[k] << '\n';
	}
	std::cout << "Attributes: ";
	uint16_t att = Attribs;
	if(att >= IS_CHARACTER) {
		std::cout << "CHARACTER ";
		att -= IS_CHARACTER;
	}
	if(att >= PASS){
		std::cout << "PASS ";
		att -= PASS;
	}
	if(att >= TUNNEL){
		std::cout << "TUNNEL ";
		att -= TUNNEL;  
	}
	if(att >= TELEPATHIC){
		std::cout << "TELE ";
		att -= TELEPATHIC;
	}
	if(att >= IS_SMART){
		std::cout << "SMART";
		att -= IS_SMART;  
	}
	std::cout << '\n';
	std::cout << "Dice Values:";
	std::cout << "Speed: " << Speed->report_data() << '\n';
	std::cout << "Damage: " << Damage->report_data() << '\n';
		std::cout << "HP: " << HP->report_data() << '\n';
		std::cout << '\n';
}

short Char_template::do_sanity_check(){
	if(Name == "") return 0;
	if(Sprite == 0) return 0;
	if(Description.size() == 0) return 0;
	else if(Color == 0) return 0;
	else if(HP == NULL) return 0;
	else if(Damage == NULL) return 0;
	else if(Speed == NULL) return 0;
	else return 1;
}