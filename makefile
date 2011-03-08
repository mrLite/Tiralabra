# makefile

CC = gcc -Wall -g

OXO: main.o helpers.o negamax.o
	$(CC) main.o helpers.o negamax.o -o OXO
test: helpers.o negamax.o test.o
	$(CC) helpers.o negamax.o test.o -o test
helpers.o: helpers.c
	$(CC) -c helpers.c -o helpers.o
main.o: main.c
	$(CC) -c main.c -o main.o
negamax.o: negamax.c
	$(CC) -c negamax.c -o negamax.o
test.o: test.c
	$(CC) -c test.c -o test.o

clean:
	rm *.o