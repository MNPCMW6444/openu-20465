/* 
 * my_set.c
 *
 * Program Goals:
 * This program takes a list of integers as input and creates a set from them.
 * A set is an unordered collection of unique elements. The program then prints
 * the set elements in the order they were received.
 *
 * Input/Output:
 * The program reads an unlimited number of integers from the input (stdin)
 * and prints the set elements in the order they were received.
 *
 * Assumptions:
 * We assume that input integers are within the range of the 'int' data type.
 * The input may contain duplicate values, which will only appear once in the set.
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE_ENLARGE 10

/*
 * Function: int *set_get(int *size)
 * Purpose: Reads integers from the user and creates a set from them.
 * Input: A pointer to an int variable that will store the size of the set.
 * Output: Returns a pointer to an int array representing the set. The array is dynamically allocated.
 * Algorithm: Uses a dynamic array and realloc to handle an unlimited number of input integers.
 */
int *set_get(int *size);

/*
 * Function: void set_print(const int *set, int size)
 * Purpose: Prints the set elements in the order they were received.
 * Input: A pointer to an int array representing the set and the size of the set.
 * Output: None
 */
void set_print(const int *set, int size);


int *set_get(int *size) {
    int *set = NULL;
    int capacity = 0;
    int value;
    int i;

    while (scanf("%d", &value) != EOF) {
        /* Check if the value is already in the set */
        int exists = 0;
        for (i = 0; i < *size; i++) {
            if (set[i] == value) {
                exists = 1;
                break;
            }
        }

        /* Add the value to the set if it's not already there */
        if (!exists) {
            if (*size == capacity) {
                capacity += SIZE_ENLARGE;
                set = (int *)realloc(set, capacity * sizeof(int));
            }
            set[*size] = value;
            (*size)++;
        }
    }

    return set;
}


void set_print(const int *set, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", set[i]);
    }
    printf("\n");
}

int main() {
    int set_size = 0;
    int *set;

    printf("Please enter the integer values (Ctrl-D to finish):\n");
    set = set_get(&set_size);
    set_print(set, set_size);

    free(set);
    return 0;
}
