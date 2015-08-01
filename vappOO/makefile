include ~/bin/makeflags_g++

# -lm is not required even though boat.cpp uses sqrt()
# because you automatically get the math library in g++

vappOO:		vappOO.o vehicle.o car.o boat.o plane.o

vehicle.o:	vehicle.h

car.o:		vehicle.o car.h

boat.o:		vehicle.o boat.h

plane.o:	vehicle.o plane.h

.PHONY:	x
x:			# clean the directory
			$(info -- cleaning the directory --)
			rm -f *.o vappOO
