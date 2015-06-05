#include <cstring>
#include <ostream>
#include "vehicle.h"

using namespace std;

Vehicle::Vehicle(char *name, int nEngines) :
	nEngines(nEngines)
{
	strncpy(this->name, name, sizeof(this->name));
}

Vehicle::~Vehicle(void)
{
}

void Vehicle::print(std::ostream& out)
{
	out << name << endl
		<< nEngines << (nEngines > 1 ? " engines" : " engine")
		<< endl;
}
