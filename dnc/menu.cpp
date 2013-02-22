/*
 *
 *  dnc menu classes for garden.
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


#include <string>
#include <deque>
#include <menu.h>
#include <cstdlib>
#include <cstring>

#include "menu.h"

using namespace style;

/* TODO:
 *
 * This class uses cstrings to do its job,
 * but I hate cstrings and the feeling is
 * mutual. Menu items need to be reimplemented
 * sometime in the future.
 *
 * Update: A partial fix is implemented. At
 *         least it works now...
 */

basic_menu::basic_menu(int height, int width, int starty, int startx, const char* options[]) :
                       message_win(height, width, starty, startx)
{
	/** Initialize Subwindow */
	subwin = derwin(win, (height - 6), (width - 2), 4, 2);

	/** Initialize ITEM array */
	int MySize;
	std::string* temp;
	for(MySize = 0; options[MySize] != NULL; MySize++);		/* Calculates number of menu entries */
	items = (ITEM**)calloc( (MySize + 1), sizeof(ITEM*) );	/* Could be be done in cpp style? */
	for(int i = 0; i < MySize; i++)		/* Adds strings to the menu */
	{
		temp = new std::string(options[i]);		/* This type of thing may */
		while(temp->size() < (width - 7) )		/* cause a memory leak... */
			*temp += " ";
		options[i] = temp->c_str();
		items[i] = new_item(options[i], NULL);
	}
	items[MySize] = (ITEM*)NULL;	/* Required for ncurses menus */

	/** Initialize MENU */
	menu = new_menu(items);
	set_menu_win(menu, win);
	set_menu_sub(menu, subwin);
	set_menu_format(menu, (height - 7), 1);			/* NB! If the window height is <7, */
	set_menu_fore(menu, COLOR_PAIR(WHITEONRED) );	/* bad things will occur...        */ 
	set_menu_back(menu, COLOR_PAIR(BLACKONWHITE) );
	set_menu_mark(menu, "* ");
}

basic_menu::basic_menu(winconf_t conf, const char* options[]) : message_win(conf)
{
	subwin = derwin(win, (conf.height - 6), (conf.width - 2), 4, 2);

	int MySize;
	std::string* temp;
	for(MySize = 0; options[MySize] != NULL; MySize++);
	items = (ITEM**)calloc((MySize + 1), sizeof(ITEM*) );
	for(int i = 0; i < MySize; i++)
	{
		temp = new std::string(options[i]);
		while(temp->size() < (conf.width - 7) )
			*temp += " ";
		options[i] = temp->c_str();
		items[i] = new_item(options[i], NULL);
	}
	items[MySize] = (ITEM*)NULL;

	menu = new_menu(items);
	set_menu_win(menu, win);
	set_menu_sub(menu, subwin);
	set_menu_format(menu, (conf.height - 7), 1);
	set_menu_fore(menu, COLOR_PAIR(WHITEONRED) );
	set_menu_back(menu, COLOR_PAIR(BLACKONWHITE) );
	set_menu_mark(menu, "* ");
}

basic_menu::~basic_menu()
{
	unpost_menu(menu);

	/** Free subwin */
	delwin(subwin);

	/** Deallocate item storage */
	for(int i = 0; items[i] != NULL; i++)
		free_item(items[i]);
	delete items;
	items = 0;

	/** Deallocate menu */
	free_menu(menu);
}

int basic_menu::select_item()
{
	int MyChoice = -1;
	int ch;
	while(MyChoice == -1)
	{
		touchwin(subwin);
		wrefresh(subwin);
		ch = getch();
		switch(ch)
		{
		case KEY_UP:
			menu_driver(menu, REQ_UP_ITEM);
			break;
		case KEY_DOWN:
			menu_driver(menu, REQ_DOWN_ITEM);
			break;
		case 10:	/* Enter key */
			MyChoice = item_index(current_item(menu) );
			break;
		default:
			break;
		}
	}
	return MyChoice;
}

int basic_menu::update()
{
	int result;
	result |= post_menu(menu);
	result |= touchwin(shadow);
	result |= wrefresh(shadow);
	result |= touchwin(win);
	result |= wrefresh(win);
	result |= touchwin(subwin);
	result |= wrefresh(subwin);
	return result;
}

