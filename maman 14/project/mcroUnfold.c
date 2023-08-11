#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "util.h"
#include "macro_table.h"
#define MAX_LINE_LEN 80 /*todo add to globals*/

/* first read: count how many macros to initialize an efficient table, check rows don't excced 80 chars, and macro names are legal
   second read: copy content to .am file, insert and unfold macros, get rid of comment and empty lines*/

FILE* macroUnfold(FILE* file, char* fileName)
{
    char* am_extension = ".am";/*todo add to globals*/
    bool openMacro = false, addMacro = false; /* flags for macro handling */
    bool skip = true; /* for printing loop */
    int counter = 0, macroLength = 0, nameLength = 0, currentLine = 1;  /* counters for macro amount and length */
    macroTable* MACROS = NULL;
    macroItem* newMacro = NULL; /* pointer to handle macro items */
    char *token = NULL, *macroContent = NULL, *macroName = NULL;
    char line[MAX_LINE_LEN+2];
    char* outputFileName = str_allocate_cat(fileName, am_extension); /* file name argument comes with no proper extension, fix it before open file */

    FILE* outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL)
    {
        printf("Failed to open file: %s\n", outputFileName);
    }

    /* (1) the loop below counts the amount of macros in the file to initialize an efficient table */
    while (fgets(line, MAX_LINE_LEN+2, file) != NULL)
    {
        /* ignore comment and empty lines */
        if (lineToIgnore(line)) 
        {
            currentLine++;
            continue;
        }

        /* if none of the chars is '\n' meaning the line in origin file excceed 80 chars */
        char* lengthTest = strchr(line, '\n');
        if (lengthTest == NULL)
        {
            printf("ERROR: Excceeding max length of line at line: %d\n", currentLine);
        }
        lengthTest = NULL;

        token = strtok(line, delims);
        while (token != NULL)
        {
            if (addMacro)
            {
                if (isReservedWord(token))
                {
                    printf("ERROR:at line %d Macro name is illegal (%s is a reserved word)\n", currentLine, token);
                    exit(0);
                }
                counter++;
                addMacro = false;
            }
            else if (strcmp(token, "mcro") == 0)
            {
                addMacro = true;
            }

            token = strtok(NULL, delims);
        }
        currentLine++;
    }
    rewind(file);
    currentLine = 1;

    /* if macro found then create a table for macros and unfold (loop 2 and 3) */
    if (counter > 0) 
    {
        MACROS = createMacroTable(counter);
    }
    /* (2) the loop below read the file and insert new macros to the hash table */
    while (fgets(line, MAX_LINE_LEN + 2, file) != NULL)
    {
        if (lineToIgnore(line))
        {
            currentLine++;
            skip = true;
            continue;
        }

        token = strtok(line, delims);
        while (token != NULL)
        {
            if (counter > 0 && (newMacro = getMacro(MACROS, token)) != NULL)
            {
                fprintf(outputFile, "%s", newMacro->text);
                skip = false;
                token = strtok(NULL, delims);
            }
            else
            /* endmcro: submit the contnet in and reset the string*/
            if ((strcmp(token, "endmcro") == 0) && counter > 0)
            {
                macroContent[strlen(macroContent) - 1] = '\0';
                newMacro = createMacro(macroName, macroContent);
                insertMacro(MACROS, newMacro);
                openMacro = false;
                free(macroName);
                macroName = NULL;
                free(macroContent);
                macroContent = NULL;
                newMacro = NULL;
                macroLength = 0;
                skip = true;
                token = strtok(NULL, delims);
            }
            else
            /* openMacro: add new words to content buffer*/
            if (openMacro && counter > 0)
            {
                macroLength = macroLength + strlen(token) + 2;
                if (macroContent == NULL) /* condtion for new macro content */
                {
                    macroContent = (char*)malloc(macroLength * sizeof(char));
                    if (macroContent == NULL)
                    {
                        printf("macroContent memory allocation failed\n");
                        exit(0);
                    }
                    strcpy(macroContent, token);
                    strcat(macroContent, " ");
                    skip = true;
                    token = strtok(NULL, delims);
                }
                else /* add to an existing macro content */
                {
                    macroContent = realloc(macroContent, macroLength * sizeof(char));
                    if (macroContent == NULL)
                    {
                        printf("macroContent memory allocation failed\n");
                        exit(0);
                    }
                    strcat(macroContent, token);
                    strcat(macroContent, " ");
                    skip = true;
                    token = strtok(NULL, delims);
                }
            }
            else
            /* encounterd 'mcro' last iteration: look up in the table, if exist - error, else insert */
            if (addMacro && counter > 0)
            {
                if (searchMacro(MACROS, token))
                {
                    printf("ERROR: in line %d macro name \"%s\" already exist!\n", currentLine, token);
                    exit(0);
                }
                else
                {
                    nameLength = strlen(token) + 1;
                    macroName = (char*)malloc(nameLength * sizeof(char));
                    strcpy(macroName, token);
                    openMacro = true; /*flag for next iterations to gather macro content*/
                    addMacro = false;
                    skip = true;
                    token = strtok(NULL, delims);
                }
            }
            else
            /* mcro declared, flag up for next iteration to consume it*/
            if ((strcmp(token, "mcro") == 0) && counter > 0)
            {
                addMacro = true;
                skip = true;
                token = strtok(NULL, delims);
            }
            /* no macro handling - copy paste to new file */
            else
            {
                fprintf(outputFile, "%s%s", token, " ");
                skip = false;
                token = strtok(NULL, delims);
            }
        }

        currentLine++;
        if (openMacro && counter > 0 && macroContent != NULL)
        {
                strcat(macroContent, "\n");
        }
        else
        if(!skip)
        {
            fprintf(outputFile, "%s", "\n");
        }
    }

    if (counter > 0)
    {
        freeMacroTable(MACROS);
    }
    free(outputFileName);
    return outputFile;
}

int main(int argc, char* argv[])
{
    char* fileName; /* the file name as given as argument */
    char* fileNameToOpen = NULL; /* modified with .as */
    char* as_extension = ".as";

    if (argc < 2)
    {
        printf("Usage: %s <filename> <filename> ...\n", argv[0]);
    }
    /* Processing each file name argument */
    for (int i = 1; i < argc; i++)
    {
        fileName = argv[i];
        fileNameToOpen = str_allocate_cat(fileName, as_extension);
        FILE* file = fopen(fileNameToOpen, "r+");

        if (file == NULL)
        {
            printf("Failed to open file: %s\n", fileName);
            free(fileNameToOpen);
            fileNameToOpen = NULL;
            continue; /* Move on to the next file */
        }

        FILE* amOutputFile = macroUnfold(file, fileName); /* unfold macros, return new file with .am extension */
        free(fileNameToOpen);
        fileNameToOpen = NULL;
        fclose(file);
        fclose(amOutputFile);
    }

    return 0;
}