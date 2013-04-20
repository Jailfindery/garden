/*
 *
 *  Log file class definition for garden.
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

#ifndef LOG_FILE_H_INCLUDED
#define LOG_FILE_H_INCLUDED

#include <string>

using namespace std;

class log_file
{
  private:
	string path;
  public:
	log_file(string new_path);
	int write(string message);
};

#endif /* LOG_FILE_H_INCLUDED */

