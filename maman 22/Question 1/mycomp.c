#include <stdio.h>
#include <string.h>
#include "complex.h"

void handle_command(char* command, complex* A, complex* B, complex* C, complex* D, complex* E, complex* F) {
    if (strncmp(command, "comp_read", 9) == 0) {
        char comp_name;
        float real, imag;
        sscanf(command, "comp_read %c, %f, %f", &comp_name, &real, &imag);
        switch(comp_name) {
            case 'A': comp_read(A, real, imag); break;
            case 'B': comp_read(B, real, imag); break;
            case 'C': comp_read(C, real, imag); break;
            case 'D': comp_read(D, real, imag); break;
            case 'E': comp_read(E, real, imag); break;
            case 'F': comp_read(F, real, imag); break;
        }
    } else if (strncmp(command, "comp_print", 10) == 0) {
        char comp_name;
        sscanf(command, "comp_print %c", &comp_name);
        switch(comp_name) {
            case 'A': comp_print(*A); break;
            case 'B': comp_print(*B); break;
            case 'C': comp_print(*C); break;
            case 'D': comp_print(*D); break;
            case 'E': comp_print(*E); break;
            case 'F': comp_print(*F); break;
        }
    } /* and so on for each of the commands in your assignment */
}

int main()
{
    complex A = {0, 0};
    complex B = {0, 0};
    complex C = {0, 0};
    complex D = {0, 0};
    complex E = {0, 0};
    complex F = {0, 0};

    char command[256];
    while (1) {
        printf("Enter command: ");
        fgets(command, sizeof(command), stdin);
        if (strncmp(command, "stop", 4) == 0) {
            break;
        }
        handle_command(command, &A, &B, &C, &D, &E, &F);
    }

    return 0;
}
