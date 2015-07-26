#ifndef _VEHICLES_
#define _VEHICLES_

// public interface to the Vehicles code

typedef enum {
	BT_POWER, BT_SAIL, BT_AMPHIBIAN, N_BOAT_TYPES
	}
BoatType;

typedef void* Vehicle;

// function prototypes

// "constructors"
Vehicle     newCar			(char *name, int weight);
Vehicle     newBoat			(char *name, BoatType type, int nEngines, int length);
Vehicle     newPlane		(char *name, char *manufacturer, int nEngines, int wingspan);

// polymorphic functions
void        printVehicle    (Vehicle v);
void        printSpeed      (Vehicle v);

// "destructor"
void        freeVehicle     (Vehicle v);

#endif // _VEHICLES_
