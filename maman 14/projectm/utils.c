#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "prototypes.h"
#include "assembler.h"
#include "ext_vars.h"
#include "utils.h"

unsigned int extract_bits(unsigned int word, int start, int end) {
    unsigned int mask = ((1 << (end - start + 1)) - 1) << start;
    return (word & mask) >> start;
}

char *convert_to_base_64(unsigned int num) {
    char *base64_seq = (char *) malloc(BASE64_WORD_LENGTH);
    if (!base64_seq) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(ERROR);
    }
    base64_seq[0] = base64[extract_bits(num, 6, 11)];
    base64_seq[1] = base64[extract_bits(num, 0, 5)];
    base64_seq[2] = '\0';
    return base64_seq;
}

boolean is_number(char *seq) {
    if (end_of_line(seq)) return FALSE;
    if (*seq == '+' || *seq == '-') {
        seq++;
        if (!isdigit(*seq++)) return FALSE;
    }
    while (!end_of_line(seq)) {
        if (!isdigit(*seq++)) return FALSE;
    }
    return TRUE;
}

boolean is_string(char *string) {
    if (!string || *string++ != '"') return FALSE;
    while (*string && *string != '"') string++;
    return (*string == '"' && *(string + 1) == '\0');
}

unsigned int insert_are(unsigned int info, int are) {
    return (info << BITS_IN_ARE) | are;
}

char *create_file_name(char *original, int type) {
    const char *extensions[] = {".as", ".ob", ".ent", ".ext"};
    char *modified = (char *) malloc(strlen(original) + MAX_EXTENSION_LENGTH);
    if (!modified) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(ERROR);
    }
    strcpy(modified, original);
    strcat(modified, extensions[type]);
    return modified;
}

void encode_to_instructions(unsigned int word) {
    instructions[ic++] = word;
}

int is_error() {
    return err != SUCCESS;
}

void write_error(int line_num) {
    const char *error_messages[] = {
        "first non-blank character must be a letter or a dot.",
        "label already exists.",
        "label is too long.",
        // ... [Add all the other error messages in the order of the error enum]
        "there was an error while trying to open the requested file."
    };

    fprintf(stderr, "ERROR (line %d): ", line_num);

    if (err >= 0 && err < sizeof(error_messages) / sizeof(error_messages[0])) {
        fprintf(stderr, "%s\n", error_messages[err]);
    }
}

char *next_list_token(char *dest, char *line) {
    char *temp = dest;
    if (end_of_line(line)) {
        dest[0] = '\0';
        return NULL;
    }
    line = skip_spaces(line);
    if (*line == ',') {
        strcpy(dest, ",");
        return ++line;
    }
    while (!end_of_line(line) && *line != ',' && !isspace(*line)) {
        *temp++ = *line++;
    }
    *temp = '\0';
    return line;
}

char *next_token_string(char *dest, char *line) {
    char temp[MAX_LINES];
    line = next_list_token(dest, line);
    if (*dest != '"') return line;
    while (!end_of_line(line) && dest[strlen(dest) - 1] != '"') {
        line = next_list_token(temp, line);
        if (line) strcat(dest, temp);
    }
    return line;
}

int end_of_line(char *line) {
    return line == NULL || *line == '\0' || *line == '\n';
}

char *next_token(char *seq) {
    if (seq == NULL) return NULL;
    while (!isspace(*seq) && !end_of_line(seq)) seq++;
    return skip_spaces(seq);
}

void copy_token(char *dest, char *line) {
    int i = 0;
    while (i < MAX_LINES && !isspace(line[i]) && line[i] != '\0') {
        dest[i] = line[i];
        i++;
    }
    dest[i] = '\0';
}

int find_index(char *token, const char *arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(token, arr[i]) == 0) return i;
    }
    return NOT_FOUND;
}

boolean is_register(char *token) {
    return strlen(token) == REGISTER_LENGTH && token[0] == 'r' && isdigit(token[1]);
}

boolean is_external(char *label) {
    return find_index(label, externs, extern_count) != NOT_FOUND;
}

int encode_number(int num, int are) {
    if (num < 0) {
        num = pow(2, WORD_LENGTH) + num;
    }
    return insert_are(num, are);
}

char *skip_spaces(char *line) {
    if (!line) return NULL;
    while (isspace(*line)) line++;
    return line;
}
