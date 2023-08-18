#ifndef COMMANDS_H
#define COMMANDS_H

#include "globals.h"

#define NUMBER_OF_COMMANDS 16
#define START_ADDRESS 100

int CODE_IMAGE[MEM_SIZE];

cmd* find_command(char*);

void assemble_machine_word(machine_word current_word, int inst_counter);

bool assemble_machine_word_with_single_param(parameter param, bool is_source, int inst_counter, char* file_name);

void assemble_machine_word_with_double_param(char* source, char* dest, int inst_counter);

void find_parameters(parameter* first_param, parameter* second_param);

int getIC();

void updateIC(int counter);

#endif