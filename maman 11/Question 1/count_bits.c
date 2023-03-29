/**
 * function - counts the number of evenly indexed bits that are "on" in an unsigned long number
 */
unsigned int bits_count(unsigned long num);

/**
 * The program gets an unsigned long number from the standard input and returns the number of evenly indexed bits that are "on" in it.
 * input: unsigned long number
 * output: unsigned int number as a count
 */

#include <stdio.h>
#include <limits.h>

int main() {
    /* Declare an unsigned long variable to store the user input */
    unsigned long num;
    /* Declare an unsigned int variable to store the result of the bits_count function */
    unsigned int result;

    /* Prompt the user to enter an unsigned long number */
    printf("Please enter an unsigned long number: ");
    /* Read the user input and store it in the num variable */
    scanf("%lu", &num);

    /* Print the entered number */
    printf("You entered: %lu\n", num);

    /* Call the bits_count function and store the result in the result variable */
    result = bits_count(num);
    /* Print the result */
    printf("The result is: %u\n", result);
    return 0;
}

unsigned int bits_count(unsigned long num) {
    /* Declare variables for counting and loop index */
    unsigned int count = 0;
    unsigned int i;
    /* Loop through even-indexed bits */
    for (i = 0; i < sizeof(unsigned long) * CHAR_BIT; i += 2) {
        /* Count the active bits */
        if (num & (1UL << i)) { /* Bitwise operator used to shift the number 2 places every iteration */
            count++;
        }
    }

    return count;
}
