# makefile

CC = gcc 

OXO: main.o helpers.o negamax.o
	$(CC) main.o helpers.o negamax.o -o OXO
helpers.o: helpers.c
	$(CC) -c helpers.c -o helpers.o
main.o: main.c
	$(CC) -c main.c -o main.o
negamax.o: negamax.c
	$(CC) -c negamax.c -o negamax.o

clean:
	rm *.o