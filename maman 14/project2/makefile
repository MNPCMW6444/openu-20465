CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11 -ggdb3
SRC_FILES = asmblrMain.c commands.c data_handler.c first_pass.c macro_table.c mcroUnfold.c read_row.c second_pass.c symbol_table.c util.c
HEADER_FILES = commands.h data_handler.h globals.h macro_table.h mcroUnfold.h symbol_table.h util.h
OUTPUT = myProg

$(OUTPUT): $(SRC_FILES) $(HEADER_FILES)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SRC_FILES)

clean:
	rm -f $(OUTPUT)

