/*
 *
 *  CM17A (X10 Firecracker) class declaration for garden.
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

#ifndef X10DEV_H_INCLUDED
#define X10DEV_H_INCLUDED

#ifdef GARDEN_DEBUG
#include "debug_menu.h"
#endif

#include <string>

using namespace std;

struct x10dev_info	/* A lightweight struct with information about x10devs */
{
	x10dev_info(int index, int MyOn, int MyOff) : off_time(MyOff),
	                                              on_time(MyOn) {}
	int index;
	/* Unique, consistent ID for use in the Interface 
	 * NB! Consistent of the index depends
	 * on the implementation.
	 */
	int off_time;
	int on_time;
};

class x10dev
{
/* Static members represent the
 * actual X10 Firecracker module.
 */
  friend class Interface;	/* Allows Interface to activate it */

  private:
	static int device;		/* X10 Firecracker module file descriptor */
	unsigned char address;
	string name;
	bool status;

/* ifdef allows debug application to acces on() and off()
 * members directly.
 */
#ifdef GARDEN_DEBUG
  public:
#endif/* GARDEN_DEBUG */
	int on();
	int off();
/*
 * TODO: on() and off() members return:
 *
 * -1 when unable to turn on
 * 1 if it is already on, but still successful
 *
 */
public:
	x10dev(char house, int unit, string new_name);
	virtual ~x10dev();
	string get_status();
	static int open_device(string path);
	static void close_device();
	string get_name() { return name; }
	unsigned char get_address() { return address; }
};

#endif

