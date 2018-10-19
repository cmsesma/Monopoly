hoarding.out: main.o board.o
	gcc -g -Wall -Werror main.o board.o -o hoarding.out

main.o: main.c
	gcc -g -Wall -Werror -c main.c

board.o: board.c board.h
	gcc -g -Wall -Werror -c board.c

clean:
	rm -f *.o *.out