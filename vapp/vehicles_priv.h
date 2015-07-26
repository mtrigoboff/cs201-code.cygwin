#ifndef _VEHICLES_PRIV_
#define _VEHICLES_PRIV_

#define NAME_MAX_LGTH	20

// private interface to the vehicles code

typedef enum {
	VT_CAR, VT_BOAT, VT_PLANE, N_VEHICLE_TYPES
	}
VehicleType;

// type-specific data for the various vehicle types

typedef struct {
	int			weight;
	}
Car;

typedef struct {
	int			length;
	BoatType	type;
	}
Boat;

typedef struct {
	int			wingspan;
	char		*manufacturerName;
	}
Plane;

// combined data structure for a vehicle
typedef struct {
	VehicleType	type;
	char		name[NAME_MAX_LGTH + 1];
	int			nEngines;
	union {					// type-specific data
		Car			car;
		Boat		boat;
		Plane		plane;
		}		vtsd;		// vehicle type-specific data
	}
VehiclePrivate, *VPtr;

#endif // _VEHICLES_PRIV_
