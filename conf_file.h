#ifndef CONF_FILE_H_INCLUDED
#define CONF_FILE_H_INCLUDED

#include <string>
#include <vector>

using namespace std;

struct x10dev
{
	string name;
	int on_time;
	int off_time;
	char housecode;
	int unit;

	x10dev()	/* Sets defaults */
	{
		name = "unknown";
		on_time = -1;
		off_time = -1;
		housecode = '\0';
		unit = -1;
	}
};

class conf_file
{
 private:
	string conf_name;
	string error_variable(int line, string MyVariable);
	string error_data(int line, string data);
 public:
	conf_file(string file_path);

	/* Add configuration variables here */
	int x10_number;
	vector<x10dev*> x10_devices;
	int ph_pin;
	int nutrient_pin;
	int level_pin;
};

#endif /* CONF_FILE_H_INCLUDED */

