CFLAGS = -g -Wall 
CC = gcc
OBJS = test_main.o device_ctrl.o bitmap.o filesys.o filesys_util.o util.o file_table.o file.o inode_table.o file_util.o ft_dir.o usr.o inode_list.o commands.o sh_util.o

All:	tiandi_file
tiandi_file: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o test_main

filesys_util.o: filesys_util.c filesys_util.h filesys.h
	$(CC) $(CFLAGS) -c filesys_util.c
	
device_ctrl.o: device_ctrl.c device_ctrl.h filesys.h
	$(CC) $(CFLAGS) -c device_ctrl.c
	
bitmap.o: bitmap.c bitmap.h util.h
	$(CC) $(CFLAGS) -c bitmap.c

file.o: file.c file.h file_table.h filesys_hd.h inode_table.h file_util.h ft_dir.h
	$(CC) $(CFLAGS) -c file.c

file_util.o: file_util.c file_util.h
	$(CC) $(CFLAGS) -c file_util.c

ft_dir.o: ft_dir.c ft_dir.h filesys.h
	$(CC) $(CFLAGS) -c ft_dir.c

filesys.o: filesys.c filesys.h filesys_util.h util.h
	$(CC) $(CLFAGS) -c filesys.c
	
file_table.o: file_table.c file_table.h util.h
	$(CC) $(CFLAGS) -c file_table.c
	
inode_table.o: inode_table.c inode_table.h util.h
	$(CC) $(CFLAGS) -c inode_table.c

inode_list.o: inode_list.c inode_list.h filesys_hd.h filesys.h kernel_mem.h
	$(CC) $(CFLAGS) -c inode_list.c

commands.o: commands.c commands.h sh_util.h inode_list.h file.h
	$(CC) $(CFLAGS) -c commands.c

sh_util.o: sh_util.c sh_util.h
	$(CC) $(CFLAGS) -c sh_util.c
	
usr.o: usr.c usr.h sh_util.h
	$(CC) $(CFLAGS) -c usr.c
	
util.o: util.c util.h filesys.h
	$(CC) $(CFLAGS) -c util.c
	
clean:
	rm -f *.o test_main .*.sw*
