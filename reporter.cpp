/*
 *
 *  Reporter class functions for logging events for garden.
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

#include <iostream>
#include "bounds.h"
#include "clock.h"
#include "conversion.h"
#include "interface.h"
#include "reporter.h"

using namespace std;

/* NB! 0 means daemon, 1 means manual. */

class Interface;

Reporter::Reporter(bool ProgramMode, Interface* MyInterface)
{
	RunMode = ProgramMode;

	MyInterface->AddReporter(this);
}

void Reporter::SendNotify(string Message)
{
	string TimeNow = GetReadableTime();
	string Report = TimeNow + " " + Message;

	/*if(RunMode == 0)
	{			Remove comment blocks when writing
	}			to logs is figured out.
	else*/
	{
		cout << Report << endl;
	}
}

void Reporter::LightOnPass()
{
	string Notice = "light: turned on";
	SendNotify(Notice);
}

void Reporter::LightOnFail()
{
	string Notice = "light: activation failure";
	SendNotify(Notice);
}

void Reporter::LightOffPass()
{
	string Notice = "light: turned off";
	SendNotify(Notice);
}

void Reporter::LightOffFail()
{
	string Notice = "light: deactivation failure";
	SendNotify(Notice);
}

void Reporter::PumpOnPass()
{
	string Notice = "pump: turned on";
	SendNotify(Notice);
}

void Reporter::PumpOnFail()
{
	string Notice = "pump: activation failure";
	SendNotify(Notice);
}

void Reporter::PumpOffPass()
{
	string Notice = "pump: turned off";
	SendNotify(Notice);
}

void Reporter::PumpOffFail()
{
	string Notice = "pump: deactivation failure";
	SendNotify(Notice);
}

void Reporter::RefreshpH(int NewpH)
{
	string pHString = IntToString(NewpH);
	string Notice;

	if(NewpH >= 6 && NewpH <= 8)
	{
		Notice = "pH: Refreshed at " + pHString;
	}
	else if(NewpH < 6)
	{
		Notice = "pH: Acidic at " + pHString;
	}
	else
	{
		Notice = "pH: Basic at " + pHString;
	}
	SendNotify(Notice);
}

void Reporter::RefreshNutrient(int NewNutrient)
{
	string NutrientString = IntToString(NewNutrient);
	string Notice;

	if(NewNutrient >= NutrientLower && NewNutrient <= NutrientUpper)
	{
		Notice = "Nutrient: Refreshed at " + NutrientString;
	}
	else if(NewNutrient < NutrientLower)
	{
		Notice = "Nutrient: Low at " + NutrientString;
	}
	else
	{
		Notice = "Nutrient: High at " + NutrientString;
	}
	SendNotify(Notice);
}

void Reporter::RefreshLevel(int NewLevel)
{
	string LevelString = IntToString(NewLevel);
	string Notice;

	if(NewLevel >= LevelLower)
	{
		Notice = "Water: Refreshed at " + LevelString;
	}
	else
	{
		Notice = "Water: Low at " + LevelString;
	}
	SendNotify(Notice);
}

