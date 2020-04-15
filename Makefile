CFLAGS = -g -std=c99 -Wall -Werror

part1: part1.o CSG.o A.o B.o C.o D.o
	$(CC) -o $@ $(CFLAGS) $^