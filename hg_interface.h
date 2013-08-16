#ifndef HG_INTERFACE_INCLUDED
#define HG_INTERFACE_INCLUDED

#include <utility>
#include <vector>

using namespace std;

#include "x10dev.h"

class x10dev;	/* Forward referenece to resolve circular dependency */

/* hg_interface is a facade class that creates
 * a consistent interface for the hydrogarden.
 * Currently, it controls:
 *   - X10 Devices
 */
class hg_interface
{
  private:
	vector<x10dev> x10dev_list; 
  public:
	/* Return from x10dev_*() contains an int for general exit status
	 * (0 for success, -1 for failure) and string for a description
	 * of the error.
	 */
	pair<int, string> x10dev_on(int i);
	pair<int, string> x10dev_off(int i);
	void add_x10dev(x10dev _dev) { x10dev_list.push_back(_dev); }
};

#endif /* HG_INTERFACE_INCLUDED */

