#include "main.h"

int DC;
int IC;
int ICF;
int DCF;
list *codeList;
int hasErrors;

void translateOpCode(char *cmd, int *output, int lineNumber)
{
	if (strcmp(cmd, "cmp") == 0)
		*output = (*output | 1<<OP_BITS);
	else if (strcmp(cmd, "add") == 0 )
		*output = (*output | 2<<OP_BITS);
	else if (strcmp(cmd, "sub") == 0)
		*output = (*output | 3<<OP_BITS);
	else if (strcmp(cmd, "not") == 0)
		*output = (*output | 4<<OP_BITS);
	else if (strcmp(cmd, "clr") == 0)
		*output = (*output | 5<<OP_BITS);
	else if (strcmp(cmd, "lea") == 0)
		*output = (*output | 6<<OP_BITS);
	else if ( strcmp(cmd, "inc") == 0)
		*output = (*output | 7<<OP_BITS);
	else if ( strcmp(cmd, "dec") == 0)
		*output = (*output | 8<<OP_BITS);
	else if (strcmp(cmd, "jmp") == 0)
		*output = (*output | 9<<OP_BITS);
	else if (strcmp(cmd, "bne") == 0)
		*output = (*output | 10<<OP_BITS);
	else if (strcmp(cmd, "get") == 0)
		*output = (*output | 11<<OP_BITS);
	else if (strcmp(cmd, "prn") == 0)
		*output = (*output | 12<<OP_BITS);
	else if (strcmp(cmd, "jsr") == 0)
		*output = (*output | 13<<OP_BITS);
	else if (strcmp(cmd, "rts") == 0)
		*output = (*output | 14<<OP_BITS);
	else if (strcmp(cmd, "hlt") == 0)
		*output = (*output | 15<<OP_BITS);
	else if (!(strcmp(cmd, "mov") == 0))
	{
		/* error: command not found */
		printf("Line:%d  command not found\n" , lineNumber);
		errors = 1;
	}
}

void translateImmediate(char *token, int *output)
{
	/*remove # before number*/
	char * num = malloc(strlen(token)-1);
	strcpy(num, token+1);
	int number;
	number = atoi(num);

	*output = (*output | (-((~number) +1 ) & MAX_IMMEDIATE)<<IMMEDIATE_BITS);

}


void translateRegister(char *tok, char *mode, int *output, int lineNumber)
{
	/*remove r before number*/
	char * num = malloc(strlen(tok)-1);
	strcpy(num, tok+1);

	int number;
	number = atoi(num);
	
	if(number >= 0 && number <= 7)
	{
	    if (strcmp(mode, SOURCE) == 0)
		    /* put in bits 6-9*/
		    *output = (*output | (number<<6));
	    else if (strcmp(mode, DST) == 0)
		    /* put in bits 2-5 */
		    *output = (*output | (number<<DST_METHOD_BITS));
	}
	else
	{
	    /* error: reg number out of range*/
		printf("Line:%d  illigal reg number\n" , lineNumber);
		errors = 1;
	}
}

void translateMethod(char *token, char * mode, int *output, int lineNumber)
{
    /* direct addressing*/
    if (getMethodNumber(token)==1)
	{
		if (strcmp(mode, SOURCE) == 0)
			/* put 1 in bits 4-5 */
			*output = (*output | 1<<SOURCE_METHOD_BITS);
		else if (strcmp(mode, DST) == 0)
			/* put 1 in bits 2-3  */
			*output = (*output | 1<<DST_METHOD_BITS);
	}
    /* struct addressing*/
	else if(getMethodNumber(token)==2)
	{
		if (strcmp(mode, SOURCE) == 0)
			/* put 2 in bits 4-5 */
			*output = (*output | 2<<SOURCE_METHOD_BITS);
		else if (strcmp(mode, DST) == 0)
			/* put 2 in bits 2-3 */
			*output = (*output | 2<<2);
	}
	/* register addressing*/
	else if (getMethodNumber(token)==3)
	{
		if (strcmp(mode, SOURCE) == 0)
			/* put 3 in bits 4-5 */
			*output = (*output | 3<<SOURCE_METHOD_BITS);
		else if (strcmp(mode, DST) == 0)
			/* put 3 in bits 2-5  */
			*output = (*output | 3<<DST_METHOD_BITS);
	}
	else if (getMethodNumber(token)!=0){
			/* error: method is illigal*/
			printf("Line:%d  illigal methon %s\n" , lineNumber, token);
			errors = 1;
			}

}

