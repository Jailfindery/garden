/*
 *
 * Configuration file interpreter class implementation for garden.
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

#include <cctype>	/* For std::toupper() */
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "conf_file.h"

//#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

using namespace std;

/* Functions from C++11 that are manually implemented
int stoi(string MyString)
{
	istringstream converter(MyString);
	int result;
	converter >> result;
	return result;
}

string to_string(int MyInt)
{
	ostringstream converter;
	converter << MyInt;
	return converter.str();
}
*/

conf_file::conf_file(string file_path) : conf_name(file_path)
{
	/* Set defaults here */
	x10_number = 0;
	ph_pin = -1;
	nutrient_pin = -1;
	level_pin = -1;

	ifstream MyConf(conf_name.c_str() );
	if(MyConf.fail() )
		throw string("Failed to open configuration file.");

	vector<string> ConfCopy;	/* Stores a copy of the conf file in ConfCopy */
	char b[256];
	for(int i = 0; !MyConf.eof(); i++)	/* i corresponds to line number */
	{
		if(MyConf.peek() == '\n')
		{
			MyConf.get();
			ConfCopy.push_back("\n");		/* Makes for proper line numbering */
		}
		else
		{	
			MyConf.getline(&b[0], 256);
			ConfCopy.push_back(string(b) );
		}
	}

	MyConf.close();

	string variable;
	string data;
	for(int i = 0; i < ConfCopy.size(); i++)
	{
		istringstream split(ConfCopy[i]);
		if(split.peek() == '\n' || split.peek() == '#' ||
		   split.peek() == ' ' || split.peek() == '\t')
			continue;
		split >> variable;
		split >> data;

		/* Variable comparing */
		if(variable == "")		/* Occurs when the conf file is empty */
			continue;

		/* Starting variable matching */
		else if(variable == "x10dev.number")
		{
			try
			{
				x10_number = stoi(data);
			}
			catch(...)
			{
				throw error_data(i, data);
			}

			for(int k = 0; k < x10_number; k++)	/* Allocate device space */
			{
				x10_devices.push_back(x10dev_conf);
				#ifdef DEBUG
				cout << "Created new x10 device." << k << endl;
				#endif
			}
		}
		else if(variable == "ph.pin")
		{
			try
			{
				ph_pin = stoi(data);
			}
			catch(...)
			{
				throw error_data(i, data);
			}
		}
		else if(variable == "nutrient.pin")
		{
			try
			{
				nutrient_pin = stoi(data);
			}
			catch(...)
			{
				throw error_data(i, data);
			}
		}
		else if(variable == "level.pin")
		{
			try
			{
				level_pin = stoi(data);
			}
			catch(...)
			{
				throw error_data(i, data);
			}
		}

		else if(x10_number > 0)	/* This must be at the end! */
		{
			for(int k = 0; k < x10_number; k++) /* x10dev.* options */
			{
				if(variable == "x10dev" + to_string( (long long int)k) + ".name")
				{
					x10_devices[k].name = data;
				}
				else if(variable == "x10dev" + to_string( (long long int)k) + ".on_time")
				{
					try
					{
						x10_devices[k].on_time = stoi(data);
					}
					catch(...)
					{
						error_data(i, data);
					}
				}
				else if(variable == "x10dev" + to_string( (long long int)k) + ".off_time")
				{
					try
					{
						x10_devices[k].off_time = stoi(data);
					}
					catch(...)
					{
						error_data(i, data);
					}
				}
				else if(variable == "x10dev" + to_string( (long long int)k) + ".address")
				{
					if(data.size() != 2)
						throw error_data(i, data);

					/* Finds the housecode */
					if(toupper(data[0]) >= 'A' && toupper(data[0]) <= 'P')
						x10_devices[k].housecode = toupper(data[0]);
					else
						throw error_data(i, data);

					/* Finds the unit number */
					/* NB! x10 devices really do up to 16, not 9. */
					if(data[1] >= '1' && data[1] <= '9')
					{
						try
						{
							string temp = "";
							temp += data[1];
							x10_devices[k].unit = stoi(temp);
						}
						catch(...)
						{
							error_data(i, data);
						}
					}
					else
						throw error_data(i, data);
				}
			}
		}

		/* Add more variables here */

		else
			throw error_variable(i, variable);
	}
}

/* NB! The cast to "long long int" when using std::to_string() is a workaround.
 *
 * Debian Squeeze's version of libstdc++ must not properly implement
 * C++11 (which the g++ only recognizes as C++0x).
 */

/*
 * Prints an error that signals an unknown variable
 * in the configuration file.
 */
string conf_file::error_variable(int line, string MyVariable)
{
	return string(conf_name + ":" + to_string( (long long int)(line + 1) ) + ": "
	               + "Unknown variable \"" + MyVariable + "\"");
}

/*
 * Similar to conf_file::error_variable(), but it prints
 * a message about incorrect data.
 */
string conf_file::error_data(int line, string MyData)
{
	return string(conf_name + ":" + to_string( (long long int)(line + 1) ) + ": "
	               + "\"" + MyData + "\" " + "is of the incorrect data type");
}

