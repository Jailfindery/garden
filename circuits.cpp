/*
 *
 *  Electric circuit functions to control attached circuits for garden.
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
#endif
#include "circuits.h"

using namespace std;

/* NB! The code required to actually use the circuits will be added later.
       There isn't a lot here because I haven't made the circuits yet.     */

int CircuitpH::Activate()
{
	#ifdef DEBUG
		cout << "Activating pH circuit... ";
	#endif

	/* Code to activate circuit */
	
	#ifdef DEBUG
		cout << "done." << endl;
	#endif
	return 7;
}

int CircuitNutrient::Activate()
{
	#ifdef DEBUG
		cout << "Activating nutrient circuit... ";
	#endif

	/* Code to activate circuit */

	#ifdef DEBUG
		cout << "done." << endl;
	#endif
	return 5;
}

int CircuitLevel::Activate()
{
	#ifdef DEBUG
		cout << "Activating water level circuit... ";
	#endif

	/* Code to activate circuit */

	#ifdef DEBUG
		cout << "done." << endl;
	#endif
	return 5;
}

