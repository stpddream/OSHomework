CFLAGS = -g -Wall 
CC = gcc
OBJS = defrag.o dozer.o util.o dreader.o dwriter.o 
All:	defrag
	
defrag: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o defrag

defrag.o: defrag.c dozer.h util.h dreader.h dwriter.h 
	$(CC) $(CFLAGS) -c defrag.c

dozer.o: dozer.c dozer.h dreader.h dwriter.h
	$(CC) $(CFLAGS) -c dozer.c

util.o: util.c util.h dozer.h
	$(CC) $(CFLAGS) -c util.c
	
dreader.o: dreader.c dreader.h dozer.h util.h
	$(CC) $(CFLAGS) -c dreader.c

dwriter.o: dwriter.c dwriter.h dozer.h util.h
	$(CC) $(CFLAGS) -c dwriter.c
	  

clean:
	rm -f *.o defrag .*.sw* 
