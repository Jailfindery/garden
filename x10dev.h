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

#include <string>

using namespace std;

class fc_module;

/* Exceptions:
    * invalid_argument - Constructor
 */
class x10dev
{
  friend class fc_module;

  private:
	/* X10 meta-data */
	char housecode;
	int unit;
	string name;
	unsigned char address;	/* br_cmd uses this */

	/* Used with the scheduler */
	int on_time;
	int off_time;

	/* X10 state information */
	bool status;

	/* Set access methods */
	void set_status(bool _status) { status = _status; }

public:
	/* NB! One must ensure that the X10 device is off _manually_. */
	x10dev(char house, int unit, string new_name, int _on, int _off);

	/* Get access methods */
	bool get_status() { return status; };
	/* For get_times(), first is the on time, second is the off time. */
	pair<int, int> get_times() { return make_pair(on_time, off_time); } 
	string get_address_readable() { return housecode + to_string(unit); };
	string get_name() { return name; }
	unsigned char get_address() { return address; }
};

#endif

