#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "clock.h"
#include "dnc/dnc.h"
#include "dnc/menu.h"
#include "interface.h"
#include "x10dev.h"

/* debug_menu must contain the following sub-menus:
 *   - Main
 *   |--> X10 Devices
 *      |--> Specific X10 Device
 *   |--> Circuits (when implemented)
 *   |--> Time (Unix Day Time)
 */
class debug_menu
{
  private:
	style::render* menu_stack;
	int maxx, maxy;
	vector<x10dev*> x10_list;
	// void circuit_menu();
	void time_menu();
	void x10_menu();
	void x10_menu_specific(x10dev* specific);
  public:
	debug_menu();
	~debug_menu();
	void add_x10(x10dev* new_dev) { x10_list.pushback(new_dev); }
	int main_menu();
};

debug_menu::debug_menu()
{
	style::basic_win::start_ncurses();
	getmaxyx(&maxy, &maxy);
	menu_stack = new render;
}

debug_menu::~debug_menu()
{
	style::basic_win::stop_ncurses();
	delete menu_stack;
	menu_stack = 0;
}

int debug_menu::main_menu()		/* All menus should follow this format: */
{
	/* Declaration and basic config for menu window */
	style::basic_menu* menu;
	winconf_t MyConf;
	MyConf.height = (maxx - 4);
	MyConf.width = (maxy - 4);
	MyConf.starty = 2;
	MyConf.startx = 2;

	/* Define the menu entries */
	const char* options[3] = { "X10 Devices", "Time", "Quit" };

	/* Create, post-configure, and render the menu */
	menu = new basic_menu(MyConf, options);
	menu->set_title("garden Debug - Main Menu");
	menu->set_message("Select an entry below:");
	menu_stack.map(menu);

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
			menu_stack.unmap();
			delete menu;
			menu = 0;
			style::basic_win::stop_ncurses();	/* B/c this is the main menu */
			return 0;
			break;
		  default:			/* Something else? */
			break;
		}
	}
	return -1;		/* Should never be reached */
}

void debug_menu::time_menu()	/* Not really a menu! */
{
	style::progress_win* win;
	winconf_t MyConf;
	MyConf.height = 9;
	MyConf.width = (maxy - 40);
	MyConf.startx = (maxx - 9) / 2;
	MyConf.starty = 20;

	/* Preparing time stuff */
	string currentTime = ctime(time(NULL) );
	currentTime.pop_back();
	int currentUDT = GetDayTime();

	win = new style::basic_progress(MyConf, currentUDT, 86400);
	win->set_title("Time Menu");
	win->set_message("Current Time: " + currentTime + "\n"
	                 "Current UDT : " + to_string(currentUDT) + "\n");
	menu_stack.map(win);
	getch();		/* Press any key to continue... */

	menu_stack.unmap();
	delete win;
	win = 0;
	return;
}

void debug_menu::x10_menu()
{
	style::basic_menu* menu;
	winconf_t MyConf;
	MyConf.height = (maxx - 6);
	MyConf.width = (maxy - 8);
	MyConf.starty = 3;
	MyConf.startx = 4;

	const char* options[x10_list.size() + 1];		/* I hate C-strings... */
	for(int i = 0; i < x10_list.size(); i++)
		options[i] = x10_list[i]->name.c_str();
	options[x10_list.size()] = "Exit";

	menu = new style::basic_menu(MyConf, options);
	menu_stack.map(menu);

	while(true)
	{
		int selected_entry = menu->select_item();
		if(selected_entry = x10_list.size() )	/* Last entry (i.e. quit) */
		{
			menu_stack.unmap();
			delete menu;
			menu = 0;
			return;
		}
		else	x10_menu_specific(x10_list[selected_entry]);
	}
	return;
}

/* TODO: Finish specific X10 device menu */
/* x10_menu_specific must display current information (e.g. on/off state)
 * as well as a way to alter their state
 */
void debug_menu::x10_menu_specific(x10dev* specific)
{

}
	

int main(int argc, char** argv)
{
	cout << "Reading configuration file... ";

	conf_file* MyConf;	/* Search for a conf file */
	if(argc > 1)
	{
	/* TODO: Make better command line options */
		try
		{
			MyConf = new conf_file(argv[1]);
		}
		catch(string& except)	/* Conf file does not exists */
		{
			cerr << "failed!" << endl
			cerr << "E:" << except << endl;
			cerr << "Unable to process provided configuration file." << endl;
			return -1;
		}
	}
	else
	{
		try		/* ~/.gardenrc */
		{
			MyConf = new conf_file("~/.gardenrc");
		}
		catch(...)	/* It failed, but we don't care why; we simply move on. */
		{
			delete MyConf;	/* Ensures the pointer is cleared. */
			MyConf = 0;
		}
		if(MyConf == 0)
		{
			try		/* /etc/garden.conf */
			{
				MyConf = new conf_file("/etc/garden.conf");
			}
			catch(...)	/* Also failed, but we must move on... */
			{
				delete MyConf;
				MyConf = 0;
			}
		}
		/* One could check other places as well... */
	}
	if(MyConf == 0)		/* If no configuration was found at this point... */
	{
		cerr << "failed!" << endl;
		cerr << "E: No suitable configuration file was found." << endl;
		cerr << "Please create one in /etc/garden.conf or ~/.gardenrc." << endl;
		return -1;
	}
	cout << "done." << end;

	/* By creating the Interface first, it
	 * becomes simpler to add X10 devices.
	 */
	cout << "Creating hydrogarden interface... " << endl;
	Interface* MyInterface = new Interface;
	cout << "done." << endl;

	debug_menu MyMenu;	/* Create the TUI */

	cout << "Populating X10 devices... ";
	vector<x10dev*> device_list;
	for(int i = 0; i < MyConf.x10_number; i++)
	{
		char temp_house = MyConf->x10_devices[i]->housecode;
		int temp_unit; = MyConf->x10_devices[i]->unit;
		string temp_name = MyConf->x10_devices[i]->name;
		x10dev* temp_x10;

		try
		{
			temp_x10 = new x10dev(temp_house, temp_unit, temp_name);
		}
		catch(string& except)
		{
			cerr << "failed!" << endl;
			cerr << "E: X10 device, index " << i << ": ";
			cerr << excpt << endl;
			return -1;
		}
		MyInterface->deviceList.push_back(temp_x10);
		MyMenu->add_x10(temp_x10);
	}
	cout << "done." << end;

	/* TODO: Add circuit initialization. */

	return MyMenu.main_menu();
}

