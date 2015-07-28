#pragma once
#include "vehicle.h"

class Plane : public Vehicle
{
	private:
		int		wingSpan;
		
	public:
		Plane(char *name, int nEngines, int wingSpan);
		~Plane(void);
		void print(std::ostream& out);
		void printSpeed(std::ostream& out);
};
