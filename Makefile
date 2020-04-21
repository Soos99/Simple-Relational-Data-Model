CFLAGS = -g -std=c99 -Wall -Werror

part1: part1.o ./Hashtable/CSG.o ./Hashtable/A.o ./Hashtable/B.o ./Hashtable/C.o ./Hashtable/D.o
	$(CC) -o $@ $(CFLAGS) $^
part2: part2.o ./Hashtable/CSG.o ./Hashtable/A.o ./Hashtable/B.o ./Hashtable/C.o ./Hashtable/D.o
	$(CC) -o $@ $(CFLAGS) $^
part3: part3.o ./Hashtable/CSG.o ./Hashtable/C.o ./Hashtable/D.o ./Hashtable/CD.o ./Query/QueryCSG.o ./Query/QueryCD.o 
	$(CC) -o $@ $(CFLAGS) $^
valgrind1: 
	make part1 && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./part1
valgrind2: 
	make part2 && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./part2
valgrind3: 
	make part3 && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./part3
clean:
	rm *.o ./Hashtable/*.o ./Query/*.o part1 part2 part3
