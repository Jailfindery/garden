/*
 *
 *  Menu functions for manual control for garden.
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
#include "conversion.h"
#include "interface.h"
#include "commander.h"

using namespace std;

Commander::Commander()
{
	MyInterface = new Interface;
}

Commander::~Commander()
{
	delete MyInterface;
	MyInterface = 0;
}

void Commander::MenuLight()
{
	string response;

	cout << endl;
	cout << "*****************************************" << endl;
	cout << "*** Light                             ***" << endl;
	cout << "*****************************************" << endl;
	cout << "* 1: Turn On                          ***" << endl;
	cout << "* 2: Turn Off                         ***" << endl;
	cout << "* 3: Return to Devices                ***" << endl;
	cout << "*****************************************" << endl << endl;
	
	cout << "Please select an action: ";
	cin >> response;
	cout << endl;

	int MenuNumber = StringToInt(response);
	switch(MenuNumber)
	{
	case 1:
		MyInterface->LightTurnOn();
		break;
	case 2:
		MyInterface->LightTurnOff();
		break;
	case 3:
		break;
	default:
		cout << "That is an invalid integer." << endl << endl;
		MenuLight();
		break;
	}
}

void Commander::MenuPump()
{
	string response;

	cout << endl;
	cout << "*****************************************" << endl;
	cout << "*** Pump                              ***" << endl;
	cout << "*****************************************" << endl;
	cout << "* 1: Turn On                          ***" << endl;
	cout << "* 2: Turn Off                         ***" << endl;
	cout << "* 3: Return to Devices                ***" << endl;
	cout << "*****************************************" << endl << endl;

	cout << "Please select an action: ";
	cin >> response;
	cout << endl;

	int MenuNumber = StringToInt(response);
	switch(MenuNumber)
	{
	case 1:
		MyInterface->PumpTurnOn();
		break;
	case 2:
		MyInterface->PumpTurnOff();
		break;
	case 3:
		break;
	default:
		cout << "That is not a valid integer." << endl << endl;
		MenuPump();
		break;
	}
		
}

void Commander::MenuWater()
{
	string response;
	
	cout << endl;
	cout << "*****************************************" << endl;
	cout << "*** Water Circuits                    ***" << endl;
	cout << "*****************************************" << endl;
	cout << "* 1: Refresh pH                       ***" << endl;
	cout << "* 2: Refresh Nutrient Level           ***" << endl;
	cout << "* 3: Refresh Water Level              ***" << endl;
	cout << "* 4: Return to Devices                ***" << endl;
	cout << "*****************************************" << endl << endl;

	cout << "Please select an action: ";
	cin >> response;
	cout << endl;

	int MenuNumber = StringToInt(response);
	switch(MenuNumber)
	{
	case 1:
		MyInterface->CheckpH();
		break;
	case 2:
		MyInterface->CheckNutrient();
		break;
	case 3:
		MyInterface->CheckLevel();
		break;
	case 4:
		break;
	default:
		cout << "That is an invalid integer." << endl << endl;
		MenuWater();
		break;
	}
	
}

void Commander::MainMenu(bool& Active)
{
	string response;

	cout << endl;
	cout << "*****************************************" << endl;
	cout << "*** Main Menu                         ***" << endl;
	cout << "*****************************************" << endl;
	cout << "* 1: Light                            ***" << endl;
	cout << "* 2: Pump                             ***" << endl;
	cout << "* 3: Water Circuits                   ***" << endl;
	cout << "* 4: Quit                             ***" << endl;
	cout << "*****************************************" << endl << endl;

	cout << "Please select an option: ";
	cin >> response;
	cout << endl;

	int MenuNumber = StringToInt(response);
	switch(MenuNumber)
	{
	case 1:
		MenuLight();
		break;
	case 2:
		MenuPump();
		break;
	case 3:
		MenuWater();
		break;
	case 4:
		Active = 0;
		break;
	default:
		cout << "That is an invalid integer." << endl << endl;
		break;
	}
}

