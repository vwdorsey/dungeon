#include "parser.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <cstring>

std::vector<mon_template*> parser::parse_defs_file(){
	char* home; 
	char* path;
	char* defspath;
	
	home = getenv("HOMEPATH"); //This should work for Windows machines.
	
	if (home == NULL){
		home = getenv("HOME"); //This definitely works for Linux.
	}
	
	path = (char*)malloc(strlen(home) + strlen(".rlg229/") + 4);
	sprintf(path, "%s/%s", home, ".rlg229/");
	mkdir(path, S_IRWXU);
	
	defspath = (char*)malloc(strlen(path) + strlen(defs_filename) + 4);
	sprintf(defspath, "%s%s", path, defs_filename);
	
	std::string in_string; 
	std::vector<std::string> in_store;
	std::vector<mon_template*> def_store;
	
	std::ifstream deffile(defspath);
	free(path);
	if(deffile.is_open()){
		while(getline(deffile, in_string)){
			in_store.push_back(in_string);
		}
		deffile.close();
	}
	else {
		return def_store;
	}
	
	mon_template* mon;
	int valid_file_header = 0;
	int on_valid_monster_def = 0;
	int in_description = 0;
	
	for(int i = 0; i < (int)in_store.size(); i++){
		in_string = in_store[i];
		if(in_string.find("RLG229")!=std::string::npos){
			valid_file_header = 1;
		}
		else if(in_string.find("BEGIN MONSTER")!=std::string::npos){
			mon = new mon_template();
			on_valid_monster_def = 1;
		}
		else if(in_string.find("NAME")!=std::string::npos){
			mon->Name = in_string.substr(5);
		}
		else if(in_string.find("SYMB")!=std::string::npos){
			mon->Sprite = in_string[in_string.find(' ')+1];
		}
		else if(in_string.find("COLOR")!=std::string::npos){
			mon->Color = in_string.substr(6);
		}
		else if(in_string.find("DESC")!=std::string::npos){
			in_description = 1;
		}
		else if(in_description){
			if(in_string[0] == '.'){
				in_description = 0;
			}
			else {
				mon->Description.push_back(in_string);
			}
		}
		else if(in_string.find("SPEED")!=std::string::npos){
			mon->Speed = create_dice(in_string, 6);
		}
		else if(in_string.find("DAM")!=std::string::npos){
			mon->Damage = create_dice(in_string, 4);
		}
		else if(in_string.find("HP")!=std::string::npos){
			mon->HP = create_dice(in_string, 3);
		}
		else if(in_string.find("ABIL")!=std::string::npos){
			std::string abils = in_string.substr(5);
			if(abils.find("PASS")!=std::string::npos) mon->Attribs += PASS;
			if(abils.find("TUNNEL")!=std::string::npos) mon->Attribs += TUNNEL;
			if(abils.find("SMART")!=std::string::npos) mon->Attribs += IS_SMART;
			if(abils.find("TELE")!=std::string::npos) mon->Attribs += TELEPATHIC;
		}
		else if(in_string.find("END")!=std::string::npos){
			def_store.push_back(mon);
		}
	}
	free(defspath);
	return def_store;
}

void parser::output_mon_defs(std::vector<mon_template*> def_store){
	for(int i = 0; i < def_store.size(); i++){
		std::cout << "Name: " << def_store[i]->Name << '\n';
		std::cout << "Sprite: " << def_store[i]->Sprite << '\n';
		std::cout << "Color: " << def_store[i]->Color << '\n';
		std::cout << "Description: \n";
		for(int k = 0; k < def_store[i]->Description.size(); k++){
			std::cout << def_store[i]->Description[k] << '\n';
		}
		std::cout << "Attributes: ";
		uint16_t att = def_store[i]->Attribs;
		if(att >= 8){
			att -=  8;
			std::cout << "PASS ";
		}
		if(att >= 4){
			att -=  4;
			std::cout << "TUNNEL ";  
		}
		if(att >= 2){
			att -=  2;
			std::cout << "TELE ";
		}
		if(att == 1){
			att -=  1;
			std::cout << "SMART";  
		}
		std::cout << '\n';
		std::cout << "Dice Values:";
		std::cout << "Speed: " << def_store[i]->Speed->base << '+' << def_store[i]->Speed->num_dice << 'd' << def_store[i]->Speed->sides << '\n';
		std::cout << "Damage: " << def_store[i]->Damage->base << '+' << def_store[i]->Damage->num_dice << 'd' << def_store[i]->Damage->sides << '\n';
		std::cout << "HP: " << def_store[i]->HP->base << '+' << def_store[i]->HP->num_dice << 'd' << def_store[i]->HP->sides << '\n';
		std::cout << '\n';
	}
}

