/*
 *
 *  Interface class header for garden.
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

#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <vector>

#include "reporter.h"
#include "water.h"
#include "x10dev.h"

//class Reporter;	// Why is this here?

class Interface
{
private:
	Water* MyWater;
	Reporter* MyReporter;
	vector<x10dev*> deviceList;
	void report_x10(int x10_return);
public:
	Interface();
	~Interface();
	void add_Reporter(Reporter* NewReporter);
	void add_x10dev(x10dev* NewDev);
	/* Control Members */
	void x10_on(int i);
	void x10_off(int i);
	void CheckpH();
	void CheckNutrient();
	void CheckLevel();
	void HealthCheck();
};

#endif // INTERFACE_H_INCLUDED

