#include "data_handler.h"
#include "util.h"
#include "prints.h"

/* The data handler acts as a structure to hold and manage the image data. */

int D_COUNTER = 0;
int DATA_IMG[MEM_SIZE] = {IMAGE};

bool add_data_num(char* str_num,int data_counter){
    int num;
    if (data_counter>MEM_SIZE){
        fprintf(stderr, "Variable %s,unable to save,out of bounds exception\n", str_num);
        return false;
    }
    num = convert_to_int(str_num);
    if (num == INT_MIN)
        return false;
    /* Successful till here. Save the number. Incrementing of data_counter is handled by the calling function on successful return. */
    DATA_IMG[data_counter] = num;
    return true;
}

int add_data_string(char* string,int data_counter){
    int i = 0;
    if (string[0] != '\"' || string[strlen(string) -1] != '\"'){
        fprintf(stderr, "ERROR: String variable %s,incorrect format, it should start and end with \"\n", string);
        return 0;
    }
    for (string++; string[0] != '\"'; string++){
        DATA_IMG[data_counter] = string[0]; /* Representing null-terminator in integer form. */
        data_counter++;
        i++;
        if (data_counter > MEM_SIZE){
            fprintf(stderr, "ERROR: String variable %s, unable to save, out of bounds exception\n",string-data_counter);
            return i; /* Return i to adjust the original data_counter accordingly. */
        }
    }
    string[data_counter] = 0; /* null terminator in int base */
    data_counter++;
    i++;
    return i; /* return the value of i to increment the original data_counter by that amount */
}

int getDC()
{
    return D_COUNTER;
}

void addDC(int counter)
{
    D_COUNTER = counter;
}