
CC=gcc
OUTPUT=httpStatus
CFLAGS=-std=c11 -Wall -Wextra -Wpedantic 

CFILES=\
main.c\
status.c

all:
	$(CC) $(CFLAGS) $(CFILES) -o $(OUTPUT)
	

clean:
	rm $(OUTPUT)
