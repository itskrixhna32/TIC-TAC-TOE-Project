CC=gcc
CFLAGS=-Iinclude -std=c11 -Wall
SRCS=src/main.c src/game.c src/ai.c
all:
	$(CC) $(CFLAGS) $(SRCS) -o main
clean:
	rm -f main
