/*
 *
 *  dnc (Double New Curses) classes for garden.
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
#include <ncurses.h>

#include "dnc.h"

WINDOW* style::basic_win::standard = NULL;

namespace style
{
	void wclear_screen(WINDOW* win)
	{
		int maxy, maxx;
		getmaxyx(win, maxy, maxx);
		for(int y = 0; y < maxy; y++)
		{
			for(int x = 0; x < maxx; x++)
			{
				mvwaddch(win, y, x, ' ');
			}
		}
	}
}

using namespace style;

basic_win::basic_win(int height, int width, int starty, int startx)
{
	shadow = newwin(height, width, (starty + 1), (startx + 2));
	wattrset(shadow, COLOR_PAIR(SHADOW));
	wclear_screen(shadow);

	win = newwin(height, width, starty, startx);
	wattrset(win, COLOR_PAIR(BLACKONWHITE));
	wclear_screen(win);
	box(win, ACS_VLINE, ACS_HLINE);
}

basic_win::basic_win(winconf_t conf)
{
	shadow = newwin(conf.height, conf.width, (conf.starty + 1), (conf.startx + 2));
	wattrset(shadow, COLOR_PAIR(SHADOW));
	wclear_screen(shadow);

	win = newwin(conf.height, conf.width, conf.starty, conf.startx);
	wattrset(win, COLOR_PAIR(BLACKONWHITE));
	wclear_screen(win);
	box(win, ACS_VLINE, ACS_HLINE);
}

basic_win::~basic_win()
{
	delwin(win);
	delwin(shadow);
	touchwin(standard);
	wrefresh(standard);
}

int basic_win::get_colour()
{
	return colour;
	/* COLOR_PAIR() still needs to be used! */
}

int basic_win::start_ncurses()
{
	standard = initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	if(standard == 0)
		return -1;

	// Colour definitions
	init_pair(BLACKONWHITE, COLOR_BLACK, COLOR_WHITE);
	init_pair(BLACKONCYAN, COLOR_BLACK, COLOR_CYAN);
	init_pair(SHADOW, COLOR_BLACK, COLOR_BLACK);
	init_pair(WHITEONRED, COLOR_WHITE, COLOR_RED);

	touchwin(stdscr);
	wrefresh(stdscr);
	return 0;
}

int basic_win::stop_ncurses()
{
	int result = endwin();
	return result;
}

int basic_win::set_colour(int colour_pair)
{
	colour = colour_pair;
	int result = wattrset(win, COLOR_PAIR(colour_pair) );
	return result;
}

int basic_win::set_colour_std(int colour_pair)
{
	int result = wattrset(stdscr, colour_pair);
	update_std();
	return result;
}

void basic_win::set_title(std::string new_title)
{
	int maxy, maxx, x;
	getmaxyx(win, maxy, maxx);
	x = ((maxx - (new_title.length() + 2)) / 2);
	mvwaddch(win, 0, x, ' ');
	waddstr(win, new_title.c_str());
	waddch(win, ' ');
}

int basic_win::update()
{
	int result;
	result |= touchwin(shadow);
	result |= wrefresh(shadow);
	result |= touchwin(win);
	result |= wrefresh(win);
	return result;
}

int basic_win::update_std()
{
	wclear_screen(standard);
	int result;
	result |= touchwin(standard);
	result |= wrefresh(standard);
	return result;
}

int render::map(basic_win* win)
{
	win_list.push_back(win);
	int result = win->update();
	return result;
}

int render::unmap()
{
	if(win_list.size() < 2)
		return -1;
	win_list.pop_back();

	int result;
	result |= basic_win::update_std();
	for(int i = 0; i < win_list.size(); i++)
	{
		win_list[i]->update();
	}
	return result;
}

void message_win::set_message(std::string new_message)
{
	int maxy, maxx;
	getmaxyx(win, maxy, maxx);

	int i = 0;
	for(int y = 2; y < (maxy - 2), i < new_message.length(); y++)
	{
		for(int x = 2; x < (maxx - 2), i < new_message.length(); x++, i++)
		{
			wmove(win, y, x);
			waddch(win, new_message[i]);
		}
	}
}
