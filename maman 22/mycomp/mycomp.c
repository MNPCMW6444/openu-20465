/*
 * mycomp.c
 *
 * This program interacts with the user to perform operations on complex numbers.
 * It supports the following operations: read, print, add, subtract, and multiply.
 */

#include <stdio.h>
#include <string.h>
#include "complex.h"

/* Function to handle the commands entered by the user */
void handle_command(char* command, complex* A, complex* B, complex* C, complex* D, complex* E, complex* F);

int main() {
    char command[50];
    complex A, B, C, D, E, F;

    while (1) {
        printf("Enter a command: ");
        fgets(command, 50, stdin);
        handle_command(command, &A, &B, &C, &D, &E, &F);
    }
    
    return 0;
}

/* Function to handle the commands entered by the user */
void handle_command(char* command, complex* A, complex* B, complex* C, complex* D, complex* E, complex* F) {
    /* Handle the read_comp command */
    
    complex *comp1 = NULL, *comp2 = NULL, *comp_result = NULL;

    if (strncmp(command, "read_comp", 9) == 0) {
    char comp_name;
    double real, imag;
    if (sscanf(command, "read_comp %c %lf %lf", &comp_name, &real, &imag) != 3) {
        printf("Improperly formatted command. Use: read_comp <comp_name> <real_part> <imaginary_part>\n");
        return;
    }
    switch(comp_name) {
        case 'A': A->real = real; A->imag = imag; break;
        case 'B': B->real = real; B->imag = imag; break;
        case 'C': C->real = real; C->imag = imag; break;
        case 'D': D->real = real; D->imag = imag; break;
        case 'E': E->real = real; E->imag = imag; break;
        case 'F': F->real = real; F->imag = imag; break;
    }
    /* Handle the print_comp command */
 } else if (strncmp(command, "print_comp", 10) == 0) {
        char comp_name;
        sscanf(command, "print_comp %c", &comp_name);
        switch(comp_name) {
            case 'A': print_comp(*A); break;
            case 'B': print_comp(*B); break;
            case 'C': print_comp(*C); break;
            case 'D': print_comp(*D); break;
            case 'E': print_comp(*E); break;
            case 'F': print_comp(*F); break;
        }
    /* Handle the add_comp command */
    } else if (strncmp(command, "add_comp", 8) == 0) {
        char comp_name1, comp_name2, comp_name_result;
        sscanf(command, "add_comp %c, %c, %c", &comp_name1, &comp_name2, &comp_name_result);

        comp1 = NULL;
        comp2 = NULL;
        comp_result = NULL;

        switch(comp_name1) {
            case 'A': comp1 = A; break;
            case 'B': comp1 = B; break;
            case 'C': comp1 = C; break;
            case 'D': comp1 = D; break;
            case 'E': comp1 = E; break;
            case 'F': comp1 = F; break;
        }
        switch(comp_name2) {
            case 'A': comp2 = A; break;
            case 'B': comp2 = B; break;
            case 'C': comp2 = C; break;
            case 'D': comp2 = D; break;
            case 'E': comp2 = E; break;
            case 'F': comp2 = F; break;
        }
        switch(comp_name_result) {
            case 'A': comp_result = A; break;
            case 'B': comp_result = B; break;
            case 'C': comp_result = C; break;
            case 'D': comp_result = D; break;
            case 'E': comp_result = E; break;
            case 'F': comp_result = F; break;
        }
        if (comp1 && comp2 && comp_result) {
            *comp_result = add_comp(*comp1, *comp2);
        }
    /* Handle other commands */
    } else {
        printf("Invalid command\n");
    }
}
