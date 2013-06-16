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

#include <sstream>
#include <string>
#include <ncurses.h>

#include "dnc.h"

WINDOW* style::basic_win::standard = NULL;

namespace style
{
	/* I don't always fail, but when
	 * I do, I always make C++11 stuff
	 * stop working...
	 *
	 * Love, g++
	 */
	std::string to_string(int MyInt)
	{
		std::ostringstream converter;
		converter << MyInt;
		return converter.str();
	}

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
	timeout(-1);
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

	/* Cursor is off by default */
	curs_set(0);	/* Can be changed manually for a specific use */
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
	int result = 0;
	result |= touchwin(shadow);
	result |= wrefresh(shadow);
	result |= touchwin(win);
	result |= wrefresh(win);
	return result;
}

int basic_win::update_std()
{
	wclear_screen(standard);
	int result = 0;
	result |= touchwin(standard);
	result |= wrefresh(standard);
	return result;
}

/* Used to deal with ncurses' strange way of
 * refreshing windows.
 */
int render::frefresh()
{
	int result = 0;
	std::vector<basic_win*>::iterator iter;
	for(iter = win_list.begin(); iter < win_list.end(); iter++)
	{
		basic_win* temp = *iter;
		result |= temp->update();
	}
	return result;
}

int render::map(basic_win* win)
{
	win_list.push_back(win);
	int result = win->update();
	result |= frefresh();	/* Workaround to make refreshes easier. */
	return result;
}

int render::unmap()
{
	if(win_list.size() < 1)
		return -1;
	win_list.pop_back();

	int result = 0;
	result |= basic_win::update_std();
	std::vector<basic_win*>::iterator iter;
	for(iter = win_list.begin(); iter < win_list.end(); iter++)
	{
		basic_win* temp = *iter;
		temp->update();
	}
	result |= frefresh();	/* Same workaround as above. */
	return result;
}

void message_win::set_message(std::string new_message)
{
	int maxy, maxx;
	getmaxyx(win, maxy, maxx);

	/* 'i' tracks string character, 'x' tracks x-value, 'y' tracks y-value */
	int i, x, y;
	for(i = 0, x = 2, y = 2; i < new_message.length(); i++, x++)
	{
		/* (width - 2) is the max horizontal length */
		if(new_message[i] == '\n')
		{
			x = 1;	/* x will be incremented after continue */
			y++;
			if(y >= (maxy - 2) )
				break;
			continue;
		}
		if(x >= (maxx - 2) )
		{
			x = 2;
			y++;
			if(y >= (maxy - 2) )	/* Max height - if exceeded, text will be cut off */
				break;
		}

		mvwaddch(win, y, x, new_message[i] );
	}
}

void basic_progress::draw_progress()
{
	int maxy, maxx;
	float percent;
	std::string text_data, bar_data;	/* text_data -> Top line
										   bar_data  -> Bottom line */
	getmaxyx(win, maxy, maxx);

	if(denom != 0 && numer < denom)	/* Ensure SIGFPE does not occur */
	{
		percent = (float)numer / (float)denom;
		percent *= 100;

		text_data += to_string( (int)percent) + '%';
		text_data += to_string(numer) + '/' + to_string(denom);

		/* Adds proper padding to string */
		while(text_data.length() < (maxx - 4) )	/* Spacing of 2 */
		{
			if(percent < 10)
				text_data.insert(2, 1, ' ');
			else if(percent < 100)
				text_data.insert(3, 1, ' ');
			else
				text_data.insert(4, 1, ' ');
		}

		/* Prepare bottom line */
		int bar_length = (maxx - 6) * (percent / 100);
		bar_data += '[';
		while(bar_data.length() < bar_length)	/* Equal to makes it the proper length */
			bar_data += '=';
		bar_data += '>';
		while(bar_data.length() < (maxx - (6 - 1) ) )	/* -1 because a ']' still needs to be added */
			bar_data += ' ';
		bar_data += ']';
	}
	else if(denom != 0 && numer >= denom)			/* When progress is complete */
	{
		text_data = "100%" + to_string(denom) + '/' + to_string(denom);
		while(text_data.length() < (maxx - 4) )
			text_data.insert(4, 1, ' ');

		bar_data = "[]";
		while(bar_data.length() < (maxx - 4) )	/* May need to be 6? */
			bar_data.insert(1, 1, '=');
	}
	else
	{
		text_data = "undefined";
		bar_data = "undefined";
	}

	/* Add strings to window */
	mvwaddstr(win, (maxy - 3), 2, text_data.c_str() );
	mvwaddstr(win, (maxy - 2), 2, bar_data.c_str() );

	return;
}

bool basic_progress::complete()
{
	if(numer >= denom)
		return 1;
	return 0;
}

int basic_progress::update_progress()
{
	draw_progress();
	return update();
}
	
