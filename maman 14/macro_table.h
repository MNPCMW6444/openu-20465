#ifndef MACRO_TABLE_H
#define MACRO_TABLE_H

#include "util.h"
#include "globals.h"

/* Defines the HashTable item */
typedef struct Ht_item
{
    char* key;              /* The macro name */
    unsigned long hash_value; /* The hash value */
    char* text;             /* The macro content */
} macroItem;

/* Defines the HashTable */
typedef struct HashTable
{
    macroItem** items;
    int size;
    int count;
    int maxProbs;
} macroTable;

/* Creates a macro item */
macroItem* create_macro(const char* key, const char* text);

/* Creates a macro table */
macroTable* createMacroTable(int size);

/* Frees a macro table */
void freeMacroTable(macroTable* table);

/* Searches for a macro item in the table */
bool searchMacro(macroTable* table, char* macro_name);

/* return a pointer to an existing macro item */
macroItem* getMacro(macroTable* table, char* macro_name);

/* Inserts an item into the table */
void insertMacro(macroTable* table, macroItem* newItem);

#endif /* MACRO_TABLE_H */