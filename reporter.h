/*
 *
 *  Reporter class header for garden.
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

#ifndef REPORTER_H_INCLUDED
#define REPORTER_H_INCLUDED

#include <iostream>
#include "interface.h"

using namespace std;

class Interface;

class Reporter
{
	friend class Interface;

private:
	bool RunMode;
	void SendNotify(string Message);
	
protected:
	/* Message Types - Add more situations here. */
	void LightOnPass();
	void LightOnFail();
	void LightOffPass();
	void LightOffFail();
	void PumpOnPass();
	void PumpOnFail();
	void PumpOffPass();
	void PumpOffFail();
	void RefreshpH(int NewpH);
	void RefreshNutrient(int NewNutrient);
	void RefreshLevel(int NewLevel);

public:
	Reporter(bool ProgramMode, Interface* MyInterface);
};

#endif //REPORTER_H_INCLUDED

