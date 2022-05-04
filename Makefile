CC = gcc

#CFLAGS = -Wall -g -pedantic

prog :unbounded_int.o test_unbounded.o 
	$(CC) -Wall -o prog unbounded_int.o test_unbounded.o

unbounded_int.o : unbounded_int.c
	$(CC) -Wall -o unbounded_int.o -c unbounded_int.c
test_unbounded.o : test_unbounded.c
	$(CC) -Wall -o test_unbounded.o -c test_unbounded.c
clean :
	rm -rf *.o && rm -rf prog