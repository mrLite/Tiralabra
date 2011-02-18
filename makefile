# makefile

CC = gcc 

OXO: main.o helpers.o
	$(CC) main.o helpers.o -o OXO
helpers.o: helpers.c
	$(CC) -c helpers.c -o helpers.o
main.o: main.c
	$(CC) -c main.c -o main.o

clean:
	rm *.o