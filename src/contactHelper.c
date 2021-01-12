#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/contactHelper.h"




FILE *open_file_to_readwrite(char fname[])
{
	FILE *fptr;

	fptr = fopen ( fname, "rb+" ); 
	if(fptr==NULL)	
	{
			fptr = fopen ( fname, "wb+" ); 
	}
	else{
		fseek(fptr,+1,SEEK_END); 
	}
	return fptr;
}

void writeToFile(FILE *fptr, struct contact item)
{
		int contactPosition;

		contactPosition=ftell(fptr);
		fwrite(&item, sizeof(item),1,fptr);

		item.first_name_posn=ftell(fptr);
		char fname[40];
		/*fname=malloc(40);*/
		printf("First Name: ");
		/*scanf("%s",fname);*/
		fgets(fname,40,stdin);
		fputs(fname,fptr);
		fflush(stdin);

		item.last_name_posn=ftell(fptr);
		char lname[40];
		/*lname=malloc(40);*/
		printf("Last Name: ");
		/*scanf("%s",lname);*/
		fgets(lname,40,stdin);
		fputs(lname,fptr);
		fflush(stdin);
		
		item.company_name_posn=ftell(fptr);
		char cname[100];
		printf("Company Name: ");
		fgets(cname,100,stdin);
		fputs(cname,fptr);
		fflush(stdin);
		
		unsigned long phone;
		do
		{
			printf("Phone Number (enter only numbers): ");
			scanf("%lu",&phone);
		}while(phone<=0);
		
		item.phone_number=phone;
		fprintf(fptr,"%lu",phone);


		item.email_posn=ftell(fptr);
		char *email;
		email=malloc(100);
		printf("Email: ");
		scanf("%s",email);
		fputs(email,fptr);
		fflush(stdin);

		int nextPos=ftell(fptr);
		item.next=nextPos+1;

		fseek(fptr,contactPosition,SEEK_SET);
		fwrite(&item, sizeof(item),1,fptr);

		fseek(fptr,nextPos+1,SEEK_SET);
}



void retrieveFromFile(FILE *fptr, struct contact item, unsigned long phone)
{
	fseek ( fptr, 0, SEEK_SET );
		int itemFound=0;
		while(fread(&item,sizeof(item),1, fptr)>0)
		{
			
			if(phone==item.phone_number)
			{
				
				itemFound=1;
				
				fseek ( fptr, item.first_name_posn, SEEK_SET );
				char fname[40];
				fgets(fname,40, fptr);
				printf("First Name: %s",fname);

				fseek ( fptr, item.last_name_posn, SEEK_SET );
				char *lname;
				lname=malloc(40);
				fgets(lname,40, fptr);
				printf("Last Name: %s",lname);

				fseek ( fptr, item.company_name_posn, SEEK_SET );
				char cname[100];
				fgets(cname,100, fptr);
				printf("Company Name: %s",cname);

				printf("Phone Number: %lu\n",item.phone_number);

				fseek ( fptr, item.email_posn, SEEK_SET );
				char email[100];
				fgets(email,100, fptr);
				printf("Email: %s\n",email);

				break;
			}
			fseek ( fptr, item.next, SEEK_SET );	
		}

		if(itemFound==0)
		{
			printf("No match found.\n");
		}
}