std::vector<obj_template*> parser::parse_objs_file(){
	char* home;
	char* path;
	char* defspath;
	FILE* load;
	
	home = getenv("HOMEPATH"); //This should work for Windows machines.
	
	if (home == NULL){
		home = getenv("HOME"); //This definitely works for Linux.
	}
	
	path = (char*)malloc(strlen(home) + strlen(".rlg229/") + 4);
	sprintf(path, "%s/%s", home, ".rlg229/");
	mkdir(path, S_IRWXU);
	
	defspath = (char*)malloc(strlen(path) + strlen(objs_filename) + 4);
	sprintf(defspath, "%s%s", path, objs_filename);
	
	std::string in_string; 
	std::vector<std::string> in_store;
	std::vector<obj_template*> def_store;
	
	std::ifstream deffile(defspath);
	if(deffile.is_open()){
		while(getline(deffile, in_string)){
			in_store.push_back(in_string);
		}
		deffile.close();
	}
	else {
		return def_store;
	}
	
	obj_template* obj;
	int valid_file_header = 0;
	int on_valid_object_def = 0;
	int in_description = 0;
	
	for(int i = 0; i < (int)in_store.size(); i++){
		in_string = in_store[i];
		if(in_string.find("RLG229 OBJECT DESCRIPTION")!=std::string::npos){
			valid_file_header = 1;
		}
		else if(in_string.find("BEGIN OBJECT")!=std::string::npos){
			obj = new obj_template();
			on_valid_object_def = 1;
		}
		//Object Name
		else if(in_string.find("NAME")!=std::string::npos){
			obj->Name = in_string.substr(5);
		}
		//Description
		else if(in_string.find("DESC")!=std::string::npos){
			in_description = 1;
		}
		else if(in_description){
			if(in_string[0] == '.'){
				in_description = 0;
			}
			else {
				obj->Description.push_back(in_string);
			}
		}
		//Type Stuff
		else if(in_string.find("TYPE")!=std::string::npos){
			std::string type = in_string.substr(5);
			if(type.find("WEAPON")!=std::string::npos) obj->Type += WEAPON + IS_EQUIPMENT;
			if(type.find("OFFHAND")!=std::string::npos) obj->Type += OFFHAND + IS_EQUIPMENT;
			if(type.find("RANGED")!=std::string::npos) obj->Type += RANGED + IS_EQUIPMENT;
			if(type.find("ARMOR")!=std::string::npos) obj->Type += ARMOR + IS_EQUIPMENT;
			if(type.find("HELMET")!=std::string::npos) obj->Type += HELMET + IS_EQUIPMENT;
			if(type.find("CLOAK")!=std::string::npos) obj->Type += CLOAK + IS_EQUIPMENT;
			if(type.find("GLOVES")!=std::string::npos) obj->Type += GLOVES + IS_EQUIPMENT;
			if(type.find("BOOTS")!=std::string::npos) obj->Type += BOOTS + IS_EQUIPMENT;
			if(type.find("RING")!=std::string::npos) obj->Type += RING + IS_EQUIPMENT;
			if(type.find("AMULET")!=std::string::npos) obj->Type += AMULET + IS_EQUIPMENT;
			if(type.find("LIGHT")!=std::string::npos) obj->Type += LIGHT + IS_EQUIPMENT;
			if(type.find("SCROLL")!=std::string::npos) obj->Type += SCROLL;
			if(type.find("BOOK")!=std::string::npos) obj->Type += BOOK;
			if(type.find("FLASK")!=std::string::npos) obj->Type += FLASK;
			if(type.find("GOLD")!=std::string::npos) obj->Type += GOLD;
			if(type.find("AMMUNITION")!=std::string::npos) obj->Type += AMMUNITION;
			if(type.find("FOOD")!=std::string::npos) obj->Type += FOOD;
			if(type.find("WAND")!=std::string::npos) obj->Type += WAND;
			if(type.find("CONTAINER")!=std::string::npos) obj->Type += CONTAINER;
		}
		//Finds Color
		else if(in_string.find("COLOR")!=std::string::npos){
			obj->Color = in_string.substr(6);
		}
		//Dice Values
		else if(in_string.find("HIT")!=std::string::npos){
			obj->Hit = create_dice(in_string, 4);
		}
		else if(in_string.find("DAM")!=std::string::npos){
			obj->Damage = create_dice(in_string, 4);
		}
		else if(in_string.find("DODGE")!=std::string::npos){
			obj->Dodge = create_dice(in_string, 6);
		}
		else if(in_string.find("DEF")!=std::string::npos){
			obj->Defense = create_dice(in_string, 4);
		}
		else if(in_string.find("WEIGHT")!=std::string::npos){
			obj->Weight = create_dice(in_string, 7);
		}
		else if(in_string.find("SPEED")!=std::string::npos){
			obj->Speed = create_dice(in_string, 6);
		}
		else if(in_string.find("ATTR")!=std::string::npos){
			obj->SpecAttr = create_dice(in_string, 5);
		}
		else if(in_string.find("VAL")!=std::string::npos){
			obj->Value = create_dice(in_string, 4);
		}
		//Ending Tag
		else if(in_string.find("END")!=std::string::npos){
			def_store.push_back(obj);
			on_valid_object_def = 0;
		}
	}
	return def_store;
}

