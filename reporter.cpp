/*
 *
 *  Reporter class functions for logging events for garden.
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

#include <fstream>
#include <string>

#include "bounds.h"
#include "clock.h"
#include "conversion.h"
#include "interface.h"
#include "reporter.h"

using namespace std;

/* NB! 0 means daemon, 1 means manual. */

class Interface;

Reporter::Reporter(string log_path, Interface* MyInterface)
{
	log_file = log_path;		/* The acutal log file will be opened only when
								 * a message is written to it.
								 */
	MyInterface->AddReporter(this);
}

int Reporter::SendNotify(string Message)
{
	string Report = GetReadableTime() + " " + Message;
	ofstream MyLog(log_path.c_str() )
	if(MyLog.fail() )
		return -1;
	MyLog << Report << endl;
	return 0;
}

void Reporter::LightOnPass()
{
	string Notice = "light: turned on";
	SendNotify(Notice);
	return;
}

void Reporter::LightOnFail()
{
	string Notice = "light: activation failure";
	SendNotify(Notice);
	return;
}

void Reporter::LightOffPass()
{
	string Notice = "light: turned off";
	SendNotify(Notice);
	return;
}

void Reporter::LightOffFail()
{
	string Notice = "light: deactivation failure";
	SendNotify(Notice);
	return;
}

void Reporter::PumpOnPass()
{
	string Notice = "pump: turned on";
	SendNotify(Notice);
	return;
}

void Reporter::PumpOnFail()
{
	string Notice = "pump: activation failure";
	SendNotify(Notice);
	return;
}

void Reporter::PumpOffPass()
{
	string Notice = "pump: turned off";
	SendNotify(Notice);
	return;
}

void Reporter::PumpOffFail()
{
	string Notice = "pump: deactivation failure";
	SendNotify(Notice);
	return;
}

void Reporter::RefreshpH(int NewpH)
{
	string pHString = IntToString(NewpH);
	string Notice;

	if(NewpH >= 6 && NewpH <= 8)
	{
		Notice = "pH: refreshed at " + pHString;
	}
	else if(NewpH < 6)
	{
		Notice = "pH: acidic at " + pHString;
	}
	else
	{
		Notice = "pH: basic at " + pHString;
	}
	SendNotify(Notice);
	return;
}

void Reporter::RefreshNutrient(int NewNutrient)
{
	string NutrientString = IntToString(NewNutrient);
	string Notice;

	if(NewNutrient >= NutrientLower && NewNutrient <= NutrientUpper)
	{
		Notice = "nutrient: normal at " + NutrientString;
	}
	else if(NewNutrient < NutrientLower)
	{
		Notice = "nutrient: low at " + NutrientString;
	}
	else
	{
		Notice = "nutrient: high at " + NutrientString;
	}
	SendNotify(Notice);
	return;
}

void Reporter::RefreshLevel(int NewLevel)
{
	string LevelString = IntToString(NewLevel);
	string Notice;

	if(NewLevel >= LevelLower)
	{
		Notice = "water: refreshed at " + LevelString;
	}
	else
	{
		Notice = "water: low at " + LevelString;
	}
	SendNotify(Notice);
	return;
}

