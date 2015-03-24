#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "structs.hpp"

	class display{
		public:
			void end_session();
			void init_display();
			void redraw(tile layout[columns][rows], Player* pc);
	};

#endif
