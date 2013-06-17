#include <iostream>
#include <unistd.h>

#define X10DEV_TESTING

#include "x10dev.h"

using namespace std;

int main()
{
	cout << "Opening Firecracker module... ";
	cout.flush();
	if(x10dev::open_device("/dev/ttyUSB0") < 3)		/* Do not open stdout! */
	{
		cerr << "failed!" << endl;
		cerr << "E: Unable to open Firecracker module." << endl;
		return -1;
	}
	cout << "done." << endl;

	x10dev* MyDev = new x10dev('A', 2, "pump");

	cout << "Waiting 10 seconds... ";
	cout.flush();
	sleep(10);
	cout << "done." << endl;

	cout << "Activating X10 device... ";
	cout.flush();
	if(MyDev->on() != 0)
		cerr << "failed!" << endl;
	else
		cout << "done." << endl;

	cout << "Pausing... ";
	cout.flush();
	sleep(3);
	cout << "done." << endl;

	cout << "Deactivating X10 device... ";
	cout.flush();
	if(MyDev->off() != 0)
		cerr << "failed!" << endl;
	else
		cout << "done." << endl;

	delete MyDev;
	MyDev = 0;
	x10dev::close_device();
	return 0;
}
