#pragma once
#include "vehicle.h"

typedef enum {
	unknown, sail, power, amphibian
	}
BoatType;

class Boat : public Vehicle
{
	private:
		int			length;
		BoatType	type;	
		
	public:
		Boat(char *name, BoatType type, int nEngines, int length);
		~Boat(void);
		void print(std::ostream& out);
		void printSpeed(std::ostream& out);
};
