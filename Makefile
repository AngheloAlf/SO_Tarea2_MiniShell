all: main

main: main.o strParse.o
	gcc -o main main.o strParse.o -O3 -Wall

main.o: main.c
	gcc main.c -c -O3 -Wall

strParse.o: strParse.c
	gcc strParse.c -c -O3 -Wall

clean:
	rm *.o
