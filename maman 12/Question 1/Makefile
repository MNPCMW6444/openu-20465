CC = gcc
CFLAGS = -ansi -Wall -pedantic
TARGET = my_set

all: $(TARGET)

$(TARGET): my_set.o
	$(CC) $(CFLAGS) -o $(TARGET) my_set.o

my_set.o: my_set.c
	$(CC) $(CFLAGS) -c my_set.c

clean:
	rm -f *.o $(TARGET)
