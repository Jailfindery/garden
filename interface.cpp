/*
 *
 *  Interface class functions for automation components for garden.
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

#include "water.h"
#include "interface.h"
#include "x10dev.h"

Interface::Interface()
{
	MyWater = new Water;
}

Interface::~Interface()
{
	delete MyLight;
	delete MyWater;
	delete MyPump;
	MyLight = 0;
	MyWater = 0;
	MyPump = 0;
}

void Interface::set_log(log_file* new_log)
{
	MyLog = new_log;
}

void Interface::add_x10dev(x10dev* NewDev)
{
	devicelist.push_back(NewDev);
}

void Interface::x10_on(int i)
{
	report_x10(deviceList[i]->On() );
	return;
}
void Interface::x10_off(int i)
{
	report_x10(deviceList[i]->Off() );
	return;
}

/* TODO: Fills in blanks with
 *       log_file methods.
 */
void Interface::report_x10(int x10_return)
{
	if(result == 0)
	{
		/* It worked */
	}
	else if(result > 0)
	{
		/* Nothing changed */
	}
	else
	{
		/* It failed */
	}
	return;
}

void Interface::CheckpH()
{
	int pHLevel = MyWater->GetpH();
	MyReporter->RefreshpH(pHLevel);
}

void Interface::CheckNutrient()
{
	int NutrientLevel = MyWater->GetNutrient();
	MyReporter->RefreshNutrient(NutrientLevel);
}

void Interface::CheckLevel()
{
	int WaterLevel = MyWater->GetLevel();
	MyReporter->RefreshLevel(WaterLevel);
}

void Interface::HealthCheck()
{
	CheckpH();
	CheckNutrient();
	CheckLevel();
}

