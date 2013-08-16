/*
 *
 *  CM17A (X10 Firecracker) module class definition for garden.
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

#include <string>
#include <utility>

#include "x10dev.h"

using namespace std;

/* Used to simplify the br_cmd() function */
enum br_command
{
	on = 0,
	off = 1
};

/* This class replaces static members
 * of x10dev in order to make fc module
 * code support RAII.
 */

/* Exceptions:
    * runtime_error - Constructor
 */
class fc_module
{
  private:
	int fd;
  public:
	fc_module(string path);
	~fc_module();

	/* X10 state-altering functions */
	pair<int, string> on(x10dev& _dev);
	pair<int, string> off(x10dev& _dev);
};

