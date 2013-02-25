#ifndef X10DEV_H_INCLUDED
#define X10DEV_H_INCLUDED

#include <string>

using namespace std;

class x10dev
{
private:
	static int device;
	unsigned char address;
	string name;	/* This may need to be eliminated if it has no use... */
	bool status;
protected:
	int on();
	int off();
/*
 * on() and off() members return:
 *
 * -1 when unable to turn on
 * 1 if it is already on, but still successful
 *
 */
public:
	x10dev(char house, int unit, string new_name);
	virtual ~x10dev();
	static int open_device(string path);
	static void close_device();
	string get_name();
};

#endif

