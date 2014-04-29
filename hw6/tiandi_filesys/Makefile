CFLAGS = -g -Wall 
CC = gcc
OBJS = test_main.o diskio.o bitmap.o filesys.o filesys_util.o util.o 

All:	tiandi_file
tiandi_file: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o test_main

filesys.o: filesys.c filesys.h filesys_util.h
	$(CC) $(CLFAGS) -c filesys.c
	
filesys_util.o: filesys_util.c filesys_util.h filesys.h
	$(CC) $(CFLAGS) -c filesys_util.c
	
diskio.o: diskio.c diskio.o
	$(CC) $(CFLAGS) -c diskio.c
	
bitmap.o: bitmap.c bitmap.h util.h
	$(CC) $(CFLAGS) -c bitmap.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c
	

clean:
	rm -f *.o test_main .*.sw*
