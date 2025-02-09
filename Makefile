CC = gcc
CFLAGS = -g -Wall
OUTDIR = bin

main: $(wildcard src/*.c)
	$(CC) $(CFLAGS) -o $(OUTDIR)/$@ $^
