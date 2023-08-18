#include "commands.h"
#include "symbol_table.h"
#include "util.h"
#include "globals.h"
#include "prints.h"

/* Task: Add boundary checks for arrays (exceeding 1024) */
/* This data structure 'commands' is used to store and manage the code image */

int InstructionCounter = 0;
int CodeImage[MAX_DATA_SIZE] = {IMAGE_PH};

cmd CommandTable[CMD_SUM] = {
    {"mov", mov, 2},
    {"cmp", cmp, 2},
    {"add", add, 2},
    {"sub", sub, 2},
    {"not", not, 1},
    {"clr", clr, 1},
    {"lea", lea, 2},
    {"inc", inc, 1},
    {"dec", dec, 1},
    {"jmp", jmp, 1},
    {"bne", bne, 1},
    {"red", red, 1},
    {"prn", prn, 1},
    {"jsr", jsr, 1},
    {"rts", rts, 0},
    {"stop", stop, 0}
};

cmd* find_command(char* command_name){
    int index;
    for (index = 0; index < CMD_SUM; index++) {
        if (strcmp((CommandTable[index].command_name), command_name) == 0)
            return &CommandTable[index]; /* Command found at this point */
    }
    return NULL; /* Return NULL if no matching command is found */
}

/* Function to add a machine word as a decimal representation of a binary word */
void add_machine_word(machine_word current_word, int InstructionCount) {
    int word_location = InstructionCount + START_ADDRESS;
    int assembled_word = current_word.source; /* Slots 11-9 */
    assembled_word = (assembled_word << 4) + current_word.op_code;  /* Slots 8-5 */
    assembled_word = (assembled_word << 3) + current_word.dest; /* Slots 4-2 */
    assembled_word = (assembled_word << 2); /* Slots 1-0 as encoding is always 00 */
    CodeImage[word_location] = assembled_word;
}

/* Handling single parameter case for register addressing; requires bool flag to determine which bits to flag */
bool add_extra_word_single_param(parameter param, bool is_source, int InstructionCount, char* file_name) {
    int word_location = InstructionCount + START_ADDRESS;
    int new_number;
    symbol_data* symbol_info;
    if (param.address == register_addressing) {
        new_number = param.param_name[2] - '0'; /* Extract register number */
        new_number = is_source ? new_number << 7 : new_number << 2;
        CodeImage[word_location] = new_number;
    } else if (param.address == immediate_addressing) {
        new_number = convert_to_int(param.param_name);
        if (new_number == INT_MIN) {
            return false;
        }
        new_number <<= 2; /* Accommodate for 00 */
        CodeImage[word_location] = new_number;
    } else if (param.address == direct_addressing) {
        /* Handling in second pass needs to be done */
        if ((symbol_info = find_symbol(param.param_name)) == NULL) {
            fprintf(stderr, "ERROR in %s: Unable to locate label %s in add_extra_word_single_param\n", file_name, param.param_name);
            return false;
        }
        new_number = symbol_info->symbol.value;
        if (symbol_info->symbol.attribute == SYMBOL_EXTERN) {
            new_number = (new_number << 2) + external; /* For external labels, add constant for bits 1-0 location */
            write_external_file(symbol_info->symbol.name, word_location, file_name);
        } else {
            /* For non-external labels, mark label for relocation; add constant for bits 1-0 location */
            new_number = (new_number << 2) + realocatable;
        }
        CodeImage[word_location] = new_number;
    }
    return true;
}

/* Handling the case when both operands are registers and share the word */
void add_extra_word_double_param(char* source, char* destination, int InstructionCount) {
    int word_location = InstructionCount + START_ADDRESS;
    int new_number = source[2] - '0'; /* Set first 5 digits 11-7 */
    int reg_second = destination[2] - '0';
    new_number = (new_number << 5) + reg_second; /* Shift 5 for next 5 digits 6-1 */
    new_number <<= 2; /* Last shift of 2 to set in place, always 00 in digits 1-0 */
    CodeImage[word_location] = new_number;
}

void extract_params(parameter* param1, parameter* param2) {
    char* parsed_token;
    int converted_number;
    bool comma_present = false;

    /* Clear previous parameter names, indicating there are no addressing parameters following the command */
    memset(param1->param_name, 0, strlen(param1->param_name));
    memset(param2->param_name, 0, strlen(param2->param_name));
    param1->address = addr_error;
    param2->address = addr_error;

    if ((parsed_token = strtok(NULL, delims)) == NULL) {
        param1->address = no_addressing;
        param2->address = no_addressing;
        return;
    }
    strcpy(param1->param_name, parsed_token);
    if (is_register(parsed_token)) {
        param1->address = register_addressing;
    } else { /* It could be a label or an immediate value */
        /* Labels must start with a character */
        if (isalpha(parsed_token[0])) {
            if (isReservedWord(parsed_token)) {
                fprintf(stderr, "Label reference %s must not be a reserved word in extract_params\n", parsed_token);
                return;
            }
            param1->address = direct_addressing;
        } else { /* It starts with a number, so it's an immediate value */
            converted_number = convert_to_int(parsed_token);
            if (converted_number == INT_MIN) {
                return;
            }
            param1->address = immediate_addressing;
        }
    }
    
    /* A comma must follow the first parameter */
    if ((parsed_token = strtok(NULL, delims)) == NULL || *parsed_token == ',') {
        param2->address = no_addressing;
        comma_present = true;
    }
    /* Conduct the same validation as the first parameter but for the second parameter */
    if ((parsed_token = strtok(NULL, delims)) == NULL) {
        param2->address = no_addressing;
        return;
    }
    if (!comma_present) {
        fprintf(stderr, "A comma is missing after the first parameter %s; extract_params requires a comma\n", param1->param_name);
        return;
    }
    strcpy(param2->param_name, parsed_token);
    if (is_register(parsed_token)) {
        param2->address = register_addressing;
    } else { /* It could be a label or an immediate value */
        /* Labels must start with a character */
        if (isalpha(parsed_token[0])) {
            if (isReservedWord(parsed_token)) {
                fprintf(stderr, "Label reference %s must not be a reserved word in extract_params\n", parsed_token);
                return;
            }
            param2->address = direct_addressing;
        } else { /* It starts with a number, so it's an immediate value */
            converted_number = convert_to_int(parsed_token);
            if (converted_number == INT_MIN)
                return;
            param2->address = immediate_addressing;
        }
    }
    /* Check if there's any extra text after the second parameter */
    if ((parsed_token = strtok(NULL, delims)) != NULL) {
        fprintf(stderr, "Additional text found after the second parameter %s\n", param2->param_name);
    }
}


int getInstructionCounter() {
    return InstructionCounter;
}

void addInstructionCounter(int counter) {
    InstructionCounter = counter;
}
