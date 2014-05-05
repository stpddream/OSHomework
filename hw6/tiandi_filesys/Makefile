CFLAGS = -g -Wall 
CC = gcc
OBJS = test_main.o device_ctrl.o bitmap.o filesys.o filesys_util.o util.o file_table.o file.o inode_table.o

All:	tiandi_file
tiandi_file: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o test_main

filesys_util.o: filesys_util.c filesys_util.h filesys.h
	$(CC) $(CFLAGS) -c filesys_util.c
	
device_ctrl.o: device_ctrl.c device_ctrl.h filesys.h
	$(CC) $(CFLAGS) -c device_ctrl.c
	
bitmap.o: bitmap.c bitmap.h util.h
	$(CC) $(CFLAGS) -c bitmap.c



file.o: file.c file.h file_table.h filesys_hd.h inode_table.h
	$(CC) $(CFLAGS) -c file.c

filesys.o: filesys.c filesys.h filesys_util.h util.h
	$(CC) $(CLFAGS) -c filesys.c
	
file_table.o: file_table.c file_table.h util.h
	$(CC) $(CFLAGS) -c file_table.c
	
inode_table.o: inode_table.c inode_table.h util.h
	$(CC) $(CFLAGS) -c inode_table.c
	
util.o: util.c util.h filesys.h
	$(CC) $(CFLAGS) -c util.c
	
clean:
	rm -f *.o test_main .*.sw*
