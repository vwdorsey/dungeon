#include "parser.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <cstring>

std::vector<mon_template> parser::parse_defs_file(){
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
	
	defspath = (char*)malloc(strlen(path) + strlen(defs_filename) + 4);
	sprintf(defspath, "%s%s", path, defs_filename);
	
	std::string in_string; 
	std::vector<std::string> in_store;
	std::vector<mon_template> def_store;
	
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
	
	mon_template* mon;
	int valid_file_header = 0;
	int on_monster_def = 0;
	int in_description = 0;
	
	for(int i = 0; i < (int)in_store.size(); i++){
		in_string = in_store[i];
		if(in_string.find("RLG229")!=std::string::npos){
			valid_file_header = 1;
		}
		else if(in_string.find("BEGIN")!=std::string::npos){
			mon = new mon_template();
			on_monster_def = 1;
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
			std::string base_s = in_string.substr(6, in_string.find_first_of('+')-6);
			std::string num_s = in_string.substr(in_string.find("+")+1, in_string.find("d")- in_string.find("+")-1);
			std::string sides_s = in_string.substr(in_string.find("d")+1);
			
			mon->Speed.base = atoi(base_s.c_str());
			mon->Speed.num_dice = atoi(num_s.c_str());
			mon->Speed.sides = atoi(sides_s.c_str());
		}
		else if(in_string.find("DAM")!=std::string::npos){
			std::string base_s = in_string.substr(4, in_string.find_first_of('+')-3);
			std::string num_s = in_string.substr(in_string.find("+")+1, in_string.find("d")- in_string.find("+")-1);
			std::string sides_s = in_string.substr(in_string.find("d")+1);
			
			mon->Damage.base = atoi(base_s.c_str());
			mon->Damage.num_dice = atoi(num_s.c_str());
			mon->Damage.sides = atoi(sides_s.c_str());
		}
		else if(in_string.find("HP")!=std::string::npos){
			std::string base_s = in_string.substr(3, in_string.find_first_of('+')-3);
			std::string num_s = in_string.substr(in_string.find("+")+1, in_string.find("d")- in_string.find("+")-1);
			std::string sides_s = in_string.substr(in_string.find("d")+1);
			
			mon->HP.base = atoi(base_s.c_str());
			mon->HP.num_dice = atoi(num_s.c_str());
			mon->HP.sides = atoi(sides_s.c_str());
		}
		else if(in_string.find("ABIL")!=std::string::npos){
			std::string abils = in_string.substr(5);
			if(abils.find("PASS")!=std::string::npos) mon->Attribs += PASS;
			if(abils.find("TUNNEL")!=std::string::npos) mon->Attribs += TUNNEL;
			if(abils.find("SMART")!=std::string::npos) mon->Attribs += IS_SMART;
			if(abils.find("TELE")!=std::string::npos) mon->Attribs += TELEPATHIC;
		}
		else if(in_string.find("END")!=std::string::npos){
			def_store.push_back(*mon);
		}
	}
	return def_store;
}

void parser::output_mon_defs(std::vector<mon_template> def_store){
	for(int i = 0; i < def_store.size(); i++){
		std::cout << "Name: " << def_store[i].Name << '\n';
		std::cout << "Sprite: " << def_store[i].Sprite << '\n';
		std::cout << "Color: " << def_store[i].Color << '\n';
		std::cout << "Description: \n";
		for(int k = 0; k < def_store[i].Description.size(); k++){
			std::cout << def_store[i].Description[k] << '\n';
		}
		std::cout << "Attributes: ";
		uint16_t att = def_store[i].Attribs;
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
		std::cout << "Speed: " << def_store[i].Speed.base << '+' << def_store[i].Speed.num_dice << 'd' << def_store[i].Speed.sides << '\n';
		std::cout << "Damage: " << def_store[i].Damage.base << '+' << def_store[i].Damage.num_dice << 'd' << def_store[i].Damage.sides << '\n';
		std::cout << "HP: " << def_store[i].HP.base << '+' << def_store[i].HP.num_dice << 'd' << def_store[i].HP.sides << '\n';
		std::cout << '\n';
	}
}
