#include <iostream>
#include <strings.h>
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

int basic_win::start_ncurses()
{
	standard = initscr();
	start_color();
	/* Special options, such as cbreak(), need to be
	   put in main() after this function is called. */
	if(standard == 0)
		return -1;

	// Colour definitions
	init_pair(BLACKONWHITE, COLOR_BLACK, COLOR_WHITE);
	init_pair(BLACKONCYAN, COLOR_BLACK, COLOR_CYAN);

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
	int result = wattrset(win, colour_pair);
	return result;
}

int basic_win::set_colour_std(int colour_pair)
{
	int result = wattrset(stdscr, colour_pair);
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

