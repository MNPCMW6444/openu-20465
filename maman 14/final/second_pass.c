#include "commands.h"
#include "data_handler.h"
#include "symbol_table.h"
#include "util.h"
#include "prints.h"

/* second_pass gets file name and reads through the .am file to update and finish the code image of it.
   if no errors found it returns true, else return false. */

bool secondPass(char* file_name)
{
	char line[MAX_LINE_LEN + 3];
	char* token = NULL, *file_nameExtended = str_allocate_cat (file_name, am_extension);
	bool success_flag = true;
	int instructions_counter = 0, current_line = 0;
	symbol_data* symbol = NULL;
	parameter first_param, second_param;
    cmd* current_cmd;
    FILE* file;

    if((file = fopen(file_nameExtended, "r")) == NULL)
    {
        printf("Failed to open file %s\n",file_name);
        free(file_nameExtended);
        return false; /* nothing to continue with */
    }

	while (fgets(line, MAX_LINE_LEN + 3, file) != NULL){
        current_line++;
        format_line(line);
		token = strtok(line, delims);

        if (token[strlen(token) - 1] == ':') /* has label */
            token = strtok(NULL, delims);

        if (token[0] == '.'){
            if (strcmp(token, ".entry") == 0){
                token = strtok(NULL, delims);
                if((symbol = find_symbol(token)) == NULL){
                    fprintf(stderr, "Line %d unable to find label %s",current_line,token);
                    success_flag = false;
                    continue;
                } else {
                    if (symbol->symbol.attribute == SYMBOL_EXTERN){
                        fprintf(stderr, "Line %d external label cannot be used in .entry",current_line);
                        success_flag = false;
                    } else {
                        write_entry_file(symbol->symbol, file_name);
                    }
                } 
            }
        } else {
            /* commands here */
            if((current_cmd = find_command(token)) == NULL){
                fprintf(stderr, "Line %d bad command,unable to process %s",current_line,token);
                success_flag = false;
                continue;
            }
            find_parameters(&first_param, &second_param);

            instructions_counter++; /* since already added memory word in first pass */
            switch (current_cmd -> num_of_operands){

                case 0:
                    if (first_param.address != no_addr){
                        fprintf(stderr, "Line %d cmd %s shouldnt receive parameters",current_line,current_cmd->command_name);
                        success_flag = false;
                    }
                    break;
                
                case 1:
                    if (first_param.address == no_addr || second_param.address != no_addr){
                        fprintf(stderr, "Line %d cmd %s should receive 1 parameter",current_line,current_cmd->command_name);
                        success_flag = false;
                    }
                    /* handling drct_addr access since have all the data now */
                    if (first_param.address == drct_addr)
                        if (!assemble_machine_word_with_single_param(first_param,false,instructions_counter,file_name))
                            success_flag = false;
                        instructions_counter++;
                    break;

                case 2:
                    if (first_param.address == no_addr || second_param.address == no_addr){
                        fprintf(stderr, "Line %d cmd %s should receive 2 parameter",current_line,current_cmd->command_name);
                        success_flag = false;
                    }
                    /* when both addressing types are register they share a single word */
                    if (first_param.address == reg_addr && second_param.address == reg_addr){
                        instructions_counter++;
                        continue;

                    } else { /* meaning 1 of the addressing type is not register addressing */
                        if (first_param.address != adders_error && second_param.address != adders_error){
                            if (first_param.address == drct_addr)
                                if (!assemble_machine_word_with_single_param(first_param,false,instructions_counter,file_name))
                                    success_flag = false;
                            instructions_counter++;
                            if (second_param.address == drct_addr)
                                if (!assemble_machine_word_with_single_param(second_param,false,instructions_counter,file_name))
                                    success_flag = false;
                            instructions_counter++;
                        }
                    }
                    break;
                
                default:
                    fprintf(stderr, "Line %d bad command,unable to process %s",current_line,token);
                    success_flag = false;
                    break;
            }
        }
	}
    free(file_nameExtended);
    fclose(file);

    return success_flag;
}