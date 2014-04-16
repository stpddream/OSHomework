CFLAGS = -g -Wall 
CC = gcc
OBJS = defrag.o dozer.o util.o
All:	defrag
	
defrag: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o defrag

defrag.o: defrag.c dozer.h util.h
	$(CC) $(CFLAGS) -c defrag.c

dozer.o: dozer.c dozer.h
	$(CC) $(CFLAGS) -c dozer.c
	
dreader.o: dreader.c dreader.h
	$(CC) $(CFLAGS) -c dreader.c
	
util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c


clean:
	rm -f *.o defrag .*.sw* 
