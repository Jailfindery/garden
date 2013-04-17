/*
 *
 *  Scheduler class header for garden.
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

#ifndef SCHEDULER_H_INCLUDED
#define SCHEDULER_H_INCLUDED

#include <vector>

#include "interface.h"

/* TODO: Add compatiblity for circuit
 *       classes.
 */

class Scheduler
{
private:
	int CurrentTime;
	int PreviousTime;
	Interface* MyInterface;
	vector<x10dev_info>* x10dev_list;

public:
	Scheduler();
	void add_Interface(Interface* NewInterface) : MyInterface(NewInterface);
	void add_x10dev_list(vector<x10dev_info>* MyList) : x10dev_list(MyList);
	void check_x10dev();
	void refresh_time();
};

#endif //SCHEDULER_H_INCLUDED

