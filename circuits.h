/*
 *
 *  Circuit class header for garden.
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

#ifndef CIRCUITS_H_INCLUDED
#define CIRCUITS_H_INCLUDED

#include "pins.h"

class CircuitpH
{
	friend class Water;

private:
	int PinIn;
	int PinOut;

protected:
	CircuitpH() : PinIn(PinpHIn), PinOut(PinpHOut) {}
	int Activate();
};

class CircuitNutrient
{
	friend class Water;

private:
	int PinIn;
	int PinOut;

protected:
	CircuitNutrient() : PinIn(PinNutrientIn), PinOut(PinNutrientOut) {}
	int Activate();
};

class CircuitLevel
{
	friend class Water;

private:
	int PinIn;
	int PinOut;

protected:
	CircuitLevel() : PinIn(PinLevelIn), PinOut(PinLevelOut) {}
	int Activate();
};

#endif // CIRCUITS_H_INCLUDED

