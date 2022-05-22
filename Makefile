CC = gcc
CFLAGS = -Wall -g -o

calc_unbounded_int : unbounded_int.o calc_unbounded_int.o
	$(CC) $(CFLAGS) calc_unbounded_int unbounded_int.o calc_unbounded_int.o
test : unbounded_int.o test_unbounded.o
	$(CC) $(CFLAGS) test unbounded_int.o test_unbounded.o
calc_unbounded_int.o : calc_unbounded_int.c
	$(CC) $(CFLAGS) calc_unbounded_int.o -c calc_unbounded_int.c
unbounded_int.o : unbounded_int.c
	$(CC) $(CFLAGS) unbounded_int.o -c unbounded_int.c
test_unbounded.o : test_unbounded.c
	$(CC) $(CFLAGS) test_unbounded.o -c test_unbounded.c
clean :
	rm -rf *.o && rm -rf prog