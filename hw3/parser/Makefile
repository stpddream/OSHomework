COMPILERFLAGS = -g -Wall 
CC = gcc
CFLAGS = $(COMPILERFLAGS)
OBJS = main.o parse.o jobs.o

All:	shell

shell:	$(OBJS)
	$(CC) $(CFLAGS) -o mysh $(OBJS) -lreadline

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c
    
parse.o:	parse.c parse.h
	$(CC) $(CFLAGS) -c parse.c

jobs.o: jobs.c jobs.h
	$(CC) $(CFLAGS) -c jobs.c

clean:
	rm *.o *~ mysh *.swp
