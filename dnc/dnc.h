#ifndef DNC_H_INCLUDED
#define DNC_H_INCLUDED

#include <iostream>
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
		int height;
		WINDOW* shadow;
		int startx;
		int starty;
		std::string title;
		int width;
		WINDOW* win;
		static WINDOW* standard;

	public:
		basic_win(int height, int width, int starty, int startx);
		basic_win(winconf_t conf);
		virtual ~basic_win();
		static int start_ncurses();
		static int stop_ncurses();
		int set_colour(int colour_pair);
		static int set_colour_std(int colour_pair);
		void set_title(std::string new_title);
		int update();
		static int update_std();
	};

	class render
	{
	private:
		std::vector<basic_win*> win_list;
	public:
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
}

#endif

