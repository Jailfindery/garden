/*
 *
 *  CM17A (X10 Firecracker) implementation class functions for garden.
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

#include <cctype>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <unistd.h>

extern "C" {
#include "br/br_cmd.h"
}

#include "x10dev.h"

using namespace std;

int x10dev::device = -1;	/* Allocate storage for static members */

x10dev::x10dev(char house, int unit, string new_name)
{
	/** Calculate address */
	house = toupper(house);	/* Ensures it is upper case */

	unsigned char housetemp;
	unsigned char unittemp;

	switch(house)
	{
	case 'A':	housetemp = 0x00;
				break;
	case 'B':	housetemp = 0x10;
				break;
	case 'C':	housetemp = 0x20;
				break;
	case 'D':	housetemp = 0x30;
				break;
	case 'E':	housetemp = 0x40;
				break;
	case 'F':	housetemp = 0x50;
				break;
	case 'G':	housetemp = 0x60;
				break;
	case 'H':	housetemp = 0x70;
				break;
	case 'I':	housetemp = 0x80;
				break;
	case 'J':	housetemp = 0x90;
				break;
	case 'K':	housetemp = 0xa0;
				break;
	case 'L':	housetemp = 0xb0;
				break;
	case 'M':	housetemp = 0xc0;
				break;
	case 'N':	housetemp = 0xd0;
				break;
	case 'O':	housetemp = 0xe0;
				break;
	case 'P':	housetemp = 0xf0;
				break;
	default:	throw string("Not a valid housecode [A-P]");
				break;
	}

	switch(unit)
	{
	case 1:		unittemp = 0x00;
				break;
	case 2:		unittemp = 0x01;
				break;
	case 3:		unittemp = 0x02;
				break;
	case 4:		unittemp = 0x03;
				break;
	case 5:		unittemp = 0x04;
				break;
	case 6:		unittemp = 0x05;
				break;
	case 7:		unittemp = 0x06;
				break;
	case 8:		unittemp = 0x07;
				break;
	case 9:		unittemp = 0x08;
				break;
	case 10:	unittemp = 0x09;
				break;
	case 11:	unittemp = 0x0a;
				break;
	case 12:	unittemp = 0x0b;
				break;
	case 13:	unittemp = 0x0c;
				break;
	case 14:	unittemp = 0x0d;
				break;
	case 15:	unittemp = 0x0e;
				break;
	case 16:	unittemp = 0x0f;
				break;
	default:	throw string("Not a valid unit [1-16]");
				break;
	}

	address = housetemp | unittemp;

	/** Set device name */
	name = new_name;

	off();	/* Make sure it is off before using */
}

x10dev::~x10dev()
{
	off();
}

int x10dev::open_device(string path)
{
	/* Paranoid workaround */
	while(device = open("/dev/null", 0, 0) < 3)
		if(device < 0) return -1;
	close(device);
	device = open(path.c_str(), O_RDONLY | O_NONBLOCK);
	return device;
}

void x10dev::close_device()
{
	close(device);
}

/*
 * Commands for br are:
 *  0 - on
 *  1 - off
 *
 * See br_cmd.h for more details
 *
 */

int x10dev::on()
{
	if(status)		/* Check if it is on already */
		return 1;
	if(br_cmd(device, address, 0) < 0)
		return -1;
	status = 1;
	return 0;
}

int x10dev::off()
{
	if(!status)		/* Check if it is off already */
		return 1;
	if(br_cmd(device, address, 1) < 0)
		return -1;
	status = 0;
	return 0;
}

string x10dev::get_name()
{
	return name;
}
