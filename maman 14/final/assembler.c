#include "util.h"
#include "globals.h"
#include "pre_processor_func.h"
#include "commands.h"
#include "data_handler.h"
#include "first_pass.h"
#include "second_pass.h"
#include "symbol_table.h"
#include "prints.h"

/* assembler gets file names through terminal and proccess them one at a time, assuming file name given with no extension */
int main (int totalArgs, char* argv[])
{
    int i;
    char* file_name; /* the file name as given as argument */
    bool pre_proccesor, first_pass, second_pass;

	if (totalArgs < 2)
	{
		printf("Usage: %s <filename> <filename> ...\n", argv[0]);
	}
	 /* Processing each file name argument */
    
    for (i = 1; i < totalArgs; i++) 
    {   
        gen_new_symbol_list();
        file_name = argv[i];
        if ((pre_proccesor = pre_processor_func(file_name)) == false)
        {
            printf("ERROR: pre pre_processor_func of %s failed.\n", file_name);
            release_list();
            clean_outputs(file_name);
            continue;
        }
        if ((first_pass = do_first_pass(file_name)) == false)
        {
            printf("ERROR: first pass of %s failed.\n", file_name);
            release_list();
            clean_outputs(file_name);
            continue;
        }
        if ((second_pass = secondPass(file_name)) == false)
        {
            printf("ERROR: second pass of %s failed.\n", file_name);
            release_list();
            clean_outputs(file_name);
            continue;
        }
        release_list();

        _objectOBJ(file_name);
    }

    return 0;
}
