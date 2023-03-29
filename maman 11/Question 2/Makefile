CC = gcc
CFLAGS = -ansi -Wall -pedantic
TARGET = my_string

all: $(TARGET)

$(TARGET): my_string.o
	$(CC) $(CFLAGS) -o $(TARGET) my_string.o

my_string.o: my_string.c
	$(CC) $(CFLAGS) -c my_string.c

clean:
	rm -f *.o $(TARGET)