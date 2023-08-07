#include "main.h"

int DC = 0;
int IC = BASE_MEM_ADDR;
int ICF;
int DCF;
int hasLabel;
int errors = 0;
list *codeList;
list *dataList;
list *labelList;
list *entList;

/*stage one, pass first time on file*/
void stageOne(char *fileName)
{
    FILE *file;
	char *token;
	char *labelName;
	char line[MAX_LINE];
	int lineNumber = 0;
	file = fopen(fileName, "r");
	
	/* read file line by line*/	
	while (fgets(line, MAX_LINE, file) != NULL)
	{
	    hasLabel = 0;
		lineNumber++;
		
		/*read lines first word*/
		token = strtok(line, CMD_LINE_SEPARATORS);
		/* if it is not a comment */
		if (token != NULL && token[0] != ';')
		{
		    /* the line begins with label */
			if (((isLabel(token, 1)) == 1)) 
			{
			    /*label exists already */
				if (isLabelExists(token, labelList, 0) == 1) 
				{
					/* error: label already exists */
					printf("Line:%d  label already exists\n" , lineNumber);
					errors = 1;
					continue;
				}
				else
				{
					hasLabel = 1;
					labelName = token;
		            token = strtok(NULL, CMD_LINE_SEPARATORS);
				}
			}
			
			/* the line continue with data */	
			if (strcmp(token, DATA_DIRECTIVE) == 0) 
			{
                handleDataLine(hasLabel, labelName);
			}
			
			/* the line continue with string */		
			else if (strcmp(token, STRING_DIRECTIVE) == 0) 
			{
			    handleStringLine(labelName, lineNumber);		
			}
			/* the line continue with struct */
			else if (strcmp(token, STRUCT_DIRECTIVE) == 0) 
			{
                handleStructLine(labelName, lineNumber);
			}
			/* the line begins with extern */
			else if (strcmp(token, EXTERN_DIRECTIVE) == 0) 
			{
                handleExternLine(labelName, lineNumber);
			}
			/* the line begins with entry */
			else if (strcmp(token, ENTRY_DIRECTIVE) == 0) 
			{
			    handleEntryLine(labelName, lineNumber);
			}
			else /* the line continue with command */
			{
                handleCommandLine(hasLabel, token, labelName, lineNumber);
			}
			}
	}
	fclose(file);
	ICF = IC;
	DCF = DC;
	/*change the address for data code to the correct address*/
	updateListAddress(&dataList, ICF, 0);
	/*update the address of the labels in listlabel*/
	updateListAddress(&labelList, ICF, 1);
}

void handleDataLine(int hasLabel, char *labelName)
{
                    char *strtolEnd;
    				char * token = strtok(NULL, CMD_LINE_SEPARATORS);
					int strtolInt = strtol(token, &strtolEnd, 10);
					

					if(hasLabel == 1)
					{
						addToList(&dataList , labelName, strtolInt, "d", DC);
						addToList(&labelList, labelName, 0, "data", DC); 
					}
					else
					{
						addToList(&dataList , NULL, strtolInt, "d", DC);
					}
					++DC;

					token = strtok(NULL, CMD_LINE_SEPARATORS);
						
					while (token != NULL)
					{
						strtolInt = strtol(token, &strtolEnd, 10);
						addToList(&dataList, NULL, strtolInt, "d", DC);
						token = strtok(NULL, CMD_LINE_SEPARATORS);

						++DC;
						}
}


void handleStringLine(char *labelName, int lineNumber)
{
                        char *token = strtok(NULL, CMD_LINE_SEPARATORS);
						int tokenLen = strlen(token);
						int i;
						if ((token[0] == '"') && (token[tokenLen-1] == '"'))
						{
							/*add first char and label*/
							int curChar = token[1];
							if(hasLabel == 1)
							{
								addToList(&dataList , labelName, (int)curChar, "d", DC);
								addToList(&labelList, labelName, 0, "data", DC); 
							}
							else
							{
								addToList(&dataList , NULL, (int)curChar, "d", DC);
							}
							++DC;

							/* add the string */
							for (i = 2; i < tokenLen-1; ++i)
							{
								curChar = token[i];
								addToList(&dataList, "", (int)curChar, "d", DC);
								++DC; 
							}
							/*put '\0' at the end*/
							addToList(&dataList, "", 0, "d", DC);
							++DC; 
						}
						else
						{
							printf("Line:%d  missing quates\n" , lineNumber);
							errors = 1;
						}    
}

void handleStructLine(char *labelName, int lineNumber)
{
                    char *token = strtok(NULL, CMD_LINE_SEPARATORS);
					int tokenLen;
					char *strtolEnd;
					int i;
					int strtolInt = strtol(token, &strtolEnd, 10);

					if(hasLabel == 1)
					{
						addToList(&dataList , labelName, strtolInt, "d", DC);
						addToList(&labelList, labelName, 0, "data", DC); 
					}
					else
					{
						addToList(&dataList , NULL, strtolInt, "d", DC);
					}
					++DC;
					
					
						token = strtok(NULL, CMD_LINE_SEPARATORS);
						tokenLen = strlen(token);
						
						if ((token[0] == '"') && (token[tokenLen-1] == '"'))
						{
							/*add first char and label*/
							int curChar = token[1];
							addToList(&dataList , NULL, (int)curChar, "d", DC);
							++DC;

							/* add the string */
							for (i = 2; i < tokenLen-1; ++i)
							{
								curChar = token[i];
								addToList(&dataList, "", (int)curChar, "d", DC);
								++DC; 
							}
							/*put '\0' at the end*/
							addToList(&dataList, "", 0, "d", DC);
							++DC; 
						}
						else
						{
							printf("Line:%d  missing quates\n" , lineNumber);
							errors = 1;
						}
}

void handleExternLine(char *labelName, int lineNumber)
{
    			char *	token = strtok(NULL, CMD_LINE_SEPARATORS);
				if ((isLabel(token, 0)) == 1)
				{
					if (isLabelExists(token, labelList, 1) == 1) /*label appeared earlier in code */
					{
						/* error: label already defined */
						printf("Line:%d  label already defined as non external\n" , lineNumber);
					    errors = 1;
					}
					else
					{
						addToList(&labelList, token, 0, "external", 0);

					}
				}
				else{
				    	/* error: label not leagal */
						printf("Line:%d  label not leagal\n" , lineNumber);
					    errors = 1;
				}
}

void handleEntryLine(char *labelName, int lineNumber)
{
    			char * token = strtok(NULL, CMD_LINE_SEPARATORS);
				if ((isLabel(token, 0)) == 1)
				{
				    addToList(&entList, token, 0, "entry", 0);
				}
}

void handleCommandLine(int hasLabel, char * token, char *labelName, int lineNumber)
{
    					if(hasLabel == 1)
						{
							addToList(&labelList, labelName, 0, "code", IC); 
							translateCommand(token,labelName, lineNumber);
						}
						else
						{
							translateCommand(token, NULL, lineNumber);
						}
}
