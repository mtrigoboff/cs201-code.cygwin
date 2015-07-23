#pragma once
#include <ostream>

class Vehicle
	{
	private:
		int			nEngines;
		char		name[16];

	protected:
		Vehicle(char *name, int nEngines);
	
	public:
		virtual ~Vehicle(void);
		virtual void print(std::ostream& out);
		virtual void printSpeed(std::ostream& out) = 0;
	};
