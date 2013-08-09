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

class Circuit
{
protected:
	int PinIn;
	int PinOut;
	virtual int Activate() = 0;
};

class CircuitpH : public Circuit
{
friend class Water;

protected:
	CircuitpH();
	int Activate();
};

class CircuitNutrient : public Circuit
{
friend class Water;

protected:
	CircuitNutrient();
	int Activate();
};

class CircuitLevel : public Circuit
{
friend class Water;

protected:
	CircuitLevel();
	int Activate();
};

#endif // CIRCUITS_H_INCLUDED