void translateCommand(char *token, char *labelName, int lineNumber)
{

	char *arg1 = NULL;
	char *arg2 = NULL;
	char *commandName = token;

	token = strtok(NULL, CMD_LINE_SEPARATORS);
	
		if (token != NULL)
		{
			arg1 = token;
		}
		
		token = strtok(NULL, CMD_LINE_SEPARATORS);
		
		if (token != NULL)
		{
			arg2 = token;
		}
		
		token = strtok(NULL, CMD_LINE_SEPARATORS);
		
		if (token != NULL)
		{
			/* error: too many operands */
			printf("Line:%d  too many operands\n" , lineNumber);
			errors = 1;
		}

		/*if two operands*/
		else if (arg2 != NULL)
		{
            translateTwoOperands(commandName,token,labelName, arg1, arg2, lineNumber);

		}
		/*if has  one operand*/
		else if (arg1 != NULL)
		{
            translateOneOperand(commandName,token,labelName, arg1, lineNumber);

		}
		/*if has no operands */
		else
		{
            translateNoOperands(commandName,token, lineNumber);
		}
}

int needsNoOperands(char * commandName)
{
   if((strcmp(commandName, "rts") == 0) || (strcmp(commandName, "hlt") == 0))
        return 1;
   return 0;
}

int needsTwoOperands(char * commandName)
{
   if((strcmp(commandName, "mov") == 0) ||
	  (strcmp(commandName, "add") == 0) ||
	  (strcmp(commandName, "sub") == 0) ||
	  (strcmp(commandName, "lea") == 0) ||
	  (strcmp(commandName, "cmp") == 0))
        return 1;
   return 0;
}



void translateNoOperands(char * commandName,char *token, int lineNumber)
{
    int output1 = 0;
    char *type = "a";
	/*first word - opcode*/
    translateOpCode(commandName, &output1, lineNumber);
    		/*if command is not rts or hlt, there are too few operands*/
			if (needsNoOperands(commandName) == 0)
			{
				printf("Line:%d  too few operands for %s\n" , lineNumber, commandName);
				errors = 1;
			}
			else
			{
			    	addToList(&codeList, "", output1, type, IC);
	                ++IC;
			}
}


void translateOneOperand(char * commandName, char *token, char *labelName,char * arg1, int lineNumber)
{
    int output1 = 0;
	int output2 = 0;
	int output3 = 0;
	char *type = "a";
		/*first word - opcode*/
    translateOpCode(commandName, &output1, lineNumber);
    if(needsNoOperands(commandName) == 1)
	{
        /* error: too many operands, needs to be zero operands */
		printf("Line:%d  too many operands\n" , lineNumber);
		errors = 1;
	}
				
	else if(needsTwoOperands(commandName) == 1)
	{
		/* error: too few operands, needs to be two operands */
		printf("Line:%d  too few operands\n" , lineNumber);
		errors = 1;
	}
	else if (!(strcmp(commandName, "prn") == 0) && getMethodNumber(arg1)==0)
	{
		/* error: incorrect method, only prn can be with method 0*/
		printf("Line:%d  incorrect operand %s for %s\n" , lineNumber, arg1, commandName);
		errors = 1;
	}
	else
	{
	    translateMethod(arg1, DST, &output1, lineNumber);
		addToList(&codeList, "", output1, type, IC);
	   ++IC;
	                
	    if (getMethodNumber(arg1)==3)
		{
			translateRegister(arg1, DST, &output2, lineNumber);
		    addToList(&codeList, "", output2, type, IC);
	        ++IC;
		}
		else if (getMethodNumber(arg1)==0)
		{
            translateImmediate(arg1, &output2);
			addToList(&codeList, "", output2, type, IC);
	        ++IC;
		}
		else if (getMethodNumber(arg1)==1)
		{
		    labelName = malloc(sizeof(arg1));
	        strcpy(labelName ,arg1);
	        addToList(&codeList, labelName, output2, type, IC);
	       ++IC;
		}
	    else if (getMethodNumber(arg1)==2)
	    {
	        labelName = malloc(sizeof(arg1));
	        strcpy(labelName ,getLabelStruct(arg1));
	        addToList(&codeList, labelName, output2, type, IC);
	        ++IC;
	       addToList(&codeList, "", output3 | getStructNumber(arg1)<<2, type, IC);
	       ++IC;
		}
			    
	}
		 
}

