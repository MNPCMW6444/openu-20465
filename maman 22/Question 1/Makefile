CC = gcc
CFLAGS = -ansi -Wall -pedantic
TARGET = mycomp

all: $(TARGET)

$(TARGET): mycomp.o complex.o
	$(CC) $(CFLAGS) -o $(TARGET) mycomp.o complex.o

mycomp.o: mycomp.c complex.h
	$(CC) $(CFLAGS) -c mycomp.c

complex.o: complex.c complex.h
	$(CC) $(CFLAGS) -c complex.c

clean:
	rm -f *.o $(TARGET)
