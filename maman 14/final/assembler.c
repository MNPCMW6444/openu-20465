#include "util.h"
#include "globals.h"
#include "preprocessor.h"
#include "commands.h"
#include "data_handler.h"
#include "first_pass.h"
#include "second_pass.h"
#include "symbol_table.h"
#include "prints.h"

/* Main function that reads filenames from the command line arguments
   and processes each file separately. Filenames are assumed to be provided without extensions. */
int main(int argc, char* argv[]) {
    int i;
    char* fileName; /* Filename passed as a command-line argument */
    bool pre_proccesor, first_pass, second_pass;

    if (argc < 2) {
        printf("Usage: %s <filename> <filename> ...\n", argv[0]);
        return 1; /* Return an error code if not enough arguments are provided */
    }

    /* Iterate through each provided filename and process it */
    for (i = 1; i < argc; i++) {
        create_new_symbol_list();
        fileName = argv[i];

        /* Preprocess the file and check for failure */
        pre_proccesor = preprocessor(fileName);
        if (!pre_proccesor) {
            printf("ERROR: Preprocessor of %s failed.\n", fileName);
            free_list();
            removeOutputs(fileName);
            continue;
        }

        /* Run the first pass on the file and check for failure */
        first_pass = firstPass(fileName);
        if (!first_pass) {
            printf("ERROR: First pass of %s failed.\n", fileName);
            free_list();
            removeOutputs(fileName);
            continue;
        }

        /* Run the second pass on the file and check for failure */
        second_pass = secondPass(fileName);
        if (!second_pass) {
            printf("ERROR: Second pass of %s failed.\n", fileName);
            free_list();
            removeOutputs(fileName);
            continue;
        }

        free_list();

        /* Print the object file */
        printOBJ(fileName);
    }

    return 0;
}
