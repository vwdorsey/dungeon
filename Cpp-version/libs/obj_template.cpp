#include "obj_template.hpp"
#include <iostream>
#include "values.hpp"

Obj_template::Obj_template(){
	Name = "";
	Type = 0;
	Color = 0;
}

Obj_template::~Obj_template(){
	delete(Hit);
	delete(Damage);
	delete(Dodge);
	delete(Defense);
	delete(Weight);
	delete(Speed);
	delete(SpecAttr);
	delete(Value);
}

void Obj_template::printout(){
	std::cout << "NAME: " << Name << '\n';
	std::cout << "DESC: " << '\n';
	for(int k = 0; k < Description.size(); k++){
		std::cout << Description[k] << '\n';
	}
	std::cout << "TYPE: ";

	if(Type == WEAPON + IS_EQUIPMENT) std::cout << "WEAPON" << '\n';
	if(Type == OFFHAND + IS_EQUIPMENT) std::cout << "OFFHAND" << '\n';
	if(Type == WEAPON + OFFHAND + IS_EQUIPMENT) std::cout << "WEAPON OFFHAND" << '\n';
	if(Type == RANGED + IS_EQUIPMENT) std::cout << "RANGED" << '\n';
	if(Type == ARMOR + IS_EQUIPMENT) std::cout << "ARMOR" << '\n';
	if(Type == HELMET + IS_EQUIPMENT) std::cout << "HELMET" << '\n';
	if(Type == CLOAK + IS_EQUIPMENT) std::cout << "CLOAK" << '\n';
	if(Type == GLOVES + IS_EQUIPMENT) std::cout << "GLOVES" << '\n';
	if(Type == BOOTS + IS_EQUIPMENT) std::cout << "BOOTS" << '\n';
	if(Type == RING + IS_EQUIPMENT) std::cout << "RING" << '\n';
	if(Type == AMULET + IS_EQUIPMENT) std::cout << "AMULET" << '\n';
	if(Type == LIGHT + IS_EQUIPMENT) std::cout << "LIGHT" << '\n';
	if(Type == SCROLL) std::cout << "SCROLL" << '\n';
	if(Type == BOOK) std::cout << "BOOK" << '\n';
	if(Type == FLASK) std::cout << "FLASK" << '\n';
	if(Type == GOLD) std::cout << "GOLD" << '\n';
	if(Type == AMMUNITION) std::cout << "AMMUNITION" << '\n';
	if(Type == FOOD) std::cout << "FOOD" << '\n';
	if(Type == WAND) std::cout << "WAND" << '\n';
	if(Type == CONTAINER) std::cout << "CONTAINER" << '\n';

	std::cout << "COLOR: " << Color << '\n';
	std::cout << "HIT: " << Hit->report_data() << '\n';
	std::cout << "DAM: " << Damage->report_data() << '\n';
	std::cout << "DODGE: " << Dodge->report_data() << '\n';
	std::cout << "DEF: " << Defense->report_data() << '\n';
	std::cout << "WEIGHT: " << Weight->report_data() << '\n';
	std::cout << "SPEED: " << Speed->report_data() << '\n';
	std::cout << "ATTR: " << SpecAttr->report_data() << '\n';
	std::cout << "VAL: " << Value->report_data() << '\n';
	std::cout << '\n';
}

short Obj_template::do_sanity_check(){
	if(Name == "") return 0;
	if(Description.size() == 0) return 0;
	else if(Type == 0) return 0;
	else if(Color == 0) return 0;
	else if(Hit == NULL) return 0;
	else if(Damage == NULL) return 0;
	else if(Dodge == NULL) return 0;
	else if(Defense == NULL) return 0;
	else if(Weight == NULL) return 0;
	else if(Speed == NULL) return 0;
	else if(SpecAttr == NULL) return 0;
	else if(Value == NULL) return 0;
	else return 1;
}
