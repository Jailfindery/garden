/*
 *
 *  CM17A (X10 Firecracker) class implementation for garden.
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

#include <cctype>

#include "x10dev.h"

using namespace std;

x10dev::x10dev(char _housecode, int _unit, string _name, int _on, int _off) :
	unit(_unit), name(_name), on_time(_on), off_time(_off)
{
	housecode = toupper(_housecode);	/* Ensures it is upper case */

	unsigned char housetemp;
	unsigned char unittemp;

	switch(_housecode)
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
	default:	throw invalid_argument('\"' + _housecode + '\"' +
				                       " is not a valid housecode [A-P]");
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
	default:	throw invalid_argument('\"' + _unit + '\"' +
				                       " is not a valid unit [1-16]");
				break;
	}

	address = housetemp | unittemp;
}

