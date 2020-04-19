CFLAGS = -g -std=c99 -Wall -Werror

part1: part1.o CSG.o A.o B.o C.o D.o
	$(CC) -o $@ $(CFLAGS) $^

part2: part2.o CSG.o A.o B.o C.o D.o
	$(CC) -o $@ $(CFLAGS) $^
part3: part3.o CSG.o A.o B.o C.o D.o
	$(CC) -o $@ $(CFLAGS) $^
clean:
	rm *.o part1 part2 part3
