include ~/bin/makeflags_gcc

done:		burntime timer
			touch done

burntime:	burntime.c
			$(CC) $(CFLAGS) -DTEST burntime.c -o burntime

timer:		timer.c burntime.c
			$(CC) $(CFLAGS) burntime.c timer.c -o timer

.PHONY:		x
x:
			$(info -- cleaning directory --)
			rm -f done burntime timer
