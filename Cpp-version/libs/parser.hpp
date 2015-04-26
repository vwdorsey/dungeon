#ifndef PARSER_HPP
#define PARSER_HPP

#include "char_template.hpp"
#include "obj_template.hpp"
#include "values.hpp"

class parser{
	public:
		std::vector<Char_template*> parse_defs_file(); 
		void output_mon_defs(std::vector<Char_template*> defs);
		std::vector<Obj_template*> parse_objs_file();
		void output_obj_defs(std::vector<Obj_template*> defs);
		void kill_mon_defs(std::vector<Char_template*> defs);
		void kill_obj_defs(std::vector<Obj_template*> defs);
	private:
		int check_monster(Char_template* mon);
		int check_object(Obj_template* obj);
};

#endif
