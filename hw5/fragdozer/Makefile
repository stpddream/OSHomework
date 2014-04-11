CFLAGS = -g -Wall 
CC = gcc
$OBJS = defrag.o
All:	defrag
	
defrag: defrag.o dozer.o
	$(CC) $(CFLAGS) defrag.o dozer.o -o defrag

defrag.o: defrag.c dozer.h
	$(CC) $(CFLAGS) -c defrag.c

dozer.o: dozer.c dozer.h
	$(CC) $(CFLAGS) -c dozer.c


clean:
	rm -f *.o defrag .*.sw* 
