#pragma once
#include <ostream>

class Vehicle
	{
	protected:
		char		name[30];
		int			nEngines;

		Vehicle(char *name, int nEngines);
	
	public:
		virtual ~Vehicle(void);
		virtual void print(std::ostream& out);
		virtual void printSpeed(std::ostream& out) = 0;
	};
