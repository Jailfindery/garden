#include <iostream>
#include <string>
#include <vector>

#include "conf_file.h"
#include "debug_menu.h"
#include "x10dev.h"

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
			cerr << "failed!" << endl;
			cerr << "E:" << except << endl;
			cerr << "Unable to process provided configuration file." << endl;
			return -1;
		}
	}
	else
	{
		/* TODO: Print error when config file is incorrect. */

		try		/* ~/.gardenrc */
		{
			MyConf = new conf_file("/home/josh/.gardenrc");
		}
		catch(...)	/* It failed, but we don't care why; we simply move on. */
		{
			MyConf = 0;	/* Ensures the pointer is cleared */
		}
		if(MyConf == 0)
		{
			try		/* /etc/garden.conf */
			{
				MyConf = new conf_file("/etc/garden.conf");
			}
			catch(...)	/* Also failed, but we must move on... */
			{
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
	cout << "done." << endl;

	/* TODO: Make X10 Firecracker path configurable. */
	cout << "Opening X10 Firecracker module... ";
	if(x10dev::open_device("/dev/ttyUSB0") < 3)	/* We should not use stdout. */
	{
		cerr << "failed!" << endl;
		cerr << "E: Unable to open Firecracker module." << endl;
		return -1;
	}
	cout << "done." << endl;

	debug_menu* MyMenu = new debug_menu;	/* Create the TUI */

	cout << "Populating X10 devices... ";
	vector<x10dev*> device_list;
	for(int i = 0; i < MyConf->x10_number; i++)
	{
		char temp_house = MyConf->x10_devices[i]->housecode;
		int temp_unit = MyConf->x10_devices[i]->unit;
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
			cerr << except << endl;

			delete MyMenu;		/* Ensures fb goes back to normal */
			MyMenu = 0;
			return -1;
		}
		MyMenu->add_x10(temp_x10);
	}
	cout << "done." << endl;

	/* TODO: Add circuit initialization. */

	if(MyMenu->start() != 0)
	{
		delete MyMenu;
		MyMenu = 0;
		cerr << "E: Failed to start ncurses." << endl;
		return -1;
	}
	int menu_return = MyMenu->main_menu();	/* Give control to the TUI */

	/* Stopping and clean-up */
	delete MyMenu;
	MyMenu = 0;
	for(int i = 0; i < device_list.size(); i++)
	{
		delete device_list[i];
		device_list[i] = 0;
	}
	x10dev::close_device();
	return menu_return;
}

