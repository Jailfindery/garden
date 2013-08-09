/*
 *
 *  Scheduler class for timed tasks for garden.
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

//#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

#include <vector>

#include "clock.h"
#include "interface.h"
#include "scheduler.h"

Scheduler::Scheduler()
{
	CurrentTime = GetDayTime();
	PreviousTime = (CurrentTime - 1);
}

/* Cycles through the list of
 * X10 devices and checks whether
 * they should be on or not.
 */
/* TODO: Make this system more
 * robust by thinking of "states"
 * rather than "changes."
 */
void Scheduler::check_x10dev()
{
	vector<x10dev_info>::iterator iter = x10dev_list.begin();
	for(; iter < x10dev_list.end(); iter++)
	{
		if(iter->on_time > PreviousTime && iter->on_time < CurrentTime)
			MyInterface->On(iter->index);
		else if(iter->off_time > PreviousTime && iter->off_time < CurrentTime)
			MyInterface->Off(iter->index);
	}
	return;
}

void Scheduler::refresh_time()
{
	PreviousTime = CurrentTime;
	CurrentTime = GetDayTime();

	#ifdef DEBUG
		cout << "Scheduler: Time refresh: [ " << CurrentTime << " ]" << endl;
		cout << "\t PreviousTime = " << PreviousTime << endl;
	#endif
}

