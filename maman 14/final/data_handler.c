#include "data_handler.h"
#include "util.h"
#include "prints.h"

/* The data_handler is utilized to store and control the image data */

int DATA_COUNT = 0;
int DATA_IMAGE[MAX_DATA_SIZE] = {IMAGE_PH};

bool insert_number(char* input_num, int data_count){
    int number;
    if (data_count > MAX_DATA_SIZE){
        fprintf(stderr, "Variable %s cannot be saved; out of bounds exception\n", input_num);
        return false;
    }
    number = convert_to_int(input_num);
    if (number == INT_MIN)
        return false;
    /* If code execution reaches here, everything is correct, and the number is saved. Data count will be incremented by the calling function if true is returned. */
    DATA_IMAGE[data_count] = number;
    return true;
}

int insert_string(char* str, int data_count){
    int index = 0;
    if (str[0] != '\"' || str[strlen(str) - 1] != '\"'){
        fprintf(stderr, "ERROR: String variable %s has an incorrect format; it must start and end with \"\n", str);
        return 0;
    }
    for (str++; str[0] != '\"'; str++){
        DATA_IMAGE[data_count] = str[0];
        data_count++;
        index++;
        if (data_count > MAX_DATA_SIZE){
            fprintf(stderr, "ERROR: String variable %s cannot be saved; out of bounds exception\n", str - data_count);
            return -1;
        }
    }
    DATA_IMAGE[data_count] = 0; /* Insert null terminator in integer form */
    data_count++;
    index++;
    return index; /* Return index's value to increment the original data_count by that amount */
}

int retrieveDC()
{
    return DATA_COUNT;
}

void updateDC(int count)
{
    DATA_COUNT = count;
}
