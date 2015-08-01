#include <iostream>
#include "car.h"
#include "boat.h"
#include "plane.h"

using namespace std;

int main (void)
{
	Vehicle		*vehicles[6];
	int			i;
	
	vehicles[0] = new Car((char*) "Ford", 2000);
	vehicles[1] = new Car((char*) "Chevy", 3000);
	vehicles[2] = new Boat((char*) "Pinta", BoatType::sail, 0, 60);
	vehicles[3] = new Boat((char*) "PT658", BoatType::power, 3, 70);
	vehicles[4] = new Plane((char*) "Boeing", 4, 150);
	vehicles[5] = new Plane((char*) "Cessna", 1, 35);

	for (i = 0; i < 6; i++) {
		vehicles[i]->print(cout);
		vehicles[i]->printSpeed(cout);
		cout << endl;
		}

	for (i = 0; i < 6; i++)
		delete vehicles[i];
	
	return 0;
}
