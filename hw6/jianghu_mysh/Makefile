COMPILERFLAGS = -g -Wall -L.
FLB = -lfilesys
CC = gcc
CFLAGS = $(COMPILERFLAGS)
OBJS = main.o cmd_control.o cmd_history.o parser.o jobs.o util.o inode_list.o commands.o

All:	shell

shell:	$(OBJS)
	$(CC) $(CFLAGS) -o mysh $(OBJS) -lreadline $(FLB)

main.o: main.c parser.h cmd_control.h cmd_history.h util.h jobs.h commands.h
	$(CC) $(CFLAGS) -c main.c $(FLB)

cmd_conrtol.o:  cmd_control.c cmd_control.h
	$(CC) $(CFLAGS) -c cmd_control.c $(FLB)

cmd_history.o:  cmd_history.c cmd_history.h util.h
	$(CC) $(CFLAGS) -c cmd_history.c $(FLB)
	
commands.o: commands.c commands.h
	$(CC) $(CFLAGS) -c commands.c $(FLB)

parser.o:	parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c $(FLB)

jobs.o: jobs.c jobs.h
	$(CC) $(CFLAGS) -c jobs.c

inode_list.o: inode_list.c inode_list.h
	$(CC) $(CFLAGS) -c inode_list.c $(FLB)

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c $(FLB)


clean:
	rm -rf *.o mysh
