# Makefile for mtpl
#
#
#
edit: main.o readfile.o
	cc -o mtpl main.o readfile.o

main.o: frontend/main.c frontend/readfile.h
	cc -c frontend/main.c
readfile.o: frontend/readfile.c
	cc -c frontend/readfile.c
rmex:
	rm mtpl
.PHONY : main.o readfile.o

clean:
	rm *.o
simple: frontend/main.c frontend/readfile.c frontend/readfile.h
	cc -o mptl frontend/main.c frontend/readfile.c frontend/readfile.h
