#pragma once
#include "vehicle.h"

class Boat :
	public Vehicle
	{
	private:
		int		length;
		
	public:
		Boat(char *name, int nEngines, int length);
		~Boat(void);
		void print(std::ostream& out);
		void printSpeed(std::ostream& out);
	};
