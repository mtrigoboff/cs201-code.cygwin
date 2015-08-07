include ~/bin/makeflags_gcc

# LDFLAGS definition from makeflags_gcc is
# redundant in this situation

LDFLAGS =

all:			loop loopunroll loopsplit loopptr \
					loop.opt loopunroll.opt \
					loopsplit.opt loopptr.opt
				touch all

loop:			iterations.h

loopunroll:		iterations.h

loopsplit:		iterations.h

loopptr:		iterations.h

loop.opt:		iterations.h

loopunroll.opt:	iterations.h

loopsplit.opt:	iterations.h

loopptr.opt:	iterations.h

.PHONY:	x
x:
				$(info -- cleaning directory --)
				rm -f loop loopunroll
				rm -f loopsplit loopptr
				rm -f loop.opt loopunroll.opt
				rm -f loopsplit.opt loopptr.opt
				rm -f all

# rule for building optimized executables
%.opt : %.c
				$(CC) $(CFLAGS) -O3 $< -o $@

