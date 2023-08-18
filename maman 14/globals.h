#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* accroding to word size -  (2^12-1) to (2^12-1)-1 */
#define MAX_NUM 2047
#define MIN_NUM -2048

#define MAX_LINE_LEN 80
#define SYMBOL_MAX_NAME_SIZE 31
#define MACRO_MAX_NAME_SIZE 31
#define MEM_SIZE 1024

#define INITIAL_ADDRESS 100
#define IMAGE 0 /*code and data image place holder*/

/* define op_code enum */
typedef enum op_code {
    op_code_error = -1,
    mov = 0,
    cmp,
    add,
    sub,
    not,
    clr,
    lea,
    inc,
    dec,
    jmp,
    bne,
    red,
    prn,
    jsr,
    rts,
    stop
} op_code_type;

/* define bool type */
typedef enum bool_t {
    false = 0,
    true
} bool;

typedef enum a_r_e {
    unknown_addr = -1,
    absolute = 0,
    external = 1,
    realocatable = 2
} encoding_type;

/* define addressing type enum */
typedef enum address_t {
    adders_error = -1,
    no_addr = 0,
    imm_addr = 1,
    drct_addr = 3,
    reg_addr = 5
} addr_type;

/* machine word struct with all required parameters */
typedef struct macine_word {
    encoding_type encoding;
    addr_type dest;
    op_code_type op_code;
    addr_type source;
} machine_word;

typedef struct command_t {
    char command_name[5];
    op_code_type op_code;
    int num_of_operands;
} cmd;

typedef struct parameter_t {
    char param_name[SYMBOL_MAX_NAME_SIZE + 1];
    addr_type address;
} parameter;

#endif