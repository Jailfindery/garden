/*
 *
 *  Hydrogarden interface class definition for garden.
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


#ifndef HG_INTERFACE_INCLUDED
#define HG_INTERFACE_INCLUDED

#include <utility>
#include <vector>

#include "log_file.h"

using namespace std;

class x10dev;	/* Forward referenece to resolve circular dependency */

/* hg_interface is a facade class that creates
 * a consistent interface for the hydrogarden
 * and logging.
 * Currently, it controls:
 *   - X10 Devices
 */
class hg_interface	/* NB! This object is not responsible any pointers */
{
  private:
	fc_module* fcm;		/* If set to nullptr, will cause exceptions when used */
	log_file* log;		/* If not using logging, this is set to nullptr */
	vector<x10dev*> x10dev_list;
  public:
	hg_interface() : fcm(nullptr), log(nullptr) {}
	/* Return from x10dev_*() contains an int for general exit status
	 * (0 for success, -1 for failure) and string for a description
	 * of the error.
	 */
	void x10dev_alter(int i, bool state);
	void add_fc_module(fc_module& _fcm) { fcm = &_fcm; }
	void add_log_file(log_file& _log) { log = &_log; };
	void add_x10dev(x10dev& _dev) { x10dev_list.push_back(&_dev); }
};

#endif /* HG_INTERFACE_INCLUDED */

