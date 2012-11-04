/*
 *
 *  garden - a control program for DotSlashGarden
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

/* I'm sorry, but I have used multiple types of indenting.  */
/* At the time, I was getting a feel for the different		*/
/* styles, and ended up with a mess. For future reference,	*/
/* I am using the Allman style. I'll fix it later.			*/

#include <iostream>
#include <unistd.h>
#include "reporter.h"
#include "interface.h"
#include "commander.h"
#include "scheduler.h"

// Program quality state
#define DEBUG

/* Program Version */
string version = "20121102";

using namespace std;

void ParamError()
{
	cout << "garden " << version << endl;
	cout << "Usage: garden [options]" << endl;
	cout << "Please refer to the man page for more details." << endl;
}

int main(int argc, char *argv[])
{
	bool RunMode;	// Used in Reporter

	/* Parameter Processing */

	if(argc != 2) {		/* This is a temporary solution to stop    */
		ParamError();	/* invalid parameters. This will need to   */
		return 1;		/* be changed as more parameters are made. */
	}

	for(int i = 1; i < argc; i++) {
		if(argv[i][0] == '-')	// Make sure parameter is valid.
		{
			if(argv[i][1] == '-')
			{			// Parameter is in long-form.
				string Parameter;
				for(int k = 0; argv[i][k] != '\0'; k++) {	// Convert argv[i] to string
					Parameter += argv[i][k];
				}

				if(Parameter == "--daemon") {
					RunMode = 0;
					#ifdef DEBUG
						cout << "Run mode set to daemon." << endl;
					#endif
				}
				else if(Parameter == "--manual") {
					RunMode = 1;
					#ifdef DEBUG
						cout << "Run mode set to manual." << endl;
					#endif
				}

				/* Add more long-form
				   options here.      */

				else {
					ParamError();
					return 1;
				}
			}
			else if(argv[i][2] == '\0')
			{			// Parameter is in short-form.
				switch(argv[i][1]) {
					case 'd':
						RunMode = 0;
						#ifdef DEBUG
							cout << "Run mode set to daemon." << endl;
						#endif
						break;		// TRADITION!
					case 'm':
						RunMode = 1;
						#ifdef DEBUG
							cout << "Run mode set to manual." << endl;
						#endif
						break;

					/* Add more short-form
					   options here.       */

					default:
						ParamError();
						return 1;
						break;
				}
			}
			else {
				ParamError();
				return 1;
			}
		}
		else
		{			// Parameter is some random text.
			ParamError();
			return 1;
		}
	}


	/* Program Runtime */

	if(RunMode == 1) {
		Commander* MainCommander = new Commander;
		Interface* MainInterface = MainCommander->GetInterface();
		Reporter* MainReporter = new Reporter(RunMode, MainInterface);
		
		bool Continue = 1;
		bool& Active = Continue;
		while(Active) {
			MainCommander->MainMenu(Active);	// Runs the main menu.
		}

		delete MainCommander;
		delete MainReporter;
		MainCommander = 0;
		MainReporter = 0;
	}
	else if(RunMode == 0) {
		Scheduler* MainScheduler = new Scheduler;
		Interface* MainInterface = MainScheduler->GetInterface();
		Reporter* MainReporter = new Reporter(RunMode, MainInterface);
		
		while(true) {
			MainScheduler->InterpretTime();	// Checks for tasks to run.
			sleep(5);
		}

		delete MainScheduler;
		delete MainReporter;
		MainScheduler = 0;
		MainReporter = 0;
	}
	return 0;
}

