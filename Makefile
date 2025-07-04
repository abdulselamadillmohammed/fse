# File: Makefile

CC = gcc
CFLAGS = -Wall -O2 -I/usr/local/include
LDFLAGS = -L/usr/local/lib -larcfour

TARGET = fse
SRC = fse.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install:
	cp libarcfour.so /usr/local/lib/
	cp arcfour.h /usr/local/include/

clean:
	rm -f $(OBJ) $(TARGET)
