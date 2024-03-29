#include "util.h"
#include "globals.h"
#include "preprocessor.h"
#include "commands.h"
#include "data_handler.h"
#include "first_pass.h"
#include "second_pass.h"
#include "symbol_table.h"
#include "prints.h"

/* The main function takes filenames from command-line arguments and processes each of them individually.
   The filenames should be given without extensions. */
int main(int totalArgs, char* args[]) {
    int index;
    char* file; /* File name given as a command-line argument */
    bool preprocess_status, pass1_status, pass2_status;

    if (totalArgs < 2) {
        printf("Usage: %s <filename> <filename> ...\n", args[0]);
        return 1; /* An error code is returned if the arguments are insufficient */
    }

    /* Each filename given is processed in this loop */
    for (index = 1; index < totalArgs; index++) {
        create_new_symbol_list();
        file = args[index];

        /* The file is preprocessed, and failure is checked */
        preprocess_status = preprocessor(file);
        if (!preprocess_status) {
            printf("ERROR: Preprocessing of %s failed.\n", file);
            free_list();
            removeOutputs(file);
            continue;
        }

        /* The first pass is performed on the file, and failure is checked */
        pass1_status = firstPass(file);
        if (!pass1_status) {
            printf("ERROR: First pass of %s failed.\n", file);
            free_list();
            removeOutputs(file);
            continue;
        }

        /* The second pass is performed on the file, and failure is checked */
        pass2_status = secondPass(file);
        if (!pass2_status) {
            printf("ERROR: Second pass of %s failed.\n", file);
            free_list();
            removeOutputs(file);
            continue;
        }

        free_list();

        /* The object file is printed */
        printOBJ(file);
    }

    return 0;
}
