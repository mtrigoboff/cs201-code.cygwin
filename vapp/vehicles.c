#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "vehicles.h"
#include "vehicles_priv.h"

// private functions

// the Vehicle "constructor"
static VPtr newVehicle(VehicleType type, char *name, int nEngines)
{
    VPtr    v = (VPtr) malloc(sizeof(VehiclePrivate));
    
    v->type = type;
    strncpy(v->name, name, sizeof(v->name));    // strncpy won't overwrite end of array
    v->nEngines = nEngines;
    return v;
}

// the printNEngines implementation for Vehicle
static void printNEngines(VPtr v)
{
    printf("nEngines:     %d\n", ((VPtr) v)->nEngines);
}

void printType(VPtr v)
{
    switch (v->type) {
        case VT_CAR:
			printf("CAR:\n");
            break;
        case VT_BOAT:
			printf("BOAT:\n");
            break;
        case VT_PLANE:
			printf("PLANE:\n");
            break;
        default:
            printf("UNKNOWN_VEHICLE_TYPE:\n");
            break;
        }
}

// for printSpeed, demonstrate simulated virtual function pointer table

typedef void (*PrintSpeedFn)(VPtr v);

static void printCarSpeed(VPtr v)
{
    printf("speed:        %.2f mph\n",
		   ((double) 200000) / v->vtsd.car.weight);
}

static void printBoatSpeed(VPtr v)
{
    printf("speed:        %.2f knots\n",
		   1.34 * sqrt(v->vtsd.boat.length));
}

static void printPlaneSpeed(VPtr v)
{
    printf("speed:        %.2f mph\n",
		   20 * ((double) v->vtsd.plane.wingspan) / v->nEngines);
}

static PrintSpeedFn	printSpeedFns[] =
						{printCarSpeed, printBoatSpeed, printPlaneSpeed};

// public functions

// the Car "constructor"
Vehicle newCar(char *name, int weight)
{
	// calls "superclass constructor"
    VPtr    v = newVehicle(VT_CAR, name, 1);     // car always has 1 engine

    v->vtsd.car.weight = weight;
    return (Vehicle) v;
}

// the Boat "constructor"
Vehicle newBoat(char *name, BoatType type, int nEngines, int length)
{
	// calls "superclass constructor"
    VPtr    v = newVehicle(VT_BOAT, name, nEngines);

    v->vtsd.boat.type = type;
    v->vtsd.boat.length = length;
    return (Vehicle) v;
}

// the Plane "constructor"
Vehicle newPlane(char *name, char *manufacturer, int nEngines, int wingspan)
{
	// calls "superclass constructor"
    VPtr    v = newVehicle(VT_PLANE, name, nEngines);
	size_t	nBytes = strlen(manufacturer) + 1;

    v->vtsd.plane.wingspan = wingspan;
	v->vtsd.plane.manufacturerName = malloc(nBytes);
	strncpy(v->vtsd.plane.manufacturerName, manufacturer, nBytes);
    return (Vehicle) v;
}


// print information about a vehicle -- information depends on vehicle type
void printVehicle(Vehicle v)
{
	VPtr	vp = (VPtr)	v;

	printType(v);
	printf("name:         %s\n", vp->name);
    switch (vp->type) {
        case VT_CAR:
            printf("weight:       %d\n", vp->vtsd.car.weight);
            break;
        case VT_BOAT:
            printNEngines(vp);
			printf("type:         %s\n", vp->vtsd.boat.type == BT_SAIL ?  "sail" :
										 vp->vtsd.boat.type == BT_POWER ? "power" :
																		  "amphibian");
            printf("length:       %d\n", vp->vtsd.boat.length);
            break;
        case VT_PLANE:
            printNEngines(vp);
            printf("manufacturer: %s\n", vp->vtsd.plane.manufacturerName);
            printf("wingspan:     %d\n", vp->vtsd.plane.wingspan);
            break;
        default:
            printf("unknown vehicle type\n");
            break;
        }
}

// calculate and print speed of a vehicle, depending on vehicle type
void printSpeed(Vehicle v)
{
	VehicleType		vType = ((VPtr) v)->type;

	if (vType < 0 || vType >= N_VEHICLE_TYPES) {
		printf("----> bad vehicle type: %d!\n", vType);
		return;
		}
	(*printSpeedFns[vType])((VPtr) v);
}

// "destructor" for vehicle instances
void freeVehicle(Vehicle v)
{
    switch (((VPtr) v)->type) {
        case VT_PLANE:
            free(((VPtr) v)->vtsd.plane.manufacturerName);
            break;
		default:
			break;
        }
    free(v);
}
