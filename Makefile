CFLAGS = -g -std=c99 -Wall -Werror

part1: part1.o CSG.o A.o B.o C.o D.o
	$(CC) -o $@ $(CFLAGS) $^
part2: part2.o CSG.o A.o B.o C.o D.o
	$(CC) -o $@ $(CFLAGS) $^
part3: part3.o CSG.o C.o D.o CD.o QueryCSG.o QueryCD.o 
	$(CC) -o $@ $(CFLAGS) $^
valgrind1: 
	make part1 && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./part1
valgrind2: 
	make part2 && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./part2
valgrind3: 
	make part3 && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./part3
clean1:
	rm *.o part1 
clean2:
	rm *.o part2 
clean3:
	rm *.o part3
