#include "plane.h"

using namespace std;

Plane::Plane(char *name, int nEngines, int wingSpan) :
	Vehicle(name, nEngines)
{
	this->wingSpan = wingSpan;
}

Plane::~Plane(void)
{
}

void Plane::print(ostream& out)
{
	Vehicle::print(out);
	out << wingSpan << " feet" << endl;
}

void Plane::printSpeed(ostream& out)
{
	out << 4.5 * wingSpan << " mph" << endl;
}
