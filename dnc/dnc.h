/*
 *
 *  dnc (Double New Curses) classes header for garden.
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


#ifndef DNC_H_INCLUDED
#define DNC_H_INCLUDED

#include <string>
#include <ncurses.h>
#include <vector>

/* TODO:
	* Implement copy and advanced constructors (?)
	* Allow message_win::set_message() to interpret newline chars
	* Make windows have a minimum size (defined by the screen size)
*/

namespace style
{
	const int BLACKONWHITE	= 1;
	const int BLACKONCYAN	= 2;
	const int SHADOW		= 3;
	const int WHITEONRED	= 4;

	struct winconf_t
	{
		int height;
		int startx;
		int starty;
		int width;
	};

	class render;

	class basic_win
	{
	friend render;
	protected:
		int colour;
		WINDOW* shadow;
		static WINDOW* standard;
		int startx;
		int starty;
		std::string title;
		virtual int update();
		static int update_std();
		WINDOW* win;
	public:
		basic_win(int height, int width, int starty, int startx);
		basic_win(winconf_t conf);
		virtual ~basic_win();
		int get_colour();
		static int start_ncurses();
		static int stop_ncurses();
		int set_colour(int colour_pair);
		static int set_colour_std(int colour_pair);
		void set_title(std::string new_title);
	};

	class render
	{
	private:
		std::vector<basic_win*> win_list;
	public:
		int frefresh();		/* Forces all windows in stack to be refreshed. */
		int map(basic_win* win);
		int unmap();
	};

	class message_win : public basic_win
	{
	private:
		std::string message;
	public:
		message_win(int height, int width, int starty, int startx) :
                    basic_win(height, width, starty, startx) {}
		message_win(winconf_t conf) : basic_win(conf) {}
		void set_message(std::string new_message);
	};

	class basic_progress: public message_win
	{
	private:
		int& numer;
		int denom;
		void draw_progress();
	public:
		basic_progress(int height, int width, int starty, int startx,
		               int& num, int den) : message_win(height, width, starty,
		               startx), numer(num), denom(den) { draw_progress();}
		basic_progress(winconf_t conf, int& num, int den) : message_win(conf),
		               numer(num), denom(den) { draw_progress(); }
		bool complete();
		int update_progress();
	};
}

#endif

