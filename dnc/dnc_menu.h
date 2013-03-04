/*
 *
 *  dnc menu class header for garden.
 *  Copyright (C) 2013 Joshua Schell (joshua.g.schell@gmail.com)
 *
 *  garden is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  garden is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with garden.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <string>
#include <menu.h>

#include "dnc.h"

namespace style
{
	class basic_menu : public message_win
	{
	private:
		ITEM** items;
		MENU* menu;
		WINDOW* subwin;
	protected:
		int update();
	public:
		basic_menu(int height, int width, int starty, int startx, const char* options[]);
		basic_menu(winconf_t conf, const char* options[]);
		virtual ~basic_menu();
		int select_item();
	};
}

#endif

