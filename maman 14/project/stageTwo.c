#include "main.h"

int DC;
int IC;
int ICF;
int DCF;
list* codeList;
list* dataList;
list* labelList;
list* extList;
list* entList;


/*second pass list to update addresses and print*/
void stageTwo(char *fileName)
{
    char fileNameAS[30];
	char fileNameEXT[30];
	char fileNameENT[30];
    strcpy(fileNameAS, fileName);
    strcpy(fileNameEXT, fileName);
    strcpy(fileNameENT, fileName);
    /*update label address in code list*/
	updateLabelAddress(&codeList, labelList);
	
	/*update ext address in code list*/
	updateExt(&codeList, extList);
	
	/*put machine code of code to .ob file*/
	strcat(fileNameAS, OB_EXT);
	printToObFile(fileNameAS);
	
	/*put the external labels in .ext file*/
	strcat(fileNameEXT, EXT_EXT);
	printToExt(fileNameEXT, codeList, "e");
	
	/*put the entry labels in .ent file*/
	strcat(fileNameENT, ENT_EXT);
	printToEnt(fileNameENT, labelList, entList);

    /*free up lists*/
    clearList(&codeList);
	clearList(&dataList);
	clearList(&labelList);
	clearList(&extList);
	clearList(&entList);
}


void printToObFile(char *fileName)
{
    FILE *outputFile;
    outputFile = fopen(fileName, "w");
	fprintf(outputFile, "Base32 address  Base32 code\n");
	fprintf(outputFile, "           m    f\n");
	printToFile(codeList , outputFile);
	fclose(outputFile);
	
	/*put machine code of the data at the end of the file*/ 
	outputFile = fopen(fileName, "a+");
	printToFile(dataList , outputFile);
	fclose(outputFile);
}

/*print in file the value of linked list*/
void printToFile(list *head, FILE *outputFile)
{
	int num; 
	while (head != NULL)
	{
	    num = head->num & 1023;
		/*print counter with leading zeros*/
		fprintf(outputFile, "       %c%c ", SPECIAL_BASE32_STR[head->address/32], SPECIAL_BASE32_STR[head->address%32]);
			
		/*print in special base*/
		fprintf(outputFile, "        %c%c",SPECIAL_BASE32_STR[num/32], SPECIAL_BASE32_STR[num%32]);
		head = head->next;
		
		fprintf(outputFile,"\n");
	}
}


/*print listext in file*/
void printToExt(char *fileName, list* head, char *type)
{
    int i;
	list*  pntList;
    FILE *outputFile;
	outputFile = fopen(fileName, "w");
	for (pntList = (head); pntList; pntList = pntList->next)
	{
		if (strcmp(pntList->type,type) == 0)
		{
			    fprintf(outputFile, "%s", pntList->name);
			    for(i=10-strlen(pntList->name); i>0; i--)
			        fprintf(outputFile, " ");
			    fprintf(outputFile, "%c%c\t\n", SPECIAL_BASE32_STR[pntList->address/32], SPECIAL_BASE32_STR[pntList->address%32]);
		
		}
	}

	fclose(outputFile);
}

/*print listent in file*/
void printToEnt(char *fileName , list* head, list* headEnt)
{
    int i;
	list* pntList1;
	list* pntList2;
	char temp[30];
    FILE *outputFile;
    outputFile = fopen(fileName, "w");
	/*pntList1  is pointing to the address of listcode*/
	for (pntList1 = (head); pntList1 != NULL; pntList1 = pntList1->next) 
	{
	    /*pntList2  is pointing to copy of listent*/
		pntList2 = headEnt; 

		
			strcpy(temp ,pntList1->name);

			temp[strlen(temp)-1]=0; 

			while (pntList2 != NULL )
			{
				if (strcmp(pntList2->name, temp ) == 0)
				{
					pntList2->address = pntList1->address;
					fprintf(outputFile,"%s",  pntList2->name);
					for(i=10-strlen(pntList2->name); i>0; i--)
			            fprintf(outputFile, " ");
					fprintf(outputFile,"%c%c\t\n",  SPECIAL_BASE32_STR[pntList1->address/32], SPECIAL_BASE32_STR[pntList1->address%32]);  
				}
		
				pntList2 = pntList2->next;
			}
		
	}

	fclose(outputFile);
}
