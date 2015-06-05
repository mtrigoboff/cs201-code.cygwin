#include "boat.h"
#include <math.h>
#include <iomanip>

using namespace std;

Boat::Boat(char *name, int nEngines, int length) :
	Vehicle(name, nEngines)
{
	this->length = length;
}

Boat::~Boat(void)
{
}

void Boat::print(std::ostream& out)
{
	Vehicle::print(out);
	out << length << " feet" << endl;
}

void Boat::printSpeed(ostream& out)
{
	out << setprecision(3) << 1.34 * sqrt((float) length) << " knots" << endl;
}
