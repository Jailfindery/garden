#include <string>
#include <utility>
#include <vector>

#include "hg_interface.h"
#include "x10dev.h"

using namespace std;

pair<int, string> hg_interface::x10dev_on(int i)
{
	/* First, check if it is already on */
	if(x10dev_list[i].status)
		return make_pair(1, x10dev_list[i].name + ": Already active");
	int result = x10dev_list[i].on();
	if(result)
		return make_pair(1, x10dev_list[i].name + ": Activation failed");
	return make_pair(0, x10dev_list[i].name + ": Activated successfully");
}

pair<int, string> hg_interface::x10dev_off(int i)
{
	/* First, check if it is already off */
	if(!x10dev_list[i].status)
		return make_pair(1, x10dev_list[i].name + ": Already inactive");
	int result = x10dev_list[i].off();
	if(result)
		return make_pair(1, x10dev_list[i].name + ": Deactivation failed");
	return make_pair(0, x10dev_list[i].name + ": Deactived successfully");
}

