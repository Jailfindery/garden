#include <string>
#include <sstream>

#include "conversion.h"

using namespace std;

string to_string(int MyInt)
{
	ostringstream converter;
	converter << MyInt;
	return converter.str();
}

int StringToInt(string MyStr)
{
	istringstream converter(MyStr);
	int result;
	converter >> result;
	return result;
}

