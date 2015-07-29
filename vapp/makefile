include ~/bin/makeflags_gcc

LDFLAGS = -m32 -lm

vapp:		vapp.o vehicles.o

vapp.o:		vehicles.h vehicles_priv.h

vehicles.o:	vehicles.h vehicles_priv.h

.PHONY:	x
x:			# clean the directory
			$(info -- cleaning the directory --)
			rm -f *.o vapp
