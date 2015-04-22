#include "parser.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <cstring>

std::vector<Char_template*> parser::parse_defs_file(){
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
	std::vector<Char_template*> def_store;
	
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
	
	Char_template* mon;
	int valid_file_header = 0;
	int on_valid_character_def = 0;
	int in_description = 0;
	
	for(int i = 0; i < (int)in_store.size(); i++){
		in_string = in_store[i];
		if(in_string.find("RLG229")!=std::string::npos){
			valid_file_header = 1;
		}
		else if(in_string.find("BEGIN MONSTER")!=std::string::npos){
			mon = new Char_template();
			on_valid_character_def = 1;
		}
		else if(in_string.find("NAME")!=std::string::npos){
			mon->Name = in_string.substr(5);
		}
		else if(in_string.find("SYMB")!=std::string::npos){
			mon->Sprite = in_string[in_string.find(' ')+1];
		}
		else if(in_string.find("COLOR")!=std::string::npos){
			std::string color = in_string.substr(6);
			if(color == "BLACK") mon->Color = BLACK;
			if(color == "RED") mon->Color = RED;
			if(color == "GREEN") mon->Color = GREEN;
			if(color == "YELLOW") mon->Color = YELLOW;
			if(color == "BLUE") mon->Color = BLUE;
			if(color == "CYAN") mon->Color = CYAN;
			if(color == "MAGENTA") mon->Color = MAGENTA;
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
			mon->Speed = new Dice(in_string, 6);
		}
		else if(in_string.find("DAM")!=std::string::npos){
			mon->Damage = new Dice(in_string, 4);
		}
		else if(in_string.find("HP")!=std::string::npos){
			mon->HP = new Dice(in_string, 3);
		}
		else if(in_string.find("ABIL")!=std::string::npos){
			std::string abils = in_string.substr(5);
			if(abils.find("PASS")!=std::string::npos){
				mon->Attribs += PASS;
			} 
			if(abils.find("TUNNEL")!=std::string::npos) mon->Attribs += TUNNEL;
			if(abils.find("SMART")!=std::string::npos) mon->Attribs += IS_SMART;
			if(abils.find("TELE")!=std::string::npos) mon->Attribs += TELEPATHIC;
			if(abils.find("CHARACTER")!=std::string::npos) mon->Attribs += IS_CHARACTER;
		}
		else if(in_string.find("END")!=std::string::npos){
			def_store.push_back(mon);
		}
	}
	free(defspath);
	return def_store;
}

void parser::output_mon_defs(std::vector<Char_template*> def_store){
	for(int i = 0; i < def_store.size(); i++){
		def_store[i]->printout();
	}
}

std::vector<Obj_template*> parser::parse_objs_file(){
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
	free(path);
	std::string in_string; 
	std::vector<std::string> in_store;
	std::vector<Obj_template*> def_store;
	
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
	
	Obj_template* obj;
	int valid_file_header = 0;
	int on_valid_object_def = 0;
	int in_description = 0;
	
	for(int i = 0; i < (int)in_store.size(); i++){
		in_string = in_store[i];
		if(in_string.find("RLG229 OBJECT DESCRIPTION")!=std::string::npos){
			valid_file_header = 1;
		}
		else if(valid_file_header){
			if(in_string.find("BEGIN OBJECT")!=std::string::npos){
				if(on_valid_object_def){
					on_valid_object_def = 0;
					delete obj;
				}
				obj = new Obj_template();
				on_valid_object_def = 1;
			}
			if(on_valid_object_def){
				//Object Name
				if(in_string.find("NAME")!=std::string::npos){
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
					if(type.find("WEAPON")!=std::string::npos){
						if(type.find("OFFHAND")!=std::string::npos) obj->Type += WEAPON + OFFHAND;
						else obj->Type += WEAPON;
					}
					if(type.find("OFFHAND")!=std::string::npos && (!(type.find("WEAPON")!=std::string::npos))) obj->Type += OFFHAND;
					if(type.find("RANGED")!=std::string::npos) obj->Type += RANGED;
					if(type.find("ARMOR")!=std::string::npos) obj->Type += ARMOR;
					if(type.find("HELMET")!=std::string::npos) obj->Type += HELMET;
					if(type.find("CLOAK")!=std::string::npos) obj->Type += CLOAK;
					if(type.find("GLOVES")!=std::string::npos) obj->Type += GLOVES;
					if(type.find("BOOTS")!=std::string::npos) obj->Type += BOOTS;
					if(type.find("RING")!=std::string::npos) obj->Type += RING;
					if(type.find("AMULET")!=std::string::npos) obj->Type += AMULET;
					if(type.find("LIGHT")!=std::string::npos) obj->Type += LIGHT;
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
					std::string color = in_string.substr(6);
					if(color == "BLACK") obj->Color = BLACK;
					if(color == "RED") obj->Color = RED;
					if(color == "GREEN") obj->Color = GREEN;
					if(color == "YELLOW") obj->Color = YELLOW;
					if(color == "BLUE") obj->Color = BLUE;
					if(color == "CYAN") obj->Color = CYAN;
					if(color == "MAGENTA") obj->Color = MAGENTA;
				}
				//Dice Values
				else if(in_string.find("HIT")!=std::string::npos){
					obj->Hit = new Dice(in_string, 4);
				}
				else if(in_string.find("DAM")!=std::string::npos){
					obj->Damage = new Dice(in_string, 4);
				}
				else if(in_string.find("DODGE")!=std::string::npos){
					obj->Dodge = new Dice(in_string, 6);
				}
				else if(in_string.find("DEF")!=std::string::npos){
					obj->Defense = new Dice(in_string, 4);
				}
				else if(in_string.find("WEIGHT")!=std::string::npos){
					obj->Weight = new Dice(in_string, 7);
				}
				else if(in_string.find("SPEED")!=std::string::npos){
					obj->Speed = new Dice(in_string, 6);
				}
				else if(in_string.find("ATTR")!=std::string::npos){
					obj->SpecAttr = new Dice(in_string, 5);
				}
				else if(in_string.find("VAL")!=std::string::npos){
					obj->Value = new Dice(in_string, 4);
				}
				//Ending Tag
				else if(in_string.find("END")!=std::string::npos){
					if(obj->do_sanity_check()){
						def_store.push_back(obj);
						on_valid_object_def = 0;
					}
					else {
						delete(obj);
						on_valid_object_def = 0;
					}
				}
			}
		}
		else{
		std::cout << "The object definition file doesn't have a valid header. Please check the file." << '\n';
		}
	}
	
	free(defspath);
	return def_store;
}

void parser::output_obj_defs(std::vector<Obj_template*> def_store){
	for(int i = 0; i < def_store.size(); i++){
		def_store[i]->printout();
	}
}

void parser::kill_mon_defs(std::vector<Char_template*> defs){
	while(defs.size() > 0){
		Char_template* mon = defs.back();
		delete(mon);
		defs.pop_back();
	}
}

void parser::kill_obj_defs(std::vector<Obj_template*> defs){
	while(defs.size() > 0){
		Obj_template* obj = defs.back();
		delete(obj);
		defs.pop_back();
	}
}