void translateTwoOperands(char * commandName,char *token, char *labelName,char * arg1, char * arg2, int lineNumber)
{
    int output1 = 0;
	int output2 = 0;
	int output3 = 0;
	int output4 = 0;
	int output5 = 0;
	char *type = "a";
		/*first word - opcode*/
    translateOpCode(commandName, &output1, lineNumber);
	
    if(needsTwoOperands(commandName) == 0) 
	{
		/* error: need to be only zero or one operands*/
		printf("Line:%d  too many operands\n" , lineNumber);
		errors = 1;
	}
	else
	{
	    if((strcmp(commandName, "lea") == 0) && (getMethodNumber(arg1)==0 || getMethodNumber(arg1)==3))
		{
			/* error: lea command is not legal with src method 0 and 3*/
			printf("Line:%d  incorrect operand: %s is not legal with %s\n" , lineNumber, commandName, arg1);
			errors = 1;
		}
		else if(!(strcmp(commandName, "cmp") == 0) && getMethodNumber(arg2)==0)
	    {
			/* dest methon 0 is legal only in cmp command*/
			printf("Line:%d  incorrect operand: %s is not legal with %s\n" , lineNumber, commandName, arg2);
			errors = 1;
		}
		else 
		{
	        translateMethod(arg1, SOURCE, &output1, lineNumber);
			translateMethod(arg2, DST, &output1, lineNumber);
			addToList(&codeList, "", output1, type, IC);
	        ++IC;
			/*add extra words for arg1*/
			if (getMethodNumber(arg1)==3)
			{
		        translateRegister(arg1, SOURCE, &output2, lineNumber);
				if(getMethodNumber(arg2)==3)
				    translateRegister(arg2, DST, &output2, lineNumber);
				addToList(&codeList, "", output2, type, IC);
	             ++IC;
			}
			else if (getMethodNumber(arg1)==0)
			{
                translateImmediate(arg1, &output2);
			    addToList(&codeList, "", output2, type, IC);
	             ++IC;
			 }
			 else if (getMethodNumber(arg1)==1)
			 {
			    labelName = malloc(sizeof(arg1));
	           	strcpy(labelName ,arg1);
	           	addToList(&codeList, labelName, output2, type, IC);
	             ++IC;
			 }
	         else if(getMethodNumber(arg1)==2 )
	         {
	            labelName = malloc(sizeof(arg1));
	           	strcpy(labelName ,getLabelStruct(arg1));
	            addToList(&codeList, labelName, output2, type, IC);
	            ++IC;
	            addToList(&codeList, "", output3 | getStructNumber(arg1)<<2, type, IC);
	            ++IC;
			 }
             /*add extra words for arg2*/
			 if (getMethodNumber(arg2)==3)
			 {
			    if(getMethodNumber(arg1)!=3)
			    {
				    translateRegister(arg2, DST, &output4, lineNumber);
				    addToList(&codeList, "", output4, type, IC);
	               ++IC;
			     }
			 }
			 else if (getMethodNumber(arg2)==0)
			 {
                 translateImmediate(arg2, &output4);
			    addToList(&codeList, "", output4, type, IC);
	            ++IC;
			 }
			 else if (getMethodNumber(arg2)==1)
			 {
			    labelName = malloc(sizeof(arg2));
	           	strcpy(labelName ,arg2);
	           	addToList(&codeList, labelName, output4, type, IC);
	             ++IC;
	         }
	         else if (getMethodNumber(arg2)==2)
	         {
	            labelName = malloc(sizeof(arg2));
	           	strcpy(labelName ,getLabelStruct(arg2));
	            addToList(&codeList, labelName, output4, type, IC);
	            ++IC;
	            addToList(&codeList, "", output5 | getStructNumber(arg2)<<2, type, IC);
	            ++IC;
			 }
			
		}
	}
}
