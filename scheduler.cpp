/*
 *
 *  Scheduler class for timed tasks for garden.
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

//#define DEBUG

#include <iostream>
#include "daemon.h"
#include "clock.h"
#include "interface.h"
#include "scheduler.h"

Scheduler::Scheduler()
{
	MyInterface = new Interface;
	CurrentTime = GetDayTime();

	LightOnTime = TimeLightOn;
	LightOffTime = TimeLightOff;
	PumpOnTime = TimePumpOn;
	PumpOffTime = TimePumpOff;
	HealthCheckFreq = HealthFrequency;
}

Scheduler::~Scheduler()
{
	delete MyInterface;
	MyInterface = 0;
}

void Scheduler::InterpretTime()
{
	PreviousTime = CurrentTime;
	CurrentTime = GetDayTime();

	#ifdef DEBUG
		cout << "Scheduler: [ " << CurrentTime << " ] - Checking tasks " << endl;
		cout << "\t PreviousTime = " << PreviousTime << endl;
	#endif
		
	
	/* Turn On/Off Tasks */

	if(LightOnTime > PreviousTime && LightOnTime <= CurrentTime)
	{
		MyInterface->LightTurnOn();
	}
	if(LightOffTime > PreviousTime && LightOffTime <= CurrentTime)
	{
		MyInterface->LightTurnOff();
	}
	if(PumpOnTime > PreviousTime && PumpOnTime <= CurrentTime)
	{
		MyInterface->PumpTurnOn();
	}
	if(PumpOffTime > PreviousTime && PumpOffTime <= CurrentTime)
	{
		MyInterface->PumpTurnOff();
	}
	
	/* HealthCheck Check */
	
	int PreModTime = PreviousTime % HealthCheckFreq;
	int CurModTime = CurrentTime % HealthCheckFreq;
	
	if(CurModTime != PreModTime)
	{
		if(CurModTime < PreModTime)
		{
			MyInterface->HealthCheck();
		}
	}
	else if(CurModTime == 0)
	{
		MyInterface->HealthCheck();
	}
}

