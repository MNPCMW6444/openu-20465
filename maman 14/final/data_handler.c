#include "data_handler.h"
#include "util.h"
#include "prints.h"

/* data handler is a data structre to store and manage the data image */

int D_COUNTER = 0;
int DATA_IMG[MAX_DATA_SIZE] = {IMAGE};

bool add_data_num(char* str_num,int data_counter){
    int num;
    if (data_counter>MAX_DATA_SIZE){
        fprintf(stderr, "Variable %s,unable to save,out of bounds exception\n", str_num);
        return false;
    }
    num = convert_to_int(str_num);
    if (num == INT_MIN)
        return false;
    /* if here everything is fine,save number and data_counter will be incremented in the function caller when true is returned */
    DATA_IMG[data_counter] = num;
    return true;
}

int add_data_string(char* string,int data_counter){
    int i = 0;
    if (string[0] != '\"' || string[strlen(string) -1] != '\"'){
        fprintf(stderr, "ERROR: String variable %s,incorrect format,should start and end with \"\n", string);
        return 0;
    }
    for (string++; string[0] != '\"'; string++){
        DATA_IMG[data_counter] = string[0];
        data_counter++;
        i++;
        if (data_counter > MAX_DATA_SIZE){
            fprintf(stderr, "ERROR: String variable %s,unable to save,out of bounds exception\n",string-data_counter);
            return -1;
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