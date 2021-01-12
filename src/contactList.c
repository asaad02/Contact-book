#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/contactHelper.h"




/*Main method*/

int main ()
{
	
	/*Initialization*/

	typedef struct contact record;
		record item;
	
		FILE *fptr;
		char *input1;
		char *input2;

	/*Gets user input and loop accordingly*/
	do
	{

		/*Calling open_file_to_readwrite*/
		fptr=open_file_to_readwrite("myContactList.db");


		input1=malloc(10);
		input2=malloc(10);

		printf("Do you wish to enter a new contact (Yes or No)?: ");

		scanf("%s",input1);
		fflush(stdin);	/*clear buffer*/


		if(strcmp(input1,"No")!=0)

		{

		writeToFile(fptr,item);

	 	}


	 	else if (strcmp(input1,"No")==0) 
	 	{
	 	 
			printf("Do you wish to retrieve a contact (Yes or No)?: ");
			scanf("%s",input2);
			fflush(stdin);

			/*Input phone number from user to find it*/
			if(strcmp(input2,"No")!=0)
			{

				
				unsigned long phone;
				do
				{
					printf("Phone Number: ");
					scanf("%lu",&phone);
					fflush(stdin);
				}while(phone<=0);

				fflush(stdin);

				
				retrieveFromFile(fptr, item, phone);
			}
		}
	}while((strcmp(input1,"No")!=0) || (strcmp(input2,"No")!=0));

	fclose ( fptr );
	return 0;
}