
CFLAGS = -c -o
CC = g++
main: file3.o file2.o file1.o
	$(CC) -o finalgame.o  file2.o file3.o file1.o

%.o: %.cpp
		$(CC) $(CFLAGS) $@ $<
clean: 
		rm -f *.o