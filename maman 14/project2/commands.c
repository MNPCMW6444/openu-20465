#include "commands.h"
#include "symbol_table.h"
#include "util.h"

int CODE_IMG[MAX_DATA_SIZE];

typedef struct {
    char *name;
    void (*action)();
    int params;
} Command;

Command CommandTable[CMD_SUM] = {
    {"mov", mov, 2}, {"cmp", cmp, 2}, {"add", add, 2},
    {"sub", sub, 2}, {"not", not, 1}, {"clr", clr, 1},
    {"lea", lea, 2}, {"inc", inc, 1}, {"dec", dec, 1},
    {"jmp", jmp, 1}, {"bne", bne, 1}, {"red", red, 1},
    {"prn", prn, 1}, {"jsr", jsr, 1}, {"rts", rts, 0},
    {"stop", stop, 0}
};

Command *lookupCommand(char *name) {
    for (int i = 0; i < CMD_SUM; i++) {
        if (!strcmp(CommandTable[i].name, name)) return &CommandTable[i];
    }
    return NULL;
}

void addWordToMachineImg(machine_word word, int IC) {
    int loc = IC + START_ADDRESS;
    int finalWord = word.source << 4 | word.op_code << 3 | word.dest;
    CODE_IMG[loc] = finalWord;
}

bool appendExtraWordSingleParam(parameter p, bool isSrc, int IC) {
    int loc = IC + START_ADDRESS;
    char *end;
    int num;
    symbol_data *sym;

    if (p.address == register_addressing) {
        num = p.param_name[2] - '0';
        CODE_IMG[loc] = isSrc ? num << 7 : num << 2;
    } else if (p.address == immediate) {
        num = strtol(p.param_name, &end, 10);
        if (*end) {
            fprintf(stderr, "Line %d: %s conversion error. Got %d.", current_line, p.param_name, num);
            return false;
        }
        if (num > MAX_NUMBER || num < MIN_NUMBER) {
            fprintf(stderr, "Line %d: Number %d out of range. Max: %d, Min: %d.", current_line, num, MAX_NUMBER, MIN_NUMBER);
            return false;
        }
        CODE_IMG[loc] = num << 2;
    } else if (p.address == direct_addressing) {
        if (!(sym = find_symbol(p.param_name))) {
            fprintf(stderr, "Line %d: Label %s not found.", current_line, p.param_name);
            return false;
        }
        num = sym->symbol.value;
        if (sym->symbol.attribute == SYMBOL_EXTERN) {
            write_external_file(sym->symbol.name, loc);
            num = num << 2 | external;
        } else {
            num = num << 2 | realocatable;
        }
    }
    return true;
}

void appendExtraWordDoubleParam(char *src, char *dst, int IC) {
    int loc = IC + START_ADDRESS;
    int num = (src[2] - '0') << 5 | (dst[2] - '0');
    CODE_IMG[loc] = num << 2;
}

void extractParameters(parameter p1, parameter p2) {
    char *tk;
    char *end;
    int
