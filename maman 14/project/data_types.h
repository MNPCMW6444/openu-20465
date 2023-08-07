#include <stdlib.h>
#include <inttypes.h>

#define AS_EXT ".as"
#define AM_EXT ".am"
#define OB_EXT ".ob"
#define EXT_EXT ".ext"
#define ENT_EXT ".ent"


#define BASE_MEM_ADDR 100
#define MAX_LINE 80
#define STRING_DIRECTIVE ".string"
#define DATA_DIRECTIVE ".data"
#define ENTRY_DIRECTIVE ".entry"
#define EXTERN_DIRECTIVE ".extern"
#define STRUCT_DIRECTIVE ".struct"
#define MACRO_BEGIN_DIRECTIVE "macro"
#define MACRO_END_DIRECTIVE "endmacro"
#define SOURCE "source"
#define DST "destination"



#define SPECIAL_BASE32_STR "!@#$%^&*<>abcdefghijklmnopqrstuv"
#define OP_BITS 6
#define IMMEDIATE_BITS 2
#define MAX_IMMEDIATE 1023
#define SOURCE_METHOD_BITS 4
#define DST_METHOD_BITS 2
#define STRUCT_DELIM "."
#define STRUCT_SEPARATORS " \t\n"
#define CMD_LINE_SEPARATORS "\t\n, \r"
#define REGISTER_CHAR 'r'
#define REGISTER_MIN '0'
#define REGISTER_MAX '7'
#define IMMEDIATE_CHAR '#'


typedef struct list{
	char name[255];
	unsigned int address;
	char type[255];
    int num; 
    struct list *next;
}list;
