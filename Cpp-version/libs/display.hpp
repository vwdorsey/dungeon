#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <cstdint>
#include "tile.hpp"
#include "values.hpp"

	class display{
		public:
			struct draw_container{
				char sprite;
				short color;
			};
			void end_session();
			void init_display();
			//void redraw(tile layout[columns][rows], PC* pc);
			void redraw_with_templates(tile layout[columns][rows], PC* me);
			void draw_color(int i, int j, draw_container draw);
			void draw_equip_menu(PC* me, int mode);
			void draw_backpack_menu(PC* me, int mode);
			void AYS_prompt();
			void prompt(std::string text);
			draw_container active_disp[24][80];
	};

#endif
