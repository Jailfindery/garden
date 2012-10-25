/*
 *
 *  Time functions for getting and formatting current time for garden.
 *  Copyright (C) 2012 Joshua Schell (joshua.g.schell@gmail.com)
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

#include <time.h>
#include "conversion.h"

using namespace std;

int GetDayTime()
{
	time_t now;
	time(&now);
	int Current = now % 86400;	// Should yield the time of day in seconds.
	return Current;
}

string GetReadableTime()	// [ HH:MM:SS - XXXXX ], where X is unix day time.
{
	string result;
	int Current = GetDayTime();

	/* Hour */
	int Hour = Current / 3600;
	if(Hour == 24)
	{
		Hour = 0;
	}

	/* Minute */
	int Minute = Current % 3600;
	Minute /= 60;
	
	/* Second */
	int Second = Current % 60;

	/* All together now... */
	result += "[ ";

	if(Hour <= 9)
	{
		result += "0";
	}
	result += IntToString(Hour);

	result += ":";

	if(Minute <= 9)
	{
		result += "0";
	}
	result += IntToString(Minute);

	result += ":";

	if(Second <= 9)
	{
		result += "0";
	}
	result += IntToString(Second);

	result += " - ";
	result += IntToString(Current);
	result += " ]";

	return result;
}

