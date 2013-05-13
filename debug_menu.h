#ifndef DEBUG_MENU_H_INCLUDED
#define DEBUG_MENU_H_INCLUDED

#include <vector>

#include "dnc/dnc.h"
#include "x10dev.h"

class x10dev;	/* To allow compilation */

/* debug_menu must contain the following sub-menus:
 *   - Main
 *   |--> X10 Devices
 *      |--> Specific X10 Device
 *   |--> Circuits (when implemented)
 *   |--> Time (Unix Day Time)
 */
class debug_menu
{
  friend class x10dev;
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
	void add_x10(x10dev* new_dev) { x10_list.push_back(new_dev); }
	int start();
	int main_menu();
};

#endif /* DEBUG_MENU_H_INCLUDED */

