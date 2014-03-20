COMPILERFLAGS = -g -Wall 
CC = gcc
CFLAGS = $(COMPILERFLAGS)
OBJS = main.o cmd_control.o cmd_history.o parser.o jobs.o util.o

All:	shell

shell:	$(OBJS)
	$(CC) $(CFLAGS) -o mysh $(OBJS) -lreadline

main.o: main.c parser.h cmd_control.h cmd_history.h util.h jobs.h
	$(CC) $(CFLAGS) -c main.c

cmd_conrtol.o:  cmd_control.c cmd_control.h
	$(CC) $(CFLAGS) -c cmd_control.c

cmd_history.o:  cmd_history.c cmd_history.h util.h
	$(CC) $(CFLAGS) -c cmd_history.c

parser.o:	parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

jobs.o: jobs.c jobs.h
	$(CC) $(CFLAGS) -c jobs.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c


clean:
	rm *.o mysh
