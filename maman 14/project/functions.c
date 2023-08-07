#include "main.h"
list* codeList;
list* dataList;
list* labelList;
list* extList;
list* entList;
list *macroList;
int errors;


int isLabel(char *val, int withColon)
{
	/* in declaration withColon is 1, in use it is 0*/
	int length = strlen(val);
	int i;

    /* label must start with alphabet char*/
	if ((isalpha(val[0]))) 
	{
		if(withColon)
		{
			length = length -1;
		}
		for(i =0; i < length; i++)
		{
		    /* label contains non alphanumeric character- not legal label*/
			if ((isalpha(val[i])) == 0 && (isdigit(val[i])) == 0) 
				return 0;
		}
		/* if it  has colon is 1 but no colon, then it is extern and not label*/
		if ((withColon == 1 && val[length] == ':') || withColon == 0 ) 
		{
			return 1;
		}
	}	
	
	return 0;
}


int isLabelExists(char *label,  list *headLabelList, int external)
{
	list* pntList;
	for (pntList = (headLabelList); pntList; pntList = pntList->next)
	{
		if (strcmp(pntList->name, label) == 0)
		    if(external == 0 || (external == 1 && strcmp(pntList->type, "exteral") == 1))
			        return 1;  
	}
	return 0;
}

int isRegister(char *val)
{
  	char * number = malloc(strlen(val)-1);
	strcpy(number, val+1);
	int regNumber = atoi(number);
	/* if starts with r and number is 0-7 */
	if(val[0] == REGISTER_CHAR && regNumber >= REGISTER_MIN && regNumber<= REGISTER_MAX)
	{
		return 1;
	}
	
	return 0;
}

int isImmediate(char *val)
{
    char * number = malloc(strlen(val)-1);
	strcpy(number, val+1);
	if(isNumber(number)==0)
	    return 0;
	if(val[0] == IMMEDIATE_CHAR)
	{
		return 1;
	}
	
	return 0;
	
}

int isNumber(char *val)
{
    int length = strlen(val);
    int i;
    if(val[0] != '-' && isdigit(val[0]) == 0)
        return 0;
    for(i =1; i < length; i++)
    {
        if(isdigit(val[i]) == 0)
            return 0;
    }
    return 1;
}


int getMethodNumber(char *val)
{
    if (isRegister(val) == 1)
    {
        return 3;
    }
    else if (isImmediate(val) == 1)
    {
        return 0;
    }
    else if(isStruct(val) == 1){
        return 2;
    }
    else if (isLabel(val, 0))
    {
        return 1;
    }

    return -1;
}

int getStructNumber(char *val)
{
	char *token;
	char *valCopy = malloc(sizeof(val));;
	char *strtolEnd;
	int strtolInt;
	
	/* copy to save original value */
	strcpy(valCopy ,val);
	/* move to the number after the . */
	token = strtok(valCopy, STRUCT_DELIM);
	token = strtok(NULL, STRUCT_SEPARATORS);
	strtolInt = strtol(token, &strtolEnd, 10);
	return strtolInt;
}

char * getLabelStruct(char *val)
{
	char *token;
	char *valCopy = malloc(sizeof(val));;
	
	/* copy to save original value */
	strcpy(valCopy ,val);
	token = strtok(valCopy, STRUCT_DELIM);
	return token;
}

int isStruct(char *val)
{
	char *token;
	char *valCopy = malloc(sizeof(val));;
	char *strtolEnd;
	int strtolInt;
	
	/* copy to save original value */
	strcpy(valCopy ,val);
	token = strtok(valCopy, ".");
	
	/* if is a legal label, check the number*/
	if (isLabel(token, 0))
	{
	    token = strtok(NULL, STRUCT_SEPARATORS);
			if (token != NULL)
			{
			    strtolInt = strtol(token, &strtolEnd, 10);
                if(strtolInt == 1 || strtolInt == 2)
                    return 1;
                else return 0;
			}
			else return 0;
	}
	else
		return 0;
}

/*add to linked list a new node with the values*/
void addToList(list **head, char *label, int number, char *val, int address)
{
	list* tempNode = (list*)malloc(sizeof(list));
	list* pntList1;
	list* pntList2;
	
	if (!tempNode)
	{
		/* error: can not allocate memory */
		printf("allocate memory error!");
		exit(0);
	}
    /*if it external/label/code*/
	if (val != NULL)
	{
		strcpy(tempNode->type, val);
	}
	 /*if have a label/symbol*/
	if (label != NULL)
	{
		strcpy(tempNode->name, label);
	}
	tempNode->num = number;
    
    /* get last in list */
	for (pntList1 = (*head); pntList1; pntList1 = pntList1->next)
	{
		pntList2 = pntList1;
	}
	 /*if the node is the first node in the list*/
	if (pntList1 == (*head))
	{
		(*head) = tempNode;
		tempNode->next = NULL;
	}
	else
	{  
	    /*add to end of list*/
		pntList2->next = tempNode;
		tempNode->next = NULL;
	}
		if((val != NULL) && (strcmp(val, "e")==0))
		{ 
		    /*if it external the address is 0*/
			tempNode->address = 0;
		} 
		else
		{
			tempNode->address = address ;
		} 
	
}

