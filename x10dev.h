/*
 *
 *  CM17A (X10 Firecracker) implementation class header for garden.
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

#include <string>

using namespace std;

class x10dev
{
private:
	static int device;
	unsigned char address;
	string name;	/* This may need to be eliminated if it has no use... */
	bool status;
protected:
	int on();
	int off();
/*
 * on() and off() members return:
 *
 * -1 when unable to turn on
 * 1 if it is already on, but still successful
 *
 */
public:
	x10dev(char house, int unit, string new_name);
	virtual ~x10dev();
	static int open_device(string path);
	static void close_device();
	string get_name();
};

#endif

