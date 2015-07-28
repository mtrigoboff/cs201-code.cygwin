#include "boat.h"
#include <math.h>
#include <iomanip>

using namespace std;

Boat::Boat(char *name, BoatType type, int nEngines, int length) :
	Vehicle(name, nEngines),
	length(length),
	type(type)
{
}

Boat::~Boat(void)
{
}

void Boat::print(std::ostream& out)
{
	Vehicle::print(out);
	out << (type == sail ? "sail" : type == power ? "power" : "amphibian") << endl
		<< length << " feet" << endl;
}

void Boat::printSpeed(ostream& out)
{
	out << setprecision(3) << 1.34 * sqrt((float) length) << " knots" << endl;
}
