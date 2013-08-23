/*
 *
 *  CM17A (X10 Firecracker) module class implementation for garden.
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

#include <stdexcept>
#include <string>
#include <utility>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "fc_module.h"

extern "C" {
#include "br/br_cmd.h"
}

using namespace std;

fc_module::~fc_module()
{
	::close(fd);	/* Ensure that it really is closed */
}

void fc_module::open()
{
	/* Ensures that one does not opne the stdout of
	 * the module (they did it in bottlerocket...).
	 */
	while(fd = ::open("/dev/null", 0, 0) < 3)
		if(fd < 0)
			throw runtime_error("Unable to open X10 Firecracker module at " +
			                    path);
	::close(fd);

	/* Actually open the device */
	fd = ::open(path.c_str(), O_RDONLY | O_NONBLOCK);
	if(fd < 0)
		throw runtime_error("Unable to open X10 Firecarcker module at " +
		                    path);
}

void fc_module::close()	/* I don't want to include the fd headers again... */
{
	::close(fd);
}

/* Issue: Add working checking of current X10 status.
 *
 * ... but is that even practical?
 * Because X10 devices do not have two-way communication, can one assume that it
 * is off when it is created or even if the on/off command worked?
 *
 * I decided that it is not practical, but state information will be retained
 * for runtime-checking. Taking into account the previous conclusion, this data
 * can not be held to be accurate.
 */
pair<int, string> fc_module::on(x10dev* _dev)
{
	open();
	int result = br_cmd(fd, _dev->get_address(), br_command::on);
	close();

	if(result < 0)	/* If it failed */
		return make_pair(-1, _dev->get_name() + ": Unable to activate");
	_dev->set_status(1);	/* Set status for data collection */
	return make_pair(0, _dev->get_name() + ": Activated successfully");
}

pair<int, string> fc_module::off(x10dev* _dev)
{
	open();
	int result = br_cmd(fd, _dev->get_address(), br_command::off);
	close();

	if(result < 0)	/* If it failed */
		return make_pair(-1, _dev->get_name() + ": Unable to deactivate");
	_dev->set_status(0);	/* Set status for data collection */
	return make_pair(0, _dev->get_name() + ": Deactivated successfully");
}

