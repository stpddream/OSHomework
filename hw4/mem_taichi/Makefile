CFLAGS = -g -Wall 
CC = gcc

All:	mem_taichi

mem_taichi:	main.o mem.o util.o 
	$(CC) $(CFLAGS) -o mem_taichi main.o mem.o util.o 

main.o: main.c mem.h
	$(CC) $(CFLAGS) -c main.c
	
mem.o: mem.c mem.h
	$(CC) $(CFLAGS) -c mem.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

clean:
	rm *.o mem_taichi
