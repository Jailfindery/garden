/*
 *
 *  Hydrogarden interface class implementation for garden.
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

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "fc_module.h"
#include "hg_interface.h"
#include "x10dev.h"

using namespace std;

void hg_interface::x10dev_alter(int i, bool state)
{
	/* Make sure that fcm points to something */
	if(fcm == nullptr)
		throw runtime_error("hg_interface: the Firecracker module is not defined");
	/* Otherwise, we would seg fault. */

	/* Alter the x10 device accordingly */
	pair<int, string> result;
	if(state)
		result = fcm->on(x10dev_list[i]);
	else
		result = fcm->off(x10dev_list[i]);

	/* Log the output */
	/* TODO: Add more specific logging information? */
	if(log != nullptr)
		log->write(result.second);
	else
		cout << result.second << endl;
}

