CC = gcc
CFLAGS = -c

all : q1 q2 q3 q4

q1 : ./1/main.o ./1/functions.o
	$(CC) ./1/main.o ./1/functions.o -o ./1/q1.o

main.o : ./1/main.c
	$(CC) $(CFLAGS) ./1/main.c

functions.o : ./1/functions.c
	$(CC) $(CFLAGS) ./1/functions.c

q2 : ./2/main.o ./2/functions.o
	$(CC) ./2/main.o ./2/functions.o -o ./2/q2.o

main.o : ./2/main.c
	$(CC) $(CFLAGS) ./2/main.c

functions.o : ./2/functions.c
	$(CC) $(CFLAGS) ./2/functions.c

q3 : ./3/main.o ./3/functions.o
	$(CC) ./3/main.o ./3/functions.o -o ./3/q3.o

main.o : ./3/main.c
	$(CC) $(CFLAGS) ./3/main.c

functions.o : ./3/functions.c
	$(CC) $(CFLAGS) ./3/functions.c

q4 : ./4/main.o ./4/functions.o
	$(CC) ./4/main.o ./4/functions.o -o ./4/q4.o

main.o : ./4/main.c
	$(CC) $(CFLAGS) ./4/main.c

functions.o : ./4/funct…