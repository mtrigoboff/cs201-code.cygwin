#include "plane.h"

using namespace std;

Plane::Plane(char *name, int nEngines, int wingSpan) :
	Vehicle(name, nEngines),
	wingSpan(wingSpan)
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
	out << 20 * wingSpan / getNEngines() << " mph" << endl;
}