void parser::output_obj_defs(std::vector<obj_template*> def_store){
	for(int i = 0; i < def_store.size(); i++){
		std::cout << def_store[i]->Name << '\n';
		for(int k = 0; k < def_store[i]->Description.size(); k++){
			std::cout << def_store[i]->Description[k] << '\n';
		}
		std::cout << "TYPE HOLDER" << '\n';
		std::cout << def_store[i]->Color << '\n';
		std::cout << def_store[i]->Hit->base << '+' << def_store[i]->Hit->num_dice << 'd' << def_store[i]->Hit->sides << '\n';
		std::cout << def_store[i]->Damage->base << '+' << def_store[i]->Damage->num_dice << 'd' << def_store[i]->Damage->sides << '\n';
		std::cout << def_store[i]->Dodge->base << '+' << def_store[i]->Dodge->num_dice << 'd' << def_store[i]->Dodge->sides << '\n';
		std::cout << def_store[i]->Defense->base << '+' << def_store[i]->Defense->num_dice << 'd' << def_store[i]->Defense->sides << '\n';
		std::cout << def_store[i]->Weight->base << '+' << def_store[i]->Weight->num_dice << 'd' << def_store[i]->Weight->sides << '\n';
		std::cout << def_store[i]->Speed->base << '+' << def_store[i]->Speed->num_dice << 'd' << def_store[i]->Speed->sides << '\n';
		std::cout << def_store[i]->SpecAttr->base << '+' << def_store[i]->SpecAttr->num_dice << 'd' << def_store[i]->SpecAttr->sides << '\n';
		std::cout << def_store[i]->Value->base << '+' << def_store[i]->Value->num_dice << 'd' << def_store[i]->Value->sides << '\n';
		std::cout << '\n';
	}
}

dice* parser::create_dice(std::string in_string, int init_offset){
	dice* Dice = new dice();
	std::string base_s = in_string.substr(init_offset, in_string.find_first_of('+')-3);
	std::string num_s = in_string.substr(in_string.find("+")+1, in_string.find("d")- in_string.find("+")-1);
	std::string sides_s = in_string.substr(in_string.find("d")+1);
	
	Dice->base = atoi(base_s.c_str());
	Dice->num_dice = atoi(num_s.c_str());
	Dice->sides = atoi(sides_s.c_str());
	return Dice;
}

void parser::kill_mon_defs(std::vector<mon_template*> defs){
	while(defs.size() > 0){
		mon_template* mon = defs.back();
		delete(mon->Speed);
		delete(mon->HP);
		delete(mon->Damage);
		delete(mon);
		defs.pop_back();
	}
}

void parser::kill_obj_defs(std::vector<obj_template*> defs){
	while(defs.size() > 0){
		obj_template* obj = defs.back();
		delete(obj->Hit);
		delete(obj->Damage);
		delete(obj->Dodge);
		delete(obj->Defense);
		delete(obj->Weight);
		delete(obj->Speed);
		delete(obj->SpecAttr);
		delete(obj->Value);
		delete(obj);
		defs.pop_back();
	}
	delete &defs;
}
