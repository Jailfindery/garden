#include <iostream>
#include <string>
#include <vector>

#include "dnc/dnc.h"
#include "dnc/menu.h"
#include "interface.h"
#include "x10dev.h"

/* debug_menu must contain the following sub-menus:
 *   - Main
 *   - X10 Devices
 *   - Circuits (when implemented)
 *   - Time (Unix Day Time)
 *   - Maybe some more...?
 */
class debug_menu
{
  private:
	style::render* menu_stack;
	int maxx, maxy;
	int x10_devices;
	// void circuit_menu();
	void time_menu();
	void x10_menu(int x10_number);
  public:
	debug_menu(int );
	~debug_menu();
	int main_menu();
};

debug_menu::debug_menu(int x10_number) : x10_devices(x10_number)
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

void debug_menu::time_menu()
{}

/* How does it figure out X10 device
 * information?
 */
void debug_menu::x10_menu()
{
	style::basic_menu* menu;
	winconf_t MyConf;
	MyConf.height = (maxx - 6);
	MyConf.width = (maxy - 8);
	MyConf.starty = 3;
	MyConf.startx = 4;
	const char* options[x10_devices] =
	{
	}

	/* TODO: Finish menu configuration and usage. */
	menu = new basic_menu(MyConf, 
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
		/* One could check other places as well. */
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
	Interface* MyInterface = new Reporter;
	cout << "done." << endl;

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
	}
	cout << "done." << end;

	/* TODO: Add circuit initialization. */

	/* TODO: Graphical environment, and giving the user control. */

	/* For the graphical environment, a class should be created
	 * that contains all windows and handles user input.
	 */

	return 0;
}

