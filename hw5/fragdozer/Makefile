CFLAGS = -g -Wall 
CC = gcc
$OBJS = defrag.o
All:	defrag
	
defrag: defrag.o
	$(CC) $(CFLAGS) defrag.o -o defrag

defrag.o: defrag.c 
	$(CC) $(CFLAGS) -c defrag.c

clean:
	rm -f *.o defrag .*.sw* 
