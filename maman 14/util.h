#ifndef MY_UTILS_H
#define MY_UTILS_H

#include "globals.h"

char* amext;
char* asext;
char* entryext;
char* externalext;
char* objectext;

bool lineToIgnore(char* line);

bool lengthTest(char* line);

bool isReservedWord(char* word);

bool is_register(char* word);

char* str_allocate_cat(char* first_str, char* second_str);

void format_line(char*);

int convert_to_int(char* word);

const char delims[4];

#endif