#include <chrono>

#include "udt_clock.h"

using namespace std;
using namespace std::chrono;

/* Takes the current time and converts it to a duration so that it can
 * be manipulated. The duration is converted to UDT and is then turned
 * back into a time_point, namely a udt_clock::time_point.
 */

udt_clock::time_point udt_clock::now()
{
	system_clock::time_point local_now = system_clock::now();
	seconds local_sec = duration_cast<seconds>(local_now.time_since_epoch() );
	seconds udt_sec = local_sec % 86400;
	return udt_clock::time_point(udt_sec);
}

