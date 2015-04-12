#ifndef PARSER_HPP
#define PARSER_HPP

#include "structs.hpp"

class parser{
	public:
		std::vector<mon_template*> parse_defs_file(); 
		void output_mon_defs(std::vector<mon_template*> defs);
		std::vector<obj_template*> parse_objs_file();
		void output_obj_defs(std::vector<obj_template*> defs);
		void kill_mon_defs(std::vector<mon_template*> defs);
		void kill_obj_defs(std::vector<obj_template*> defs);
	private:
		dice* create_dice(std::string in_string, int init_offset);
		int check_monster(mon_template* mon);
		int check_object(obj_template* obj);
};

#endif
