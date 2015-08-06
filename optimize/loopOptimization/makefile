include ~/bin/makeflags_gcc

all:				loop loopunrolled \
						loopsplit ptrloop \
						loop.opt loopunrolled.opt \
						loopsplit.opt ptrloop.opt
					touch all

loop:				iterations.h

loopunrolled:		iterations.h

loopsplit:			iterations.h

ptrloop:			iterations.h

loop.opt:			iterations.h

loopunrolled.opt:	iterations.h

loopsplit.opt:		iterations.h

ptrloop.opt:		iterations.h

.PHONY:	x
x:
					$(info -- cleaning directory --)
					rm loop loopunrolled
					rm loopsplit ptrloop
					rm loop.opt loopunrolled.opt
					rm loopsplit.opt ptrloop.opt
					rm all

# rule for building optimized executables
%.opt : %.c
					$(CC) $(CFLAGS) -O3 $< -o $@
