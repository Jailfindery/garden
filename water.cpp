/*
 *
 *  Water class functions for water related things for garden.
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

#include "circuits.h"
#include "water.h"

Water::Water()
{
	/* Configure Circuits */
	pH = new CircuitpH;
	Nutrient = new CircuitNutrient;
	Level = new CircuitLevel;
}

Water::~Water()
{
	/* Delete Circuits */
	delete pH;
	delete Nutrient;
	delete Level;
	pH = 0;
	Nutrient = 0;
	Level = 0;
}

int Water::GetpH()
{
	int result = pH->Activate();
	return result;
}

int Water::GetNutrient()
{
	int result = Nutrient->Activate();
	return result;
}

int Water::GetLevel()
{
	int result = Level->Activate();
	return result;
}