/*free space of list*/
void clearList(list **head)
{
	list* pntList;
	
	for(;*head;)
	{
		pntList = (*head);
		(*head) = pntList->next;
		free(pntList);
	}
}

/*remove macros*/
void removeMacros(char *filename, char *amFileName)
{
    FILE *amInputFile, *inputFile;
    char *separators = "\t\n, \r";
	char *currentToken, *nameOfMacro, *nameOfMacroCopy;
	char line[100];
	char lineCopy[100];
	int macroSpread = 0;
	
    amInputFile = fopen(amFileName, "wb");
    inputFile = fopen(filename, "r");
    if (inputFile == NULL)
	{
		/* error: could not open the file */
		printf("could not open file %s\n", filename);
		int errors = 1;
		
	}
	else if (amInputFile == NULL)
	{
		/* error: could not open the file */
		printf("could not open file %s\n", amFileName);
		int errors = 1;
		
	}
	else
	{
    while (fgets(line, 80, inputFile) != NULL) /* read lines from file */
	{
	    if (line[0] == '\n')
	        continue;
		if (feof(inputFile) == 0)
		{
			*(strchr(line, '\n')) = '\0';
		}
		strcpy(lineCopy, line);
		currentToken = strtok(lineCopy, separators);
		if (strcmp(currentToken, MACRO_BEGIN_DIRECTIVE)==0)
		{
		    nameOfMacro = strtok(NULL, separators);
		    nameOfMacroCopy = malloc(sizeof(nameOfMacro));
		    strcpy(nameOfMacroCopy, nameOfMacro);
		    while (fgets(line, 80, inputFile) != NULL) 
		    {
		        strcpy(lineCopy, line);
		        currentToken = strtok(lineCopy, separators);
		        if (strcmp(currentToken, MACRO_END_DIRECTIVE)==0)
		        {
		            break;
		        }
		        else
		        {
		            addToList(&macroList, nameOfMacroCopy, 0, line , 0);
		        }
		        
		    }
		    
		}
		else
		{
		    list* pntList1;
	        for (pntList1 = (macroList); pntList1; pntList1 = pntList1->next)
	            {
		            if (strcmp(pntList1->name, currentToken) == 0)
		            {
		                fprintf(amInputFile, "%s\n", pntList1->type);
		                macroSpread = 1;
		            }
			                
	            }
	        if(macroSpread == 0)
	            fprintf(amInputFile, "%s\n", line);
	       macroSpread = 0;

	    }
		
    
    
	}
    fclose(inputFile);
    fclose(amInputFile);
	}

}

/*change the address for listdata/listlabel to the correct address*/
void updateListAddress(list **head, int offset, int labelList)
{
	list* pntList;
	for (pntList = (*head); pntList; pntList = pntList->next)
	{
	    if(labelList==1)
	    {
	        if(strcmp(pntList->type, "data") == 0)
		    {
				pntList->address = pntList->address + offset; 
		    }    
	    }
	    else
	    {
		    pntList->address = pntList->address + offset;
	    }
	}
}

void updateLabelAddress(list **head , list *headLabel)
{
	list*  pntList1;
	list*  pntList2;
	char temp[30];
	
	/*listcode*/
	for (pntList1 = (*head); pntList1; pntList1 = pntList1->next)
	{
	    /*check if label*/
		if ((isLabel((pntList1->name), 0)) == 1) 
		{
		    /*listlabel*/
			for (pntList2 = (headLabel); pntList2; pntList2 =pntList2->next) 
			{
			    /* temp is with no colon */
				strcpy(temp ,pntList2->name);
				temp[strlen(temp)-1]=0; 
				/* compare to with or without colon */
				if (strcmp(pntList1->name, temp) == 0 || strcmp(pntList1->name, pntList2->name) == 0)
				{	
                        if(!(strcmp(pntList2->type, "external") == 0))
                        {
                            pntList1->num = pntList2->address<<2;
						    /* mark the R bit */
						    pntList1->num = pntList1->num | 2;
						
                        }
			
						/*if external add to external list*/
						else
						{
						    /* mark the E bit*/
						    pntList1->num = pntList1->num | 1;
							addToList(&extList, pntList1->name, 0, "e", pntList1->address);
						}

				}
			}
		}
	}
}

/*updata external symbol address in listcode*/
void updateExt(list **head, list *headex)
{
	list*  pntList1;
	list*  pntList2;
	 /*pntList1  is pointing to the address of listcode*/
	for (pntList1 = (*head); pntList1 != NULL; pntList1 = pntList1->next)
	{
	    /*pntList2  is pointing to copy of listext*/
		 
		if ((isLabel((pntList1->name), 0)) == 1)
		{
			for(pntList2 = headex;pntList2 != NULL;pntList2 = pntList2->next)
			{
				if (strcmp(pntList2->name, pntList1->name ) == 0)
				{
					strcpy(pntList1->type ,"e");
					break;		
				}
			}
		}
		
	}
}
