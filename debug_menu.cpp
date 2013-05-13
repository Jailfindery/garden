#include <ctime>
#include <string>
#include <vector>

#define GARDEN_DEBUG	/* Gives direct access to X10 devices. */

#include "clock.h"
#include "dnc/dnc.h"
#include "dnc/dnc_menu.h"
#include "x10dev.h"

#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

debug_menu::debug_menu()
{
	menu_stack = new style::render;
}

debug_menu::~debug_menu()
{
	delete menu_stack;
	menu_stack = 0;
	style::basic_win::stop_ncurses();
}

int debug_menu::start()
{
	int MyReturn = style::basic_win::start_ncurses();
	style::basic_win::set_colour_std(COLOR_PAIR(style::BLACKONCYAN) );
	getmaxyx(stdscr, maxy, maxx);
	return MyReturn;
}

int debug_menu::main_menu()		/* All menus should follow this format: */
{
	/* Declaration and basic config for menu window */
	style::basic_menu* menu;
	style::winconf_t MyConf;
	MyConf.height = (maxy - 6);
	MyConf.width = (maxx - 6);
	MyConf.starty = 3;
	MyConf.startx = 3;

	/* Define the menu entries */
	const char* options[] = { "X10 Devices", "Time", "Quit", NULL };

	/* Create, post-configure, and render the menu */
	menu = new style::basic_menu(MyConf, options);
	menu->set_title("garden Debug - Main Menu");
	menu->set_message("Select an entry below:");
	menu_stack->map(menu);

	/* Menu run-time */
	/* Loop will cause the menu selection process to continue
	 * until unmapped or a new window is in focus.
	 */
	while(true)
	{
		/* Allow user to select an entry */
		int selected_entry = menu->select_item();
		/* Decide what that choice means */
		switch(selected_entry)
		{
		  case 0:			/* X10 Devices */
			x10_menu();
			break;
		  case 1:			/* Time */
			time_menu();
			break;
		  case 2:			/* Quit */
			/* Destruct the stuff before quiting */
			menu_stack->unmap();
			delete menu;
			menu = 0;
			return 0;
			break;
		  default:			/* Something else? */
			delete menu;
			menu = 0;
			break;
		}
	}
	delete menu;	/* Should never be reached */
	menu = 0;
	return -1;
}

void debug_menu::time_menu()	/* Not really a menu! */
{
	style::basic_progress* win;
	style::winconf_t MyConf;
	MyConf.height = 11;
	MyConf.width = (maxx - 40);
	MyConf.startx = (maxy - 9) / 2;
	MyConf.starty = 20;

	/* Preparing time stuff */
	time_t MyTime = time(NULL);	/* ctime() requires time_t* */
	string currentTime = ctime(&MyTime);
	currentTime.pop_back();
	int currentUDT = GetDayTime();

	win = new style::basic_progress(MyConf, currentUDT, 86400);
	win->set_title("Time Menu");
	win->set_message("Current Time: " + currentTime + "\n" +
	                 "Current UDT : " + to_string(currentUDT) + "\n");
	menu_stack->map(win);
	getch();		/* Press any key to continue... */

	menu_stack->unmap();
	delete win;
	win = 0;
	return;
}

void debug_menu::x10_menu()
{
	style::basic_menu* menu;
	style::winconf_t MyConf;
	MyConf.height = (maxy - 12);
	MyConf.width = (maxx - 12);
	MyConf.starty = (maxy - MyConf.height) / 2;
	MyConf.startx = (maxx - MyConf.width) / 2;

	const char* options[x10_list.size() + 2];		/* I hate C-strings... */
	for(int i = 0; i < x10_list.size(); i++)
		options[i] = x10_list[i]->get_name().c_str();
	options[x10_list.size()] = "Exit";
	options[x10_list.size() + 1] = NULL;

	menu = new style::basic_menu(MyConf, options);
	menu->set_title("X10 Devices");
	menu->set_message("The following X10 devices are connected:");
	menu_stack->map(menu);

	while(true)
	{
		int selected_entry = menu->select_item();
		if(selected_entry == x10_list.size() )	/* Last entry (i.e. quit) */
		{
			menu_stack->unmap();
			delete menu;
			menu = 0;
			return;
		}
		else	x10_menu_specific(x10_list[selected_entry]);
	}
	return;
}

/* x10_menu_specific must display current information (e.g. on/off state)
 * as well as a way to alter their state
 */
void debug_menu::x10_menu_specific(x10dev* specific)
{
	style::basic_menu* menu;
	style::winconf_t MyConf;
	MyConf.height = 10;
	MyConf.width = 45;
	MyConf.starty = (maxy - MyConf.height) / 2;
	MyConf.startx = (maxx - MyConf.width) / 2;

	const char* options[4] = { "Activate", "Deactivate", "Exit", NULL };

	/* Prepare specific X10 information */
	string specific_status;
	if(specific->get_status() )
		specific_status = "On";
	else
		specific_status = "Off";

	/* TODO: Fix address display */
	menu = new style::basic_menu(MyConf, options);
	menu->set_title(specific->get_name() + " Menu");
	menu->set_message("Name:    " + specific->get_name() + "\n" +
	                  "Address: " + "Unknown" + "\n" +
	                  "Status:  " + specific_status + "\n");
	menu_stack->map(menu);

	while(true)
	{
		switch(menu->select_item() )
		{
		  case 0:	/* Activate */
			specific->on();
			menu_stack->unmap();		/* Updates information */
			menu_stack->map(menu);
			break;
		  case 1:	/* Deactivate */
			specific->off();
			menu_stack->unmap();
			menu_stack->map(menu);
			break;
		  case 2:
			menu_stack->unmap();
			delete menu;
			menu = 0;
			return;
			break;
		  default:
			break;
		}
	}
	return;
}

