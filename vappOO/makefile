include ~/bin/g++flags

CC=g++
LDFLAGS=-m32

vappOO:		vappOO.o vehicle.o car.o boat.o plane.o

.cpp.o:
			g++ $(CPP_FLAGS) -c $<

.PHONY:	x
x:			# clean the directory
			$(info -- cleaning the directory --)
			rm -f *.o vappOO
