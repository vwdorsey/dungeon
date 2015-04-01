#ifndef PARSER_HPP
#define PARSER_HPP

#include "structs.hpp"

class parser{
	public:
		std::vector<mon_template> parse_defs_file();
		void output_mon_defs(std::vector<mon_template> defs);
};

#endif
