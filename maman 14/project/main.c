#include "main.h"
int errors;


int main (int argc, char *argv[])
{
    int index;
    char fileName[30];
	char fileNameAS[30];
	char fileNameAM[30];
	
	/* need at least 2 argc, one for command and one for filename with no suffix */
	if (argc <= 1)
	{
		/* error: no file*/
		printf("you need to enter file name!\n");
	}
	else 
	{
		for (index=1; index<argc; index++)
		{
		    /* file name without suffix */
		    strcpy(fileName, argv[index]);
			strcpy(fileNameAS, fileName);
			strcpy(fileNameAM, fileName);
			/* add .as to filename */
			strcat(fileNameAS, AS_EXT);
			/* add .am to filename, for *.am file with macros removed*/
			strcat(fileNameAM, AM_EXT);
			/* remove macros and write into *.am file*/
			removeMacros(fileNameAS, fileNameAM);
			/* first pass*/
			stageOne(fileNameAM);
			/*if there are no errors, do second pass*/
			if(errors == 0)
			{
				stageTwo(fileName);
				printf("File %s has been translated successfully\n", fileNameAS);

			}
			    
		    
	    }
	}
	return 0;
    }
    
    