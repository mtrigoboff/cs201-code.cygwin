include ~/bin/makeflags_g++

CC=g++
LDFLAGS=-m32

vappOO:		vappOO.o vehicle.o car.o boat.o plane.o

vehicle.o:	vehicle.h

car.o:		vehicle.o car.h

boat.o:		vehicle.o boat.h

plane.o:	vehicle.o plane.h

.PHONY:	x
x:			# clean the directory
			$(info -- cleaning the directory --)
			rm -f *.o vappOO
