#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include "globals.h"

int DATA_IMG[MAX_DATA_SIZE];

/* adds number to data_img and return true/false according to sucess */
bool insert_number(char*,int);

/* adds string and also null terminator to data_img and return the number of incerement for dc,0 in case of invalid format and -1 in case of out of bounds */
int insert_string(char*,int);

int retrieveDC();

void updateDC(int counter);

#endif