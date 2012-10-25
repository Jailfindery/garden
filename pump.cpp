/*
 *
 *  Aeration pump class functions for garden.
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

#define DEBUG

#ifdef DEBUG
#include <iostream>
#include "colours.h"
#endif
#include "pump.h"

Pump::Pump()
{
	Status = 0;
}

Pump::~Pump()
{
	if(Status == 1) {
		TurnOff();
	}
}

bool Pump::TurnOn()
{
	#ifdef DEBUG
		cout << "Turning pump on... ";
	#endif
	if(Status == 0)
	{
		/* Code that will activate the pump */

		#ifdef DEBUG
			cout << "done." << endl;
		#endif

		Status = 1;
		return 0;
	}
	#ifdef DEBUG
		cout << error() << "failed!" << def_colour() << endl;
	#endif
	return 1;
}

bool Pump::TurnOff()
{
	#ifdef DEBUG
		cout << "Turning pump off... ";
	#endif
	if(Status == 1)
	{
		/* Code that will deactivate the pump */

		#ifdef DEBUG
			cout << "done." << endl;
		#endif

		Status = 0;
		return 0;
	}
	#ifdef DEBUG
		cout << error() << "failed!" << def_colour() << endl;
	#endif
	return 1;
}

