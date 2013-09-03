#ifndef UDT_CLOCK_H_INCLUDED
#define UDT_CLOCK_H_INCLUDED

#include <chrono>

using namespace std;

/* udt_clock provides clock data similar to Standard Library clocks from
 * <chrono>. This clock uses system_clock as its base and returns time in
 * seconds, but may become a template in the future.
 */

class udt_clock
{
  public:
	using time_point = chrono::time_point<chrono::system_clock, chrono::seconds>;
	static time_point now();
};

#endif /* UDT_CLOCK_H_INCLUDED */

