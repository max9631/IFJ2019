CC = gcc
CFLAGS = -pedantic -Wall -Wextra -std=c99
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
PROGRAM = ifj
XLOGIN = xvever12

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	gcc $(CFLAGS) $^ -o $@ -lm
	rm *.o

%.o: %.c
	gcc $(CFLAGS) -c $^ -o $@ -lm

clean:
	rm *.o $(PROGRAM) $(XLOGIN).zip

zip:$(XLOGIN).zip

$(XLOGIN).zip:
	zip $(XLOGIN).zip *.c *.h Makefile dokumentace.pdf rozdeleni rozsireni
