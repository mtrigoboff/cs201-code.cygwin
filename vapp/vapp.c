#include <stdio.h>
#include "vehicles.h"

int main()
{
    Vehicle     vehicles[6];
    int         i;
    
	// "constructor" calls
    vehicles[0] = newCar("Ford", 2000);
    vehicles[1] = newCar("Chevy", 3000);
    vehicles[2] = newBoat("8 Ball", BT_SAIL, 0, 25);
    vehicles[3] = newBoat("PT658", BT_POWER, 3, 78);
    vehicles[4] = newPlane("F-117", "Lockheed", 2, 50);
    vehicles[5] = newPlane("B-2", "Northrop-Grumman", 4, 125);

	// function calls that behave polymorphically
    for (i = 0; i < 6; i++) {
        printVehicle(vehicles[i]);
        printSpeed(vehicles[i]);
        printf("\n");
        }

	// "destructor" calls
    for (i = 0; i < 6; i++)
        freeVehicle(vehicles[i]);

    return 0;
}
