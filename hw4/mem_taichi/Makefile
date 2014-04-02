CFLAGS = -g -Wall 
CC = gcc
OBJS = main.o mem.o mem_util.o test_mem.o
All:	mem_taichi

mem_taichi:	$(OBJS) 
	$(CC) $(CFLAGS) -o mem_taichi $(OBJS)

main.o: main.c mem.h
	$(CC) $(CFLAGS) -c main.c

	
mem.o: mem.c mem.h
	$(CC) $(CFLAGS) -c mem.c

util.o: mem_util.c mem_util.h
	$(CC) $(CFLAGS) -c mem_util.c

test_mem.o: test_mem.c test_mem.h
	$(CC) $(CFLAGS) -c test_mem.c

	

clean:
	rm *.o mem_taichi .*.sw*
