/*
 *
 *  Log file class implementation for garden.
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

#include <fstream>
#include <string>

#include "clock.h"
#include "log_file.h"

using namespace std;

log_file::log_file(string new_path)
{
	path = new_path;
	ofstream test_stream(path.c_str(), ios_base::app);
	if(test_stream.fail() )		/* Ensures log file is available */
		throw string("Unable to open log file for writing");
	test_stream.close();
}

/* int return is for error-checking,
 * although none really exists currently.
 */
int log_file::write(string message)
{
	ofstream log(path.c_str(), ios_base::app);
	if(log.fail() )
		return -1;
	log << (GetReadableTime() + " " + message) << endl;
	log.close();
	return 0;	/* TODO: Additional error-checking */
}

