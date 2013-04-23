/*
 *
 * Configuration file interpreter class definition for garden.
 * Copyright (C) 2013 Joshua Schell (joshua.g.schell@gmail.com)
 *
 * garden is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * garden is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with garden. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef CONF_FILE_H_INCLUDED
#define CONF_FILE_H_INCLUDED

#include <string>
#include <vector>

using namespace std;

struct x10dev_conf
{
	string name;
	int on_time;
	int off_time;
	char housecode;
	int unit;

	x10dev_conf()	/* Sets defaults */
	{
		name = "unknown";
		on_time = -1;
		off_time = -1;
		housecode = '\0';
		unit = -1;
	}
};

class conf_file
{
 private:
	string conf_name;
	string error_variable(int line, string MyVariable);
	string error_data(int line, string data);
 public:
	conf_file(string file_path);

	/* Add configuration variables here */
	int x10_number;
	vector<x10dev_conf*> x10_devices;
	int ph_pin;
	int nutrient_pin;
	int level_pin;
};

#endif /* CONF_FILE_H_INCLUDED */

