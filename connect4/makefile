all: board.c board.h connect4.c
	gcc -o connect4 board.c board.h connect4.c

run: all
	./connect4
	#./connect4 < input
clean:
	rm connect4
	rm *~
	rm *.o
