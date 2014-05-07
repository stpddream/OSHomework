COMPILERFLAGS = -g -Wall 
CC = gcc
CFLAGS = $(COMPILERFLAGS)
OBJS = main.o cmd_control.o cmd_history.o parser.o jobs.o util.o usr.o commands.o

All:	shell

shell:	$(OBJS)
	$(CC) $(CFLAGS) -o mysh $(OBJS) -lreadline

main.o: main.c parser.h cmd_control.h cmd_history.h util.h jobs.h commands.h
	$(CC) $(CFLAGS) -c main.c

cmd_conrtol.o:  cmd_control.c cmd_control.h
	$(CC) $(CFLAGS) -c cmd_control.c

cmd_history.o:  cmd_history.c cmd_history.h util.h
	$(CC) $(CFLAGS) -c cmd_history.c
	
commands.o: commands.c commands.h
	$(CC) $(CFLAGS) -c commands.c

parser.o:	parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

jobs.o: jobs.c jobs.h
	$(CC) $(CFLAGS) -c jobs.c
	
usr.o: usr.c usr.h util.h
	$(CC) $(CFLAGS) -c usr.c	

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c


clean:
	rm -rf *.o mysh
