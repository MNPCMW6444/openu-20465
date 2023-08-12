   

#include "structs.h"
#include "assembler.h"

#define MACHINE_RAM 1024

extern int ic, dc;
extern int err;
extern boolean was_error;
extern labelPtr symbols_table;
extern extPtr ext_list;
extern const char base64[64];
extern const char *commands[];
extern const char *directives[];
extern boolean entry_exists, extern_exists;
