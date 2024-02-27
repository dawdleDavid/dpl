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
clean:
	rm mtpl
.PHONY : main.o readfile.o
