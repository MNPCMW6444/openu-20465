#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "util.h"
#include "macroUnfold.h"

#define AS_EXTENSION ".as"

int main(int argCount, char* argValues[])
{
    char* inputFileName; 
    char* fullFileName; 

    if (argCount < 2)
    {
        printf("Usage: %s <filename> [<filename> ...]\n", argValues[0]);
        return 0;
    }

    for (int idx = 1; idx < argCount; ++idx) 
    {
        inputFileName = argValues[idx];
        fullFileName = argValues[idx];
        
        strcat(fullFileName, AS_EXTENSION);

        FILE* currentFile = fopen(fullFileName, "r+");
        if (!currentFile) 
        {
            printf("Error opening file: %s\n", inputFileName);
            continue;
        }

        FILE* amFile = macroUnfold(currentFile, inputFileName);
        fclose(currentFile);
    }

    return 0;
}
