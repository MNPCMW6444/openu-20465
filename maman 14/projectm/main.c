   

/*
    Welcome to our assembler program!
    It was written according to the instructions in the Mamans' book.

    We have:
    -Global variables, including an error number (according to an enum in assembler.h).
    -Each file has its own description.
*/

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "prototypes.h"
#include "ext_vars.h"
#include "utils.h"

/* We define global variables here because they are defined as extern,
 * and therefore must be initialized in a specific C file.
 */

unsigned int data[MACHINE_RAM];
unsigned int instructions[MACHINE_RAM];
int ic;
int dc;
int err;
labelPtr symbols_table;
extPtr ext_list;
boolean entry_exists, extern_exists, was_error;

const char base64[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};


const char *commands[] = {
        "mov", "cmp", "add", "sub", "lea", "not", "clr", "inc", "dec", "jmp", "bne",
        "red", "prn", "jsr", "rts", "stop"
};

const char *directives[] = {
        ".data", ".string", ".entry", ".extern"
};

void reset_global_vars()
{
    symbols_table = NULL;
    ext_list = NULL;

    entry_exists = FALSE;
    extern_exists = FALSE;
    was_error = FALSE;
}

/* This function handles all activities in the program, it receives command line arguments for filenames */
int main(int argc, char *argv[]){
    int i;
    char *input_filename;
    FILE *fp;

    for(i = 1; i < argc; i++)
    {
        input_filename = create_file_name(argv[i], FILE_INPUT); /* Appending .as to filename */
        fp = fopen(input_filename, "r");
        if(fp != NULL) { /* If file exists */
            printf("************* Started %s assembling process *************\n\n", input_filename);

            reset_global_vars();
            first_pass(fp);

            if (!was_error) { /* procceed to second pass */
                rewind(fp);
                second_pass(fp, argv[i]);
            }

            printf("\n\n************* Finished %s assembling process *************\n\n", input_filename);
        }
        else write_error(CANNOT_OPEN_FILE);
        free(input_filename);
    }

	return 0;
}
