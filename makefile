#!/usr/bin/make -f

export
cflags=-Wall -std=c18 -Os -s -march=native

all: crlayout

crlayout: main.o
	gcc $$cflags -o $@ $<

%.o: %.c makefile
	gcc $$cflags -o $@ $< -c

clean:
	rm crlayout *.o
