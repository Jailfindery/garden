/*
 *
 *  Interface class functions for automation components for garden.
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

#include "light.h"
#include "pump.h"
#include "water.h"
#include "interface.h"

Interface::Interface()
{
	MyLight = new Light;
	MyWater = new Water;
	MyPump = new Pump;
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

void Interface::AddReporter(Reporter* NewReporter)
{
	MyReporter = NewReporter;
}

/* Control Members */

void Interface::LightTurnOn()
{
	bool result = MyLight->TurnOn();
	if(result == 0)
	{
		MyReporter->LightOnPass();
	}
	else
	{
		MyReporter->LightOnFail();
	}
}

void Interface::LightTurnOff()
{
	bool result = MyLight->TurnOff();
	if(result == 0)
	{
		MyReporter->LightOffPass();
	}
	else
	{
		MyReporter->LightOffFail();
	}
}

void Interface::PumpTurnOn()
{
	bool result = MyPump->TurnOn();
	if(result == 0)
	{
		MyReporter->PumpOnPass();
	}
	else
	{
		MyReporter->PumpOnFail();
	}
}

void Interface::PumpTurnOff()
{
	bool result = MyPump->TurnOff();
	if(result == 0)
	{
		MyReporter->PumpOffPass();
	}
	else
	{
		MyReporter->PumpOffFail();
	}
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

