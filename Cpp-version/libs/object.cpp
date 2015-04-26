#include "object.hpp"
#include <sstream>
#include <iostream>

Object::Object(Obj_template* obj){
	Name = obj->Name;
	Description = obj->Description;
	Type = obj->Type;
	Sprite = determine_sprite();
	Color = obj->Color;
	Hit = obj->Hit->roll();
	Damage = new Dice(obj->Damage);
	Dodge = obj->Dodge->roll();
	Defense = obj->Defense->roll();
	Weight = obj->Weight->roll();
	Speed = obj->Speed->roll();
	SpecAttr = obj->SpecAttr->roll();
	Value = obj->Value->roll();
	pos[0] = 0;
	pos[1] = 0;
}

Object::~Object(){
	delete Damage;
}

char Object::determine_sprite(){
	if(Type == WEAPON) return SPT_WEAPON;
	else if(Type == OFFHAND) return SPT_OFFHAND;
	else if(Type == RANGED) return SPT_RANGED;
	else if(Type == ARMOR) return SPT_ARMOR;
	else if(Type == HELMET) return SPT_HELMET;
	else if(Type == CLOAK) return SPT_CLOAK;
	else if(Type == GLOVES) return SPT_GLOVES;
	else if(Type == BOOTS) return SPT_BOOTS;
	else if(Type == RING) return SPT_RING;
	else if(Type == AMULET) return SPT_AMULET;
	else if(Type == LIGHT) return SPT_LIGHT;
	else if(Type == SCROLL) return SPT_SCROLL;
	else if(Type == BOOK) return SPT_BOOK;
	else if(Type == FLASK) return SPT_FLASK;
	else if(Type == GOLD) return SPT_GOLD;
	else if(Type == AMMUNITION) return SPT_AMMUNITION;
	else if(Type == FOOD) return SPT_FOOD;
	else if(Type == WAND) return SPT_WAND;
	else if(Type == CONTAINER) return SPT_CONTAINER;
	else return SPT_NON;
}

std::string Object::print_obj(){
	char buffer[70];
	sprintf(buffer, "%s A: %s W: %d", Name.c_str(), Damage->report_data().c_str(), Weight);
	std::string built = "";
	built.assign(buffer);
	return built;
}