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

#include <iostream>
#include <unistd.h>
#include "reporter.h"
#include "interface.h"
#include "commander.h"
#include "scheduler.h"

// Program quality state
#define DEBUG

/* Program Version */
string version = "20121109";

using namespace std;

void ParamError()
{
	cout << "Invalid argument" << endl;
	cout << "Usage: garden [options]" << endl;
	cout << "  Options:" << endl;
	cout << "  -d, --daemon		Runs program in daemon mode" << endl;
	cout << "  -m, --manual		Runs program in manual mode" << endl;
	cout << "  --version		Prints version information" << endl;
	cout << "  --help		Prints help message" << endl;
}

int main(int argc, char *argv[])
{
	bool RunMode;		// 0 = daemon, 1 = manual

	int LogMode = 0;	/* 0 = Whatever RunMode says, 1 = force logging,
						   2 = force to stdout							 */

	/* Parameter Processing */

	if(argc != 2) 
	{
		ParamError();
		return 1;
	}

	for(int i = 1; i < argc; i++)
	{
		if(argv[i][0] == '-')	// Make sure parameter is valid.
		{
			if(argv[i][1] == '-')	// Parameter is in long-form.
			{
				string Parameter;
				for(int k = 0; argv[i][k] != '\0'; k++)  // Read argv[i] into a string
				{
					Parameter += argv[i][k];
				}

				if(Parameter == "--daemon")
				{
					RunMode = 0;
					#ifdef DEBUG
						cout << "Run mode set to daemon." << endl;
					#endif
				}
				else if(Parameter == "--manual")
				{
					RunMode = 1;
					#ifdef DEBUG
						cout << "Run mode set to manual." << endl;
					#endif
				}
				else if(Parameter == "--force-log")
				{
					LogMode = 1;
				}
				else if(Parameter == "--force-output")
				{
					LogMode = 2;
				}

			/* Add more long-form
			   options here.	 */

				else if(Parameter == "--version")
				{
					cout << "garden " << version << endl;
					cout << "Copyright (C) 2012 Joshua Schell" << endl;
					cout << "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>" << endl;
					cout << "This is free software: you are free to change and redistribute it." << endl;
					cout << "There is NO WARRANTY, to the extent permitted by law." << endl;
					cout << endl;
					cout << "Report bugs at: <https://github.com/Jailfindery/garden/issues>" << endl;
					cout << "garden homepage: <https://github.com/Jailfindery/garden>" << endl;
					cout << "DotSlashGarden Devel Blog: <http://dotslashgarden.blogspot.ca>" << endl;
					return 0;
				}
				else if(Parameter == "--help")
				{
					cout << "garden " << version << endl;
					cout << "Usage: garden [options]" << endl;
					cout << "  Options:" << endl;
					cout << "  -d, --daemon		Runs program in daemon mode" << endl;
					cout << "  -m, --manual		Runs program in manual mode" << endl;
					cout << "  --version		Prints version information" << endl;
					cout << "  --help		Prints this message" << endl;
					return 0;
				}
				else
				{
					ParamError();
					return 1;
				}
			}
			else if(argv[i][2] == '\0')		// Parameter is in short-form
			{
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
					case 'L':
						LogMode = 1;
						break;
					case 'O':
						LogMode = 2;
						break;

					/* Add more short-form
					   options here.       */

					default:
						ParamError();
						return 1;
						break;
				}
			}
			else
			{
				ParamError();
				return 1;
			}
		}
		else		// Parameter is some random text
		{
			ParamError();
			return 1;
		}
	}


	/* Program Runtime */

	bool PassToReporter;
	if(LogMode = 1)
	{
		PassToReporter = 0;
	}
	else if(LogMode = 2)
	{
		PassToReporter = 1;
	}
	else
	{
		PassToReporter = RunMode;
	}

	if(RunMode == 1)
	{
		Commander* MainCommander = new Commander;
		Interface* MainInterface = MainCommander->GetInterface();
		Reporter* MainReporter = new Reporter(PassToReporter, MainInterface);
		
		bool Continue = 1;
		bool& Active = Continue;
		while(Active)
		{
			MainCommander->MainMenu(Active);	// Runs the main menu.
		}

		delete MainCommander;
		delete MainReporter;
		MainCommander = 0;
		MainReporter = 0;
	}
	else if(RunMode == 0)
	{
		Scheduler* MainScheduler = new Scheduler;
		Interface* MainInterface = MainScheduler->GetInterface();
		Reporter* MainReporter = new Reporter(PassToReporter, MainInterface);
		
		while(true)
		{
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

