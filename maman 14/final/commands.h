#ifndef COMMANDS_H
#define COMMANDS_H

#include "globals.h"

#define CMD_SUM 16
#define START_ADDRESS 100

int CODE_IMG[MAX_DATA_SIZE];

cmd* find_command(char*);

void add_machine_word(machine_word current_word, int IC);

bool add_extra_word_single_param(parameter param, bool is_source, int IC, char* fileName);

void add_extra_word_double_param(char* source, char* dest, int IC);

void extract_params(parameter* first_param, parameter* second_param);

int getInstructionCounter();

void addInstructionCounter(int counter);

#endif