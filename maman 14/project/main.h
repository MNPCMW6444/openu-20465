#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "data_types.h"


void stageOne(char *fileName);
void handleDataLine(int hasLabel, char *labelName);
void handleStringLine(char *labelName, int lineNumber);
void handleStructLine(char *labelName, int lineNumber);
void handleExternLine(char *labelName, int lineNumber);
void handleEntryLine(char *labelName, int lineNumber);
void handleCommandLine(int hasLabel, char * token, char *labelName, int lineNumber);

void stageTwo(char *fileName);
void printToObFile(char *fileName);
void printToFile(list *head, FILE *outputFile);
void printToExt(char *fileName, list* head, char *type);
void printToEnt(char *fileName , list* head, list* headEnt);

void translateOpCode(char *cmd, int *output, int lineNumber);
void translateRegister(char *val, char mode[], int *output, int lineNumber);
void translateMethod(char *val, char * mode, int *output, int lineNumber);
void translateImmediate(char *val, int *output);
void translateCommand(char *currentToken, char *labelName, int lineNumber);
int needsNoOperands(char * commandName);
int needsTwoOperands(char * commandName);
void translateNoOperands(char * commandName,char *token, int lineNumber);
void translateOneOperand(char * commandName, char *token, char *labelName,char * arg1, int lineNumber);
void translateTwoOperands(char * commandName,char *token, char *labelName,char * arg1, char * arg2, int lineNumber);

int isLabel(char val[], int withColon);
int isLabelExists(char *label, list *headlabel, int external);
int isRegister(char *val);
int isImmediate(char *val);
int isNumber(char *val);
void addToList(list **headCode, char *label, int number, char *val, int adrress);
void clearList(list **headCode);
int getStructNumber(char *val);
char * getLabelStruct(char *val);
int isStruct(char *val);
int getMethodNumber(char *val);
void removeMacros(char *filename, char *amFileName);
void updateListAddress(list **head, int offset, int labelList);
void updateLabelAddress(list **headCode,list *headlabel);
void updateExt(list **head, list *headext);




