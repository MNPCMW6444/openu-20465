#ifndef PRINTS_H
#define PRINTS_H

#include "globals.h"
#include "symbol_table.h"

void write_entry_file (symbol_type symbol, char* file_name);

void write_external_file (char* symbol_name,int word_location, char* file_name);

void print_object(char* file_name);

void clean_outputs(char* file_name);

#endif