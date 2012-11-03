/*
 *
 *  Light class functions for garden.
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

#include <iostream>
#include "colours.h"
#include "light.h"

using namespace std;

Light::Light()
{
	Status = 0;
}

Light::~Light()
{
	if(Status == 1)
	{
		TurnOff();
	}
}

bool Light::TurnOn()
{
	#ifdef DEBUG
		cout << "Turning light on... ";
	#endif
	if(Status == 0)
	{
		/* Code to activate light */
		
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

bool Light::TurnOff()
{
	#ifdef DEBUG
		cout << "Turning light off... ";
	#endif
	if(Status == 1)
	{
		/* Code to deactivate light */
		
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

