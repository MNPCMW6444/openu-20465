/*****************************************
    Michael Michael, Michael Michael
*****************************************/

/*
    This file contains constants and enums that are used all over the program.
*/

#ifndef ASSEMBLER_H

#define ASSEMBLER_H

/**************************************** Defaults ****************************************/

#define MEMORY_START 100
#define EMPTY_WORD 0
#define EXTERNAL_DEFAULT_ADDRESS 0
#define NOT_FOUND -1
#define SUCCESS 0
#define ERROR 1

/**************************************** Limitations ****************************************/


#define MAX_LINES 80 /* maximum chars per line */
#define MINIMUM_LABEL_LENGTH_WITH_COLON 2
#define MINIMUM_LABEL_LENGTH_WITHOUT_COLON 1
#define LABEL_LENGTH 30 /* maximum chars per label */

#define MAX_COMMAND_LENGTH 4 /* maximum number of characters in a command */
#define MIN_COMMAND_LENGTH 3 /* minimum number of characters in a command */

#define REGISTER_LENGTH 3 /* a register's name contains 3 characters */
#define MIN_REGISTER 0    /* r0 is the first register */
#define MAX_REGISTER 7    /* r7 is the last register */

#define MAX_EXTENSION_LENGTH 5

#define BASE64_WORD_LENGTH 3 /* A base64 sequence of a word consists of 2 chars (and '\0' ending) */

/**************************************** Other Constants ****************************************/

#define NUM_DIRECTIVES 4 /* number of existing directives*/
#define NUM_COMMANDS 16  /* number of existing commands */

/* Bit-related info */
#define BITS_IN_WORD 12
#define BITS_IN_OPCODE 4
#define BITS_IN_METHOD 3
#define BITS_IN_ARE 2
#define BITS_IN_REGISTER 12

/* Addressing methods bits location in the first word of a command */
#define SRC_METHOD_START_POS 9
#define SRC_METHOD_END_POS 11
#define DEST_METHOD_START_POS 2
#define DEST_METHOD_END_POS 4

#define MACHINE_RAM 1024

/**************************************** Enums ****************************************/

/* Directives types */
enum directives
{
    DATA,
    STRING,
    ENTRY,
    EXTERN,
    UNKNOWN_DIRECTIVE
};

/* Enum of commands ordered by their opcode */
enum commands
{
    MOV,
    CMP,
    ADD,
    SUB,
    NOT,
    CLR,
    LEA,
    INC,
    DEC,
    JMP,
    BNE,
    RED,
    PRN,
    JSR,
    RTS,
    STOP,
    UNKNOWN_COMMAND
};

/* Enum of all errors that can be outputted */
enum errors
{
    SYNTAX_ERR = 1,
    LABEL_ALREADY_EXISTS,
    LABEL_TOO_LONG,
    LABEL_INVALID_FIRST_CHAR,
    LABEL_ONLY_ALPHANUMERIC,
    LABEL_CANT_BE_COMMAND,
    LABEL_ONLY,
    LABEL_CANT_BE_REGISTER,
    DIRECTIVE_NO_PARAMS,
    DIRECTIVE_INVALID_NUM_PARAMS,
    DATA_COMMAS_IN_A_ROW,
    DATA_EXPECTED_NUM,
    DATA_EXPECTED_COMMA_AFTER_NUM,
    DATA_UNEXPECTED_COMMA,
    STRING_TOO_MANY_OPERANDS,
    STRING_OPERAND_NOT_VALID,
    STRUCT_EXPECTED_STRING,
    STRUCT_INVALID_STRING,
    EXPECTED_COMMA_BETWEEN_OPERANDS,
    STRUCT_INVALID_NUM,
    STRUCT_TOO_MANY_OPERANDS,
    EXTERN_NO_LABEL,
    EXTERN_INVALID_LABEL,
    EXTERN_TOO_MANY_OPERANDS,
    COMMAND_NOT_FOUND,
    COMMAND_UNEXPECTED_CHAR,
    COMMAND_TOO_MANY_OPERANDS,
    COMMAND_INVALID_METHOD,
    COMMAND_INVALID_NUMBER_OF_OPERANDS,
    COMMAND_INVALID_OPERANDS_METHODS,
    ENTRY_LABEL_DOES_NOT_EXIST,
    ENTRY_CANT_BE_EXTERN,
    COMMAND_LABEL_DOES_NOT_EXIST,
    CANNOT_OPEN_FILE
};

/* When we need to specify if label should contain a colon or not */
enum
{
    NO_COLON,
    COLON
};

/* Addressing methods ordered by their code */
enum methods
{
    METHOD_IMMEDIATE = 1,
    METHOD_DIRECT = 3,
    METHOD_REGISTER = 5,
    METHOD_UNKNOWN
};

/* A/R/E modes ordered by their numerical value */
enum ARE
{
    ABSOLUTE,
    EXTERNAL,
    RELOCATABLE
};

/* Types of files that indicate what is the desirable file extension */
enum filetypes
{
    FILE_INPUT,
    FILE_OBJECT,
    FILE_ENTRY,
    FILE_EXTERN
};

#endif
