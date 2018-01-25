all: smallsquare.c smallsquare.h bigsquare.c bigsquare.h uttt.c
	gcc -o uttt smallsquare.c smallsquare.h bigsquare.c bigsquare.h uttt.c

run: all
	#./uttt < win
	#./uttt < o_win
	./uttt < tie
clean:
	rm uttt
	rm *~
	rm *.o
