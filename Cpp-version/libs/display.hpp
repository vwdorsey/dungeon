#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <cstdint>
#include "structs.hpp"
#include "values.hpp"

	class display{
		public:
			struct draw_container{
				char sprite;
				short color;
			};
			void end_session();
			void init_display();
			void redraw(tile layout[columns][rows], Player* pc);
			void redraw_with_templates(tile layout[columns][rows], Player* me);
			void draw_color(int i, int j, draw_container draw);
	};

#endif
