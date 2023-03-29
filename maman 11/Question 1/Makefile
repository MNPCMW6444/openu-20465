CC = gcc
CFLAGS = -ansi -Wall -pedantic
TARGET = count_bits

all: $(TARGET)

$(TARGET): count_bits.o
	$(CC) $(CFLAGS) -o $(TARGET) count_bits.o

count_bits.o: count_bits.c
	$(CC) $(CFLAGS) -c count_bits.c

clean:
	rm -f *.o $(TARGET)