CC = gcc
CFLAGS = -g -Wall
OUTDIR = bin

ppm-converter: $(wildcard src/*.c)
	$(CC) $(CFLAGS) -o $(OUTDIR)/$@ $^
