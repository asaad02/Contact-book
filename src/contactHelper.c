#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../includes/contactHelper.h"


FILE *open_file_to_readwrite(char finame[])
{
    FILE *fptr;
    
    fptr = fopen ( finame, "rb+" );
    if(fptr==NULL)
    {
        fptr = fopen ( finame, "wb+" );
    }
    else{
        fseek(fptr,+1,SEEK_END);
    }
    return fptr;
}


void Delete(FILE *fptr, int selectedRecord)
{
    record item;
    
    fseek ( fptr, 0, SEEK_SET );
    int i ;
    
    for(i=1; i<selectedRecord; i++)
    {
        fread(&item,sizeof(item),1, fptr);
        
        fseek ( fptr, item.first_name_posn, SEEK_SET );
        char fname[10];
        fgets(fname,10, fptr);
        
        fseek ( fptr, item.last_name_posn, SEEK_SET );
        char lname [10];
        fgets(lname,10, fptr);
        
        fseek ( fptr, item.company_name_posn, SEEK_SET );
        char cname[100];
        fgets(cname,100, fptr);
        
        fseek ( fptr, item.email_posn, SEEK_SET );
        char email[100];
        fgets(email,100, fptr);
        
        fseek ( fptr, item.next, SEEK_SET );
    }
    
    int contactPosition;
    
    contactPosition=ftell(fptr);
    fread(&item,sizeof(item),1, fptr);
    
    item.phone_number = -1;
    
    fseek(fptr,contactPosition,SEEK_SET);
    fwrite(&item, sizeof(item),1,fptr);
}

void Edit(FILE *fptr, int selectedRecord)
{
    record item;
    
    fseek ( fptr, 0, SEEK_SET );

    int n;
    
    for( n=1; n<selectedRecord; n++)
    {
        fread(&item,sizeof(item),1, fptr);
        
        fseek ( fptr, item.first_name_posn, SEEK_SET );
        char fname[10];
        fgets(fname,10, fptr);
        
        fseek ( fptr, item.last_name_posn, SEEK_SET );
        char lname [10];
        fgets(lname,10, fptr);
        
        fseek ( fptr, item.company_name_posn, SEEK_SET );
        char cname[100];
        fgets(cname,100, fptr);
        
        fseek ( fptr, item.email_posn, SEEK_SET );
        char email[100];
        fgets(email,100, fptr);
        
        fseek ( fptr, item.next, SEEK_SET );
    }
    
    int contactPosition;
    
    contactPosition = ftell(fptr);
    fread(&item,sizeof(item),1, fptr);
    fseek(fptr,contactPosition,SEEK_SET);
    
    writeToFile(fptr);
    
    printf("\n\nAction: ");
    
    char input;
    scanf(" %c", &input);
    
    if(input == 'R')
    {
        Delete(fptr, CountContacts(fptr) - 1);        
        return;
    }
    else if(input == 'D')
    {
        Delete(fptr, selectedRecord);
        Delete(fptr, CountContacts(fptr) - 1);
    }
}
void writeToFile(FILE *fptr)
{
    int contactPosition;
    int i;
    getchar();
    
    record item;
    contactPosition=ftell(fptr);
    fwrite(&item, sizeof(item),1,fptr);
    
    item.first_name_posn=ftell(fptr);
    char fname[10];
    printf("First Name: ");
    fgets(fname,10,stdin);
    for(i=0;i<=9;i++)
    {
        if(fname[i-1] == '\n')
        {
            fname[i-1] = '\0';
            
        }
    }
    fwrite(fname,sizeof(char),sizeof(fname),fptr);
    fflush(stdin);
    
    char lname[10];
    char cname[20];
    do
    {
    item.last_name_posn=ftell(fptr);
    /*char lname[10];*/
    printf("Last Name: ");
    fgets(lname,10,stdin);
    for(i=0;i<=9;i++)
    {
        if(lname[i-1] == '\n')
        {
            lname[i]= '\0';
            break;
        }
    }
    fwrite(lname,sizeof(char),sizeof(lname),fptr);
    fflush(stdin);
    
    item.company_name_posn=ftell(fptr);
    /*char cname[20];*/
    printf("Company Name: ");
    fgets(cname,20,stdin);
    for(i=0;i<=20;i++){
        if(cname[i] == '\n')
        {
            cname[i]= '\0';
            break;
        }
    }
    fwrite(cname,sizeof(char),sizeof(cname),fptr);
    fflush(stdin);
    if(lname[0]=='\0'&& cname[0]=='\0')
    {
    	printf("Please enter Last Name or Company Name, either one is mandatory\n");
    }
	}while(lname[0]=='\0'&& cname[0]=='\0');
    
    unsigned long phone;
    
    
    do
    {
        
        printf("Phone Number (enter only numbers): ");
        scanf("%lu",&phone);
        
        
    }while(phone<=0);
    
    item.phone_number=phone;
    fprintf(fptr,"%lu",phone);
    
    
    
    item.email_posn=ftell(fptr);
    char email[30];
    printf("Email: ");
    scanf("%s",email);
    getchar();
    for(i=0;i<=30;i++){
        if(email[i] == '\n')
        {
            email[i]= '\0';
            break;
        }
    }
    fwrite(email,sizeof(char),sizeof(email),fptr);
    fflush(stdin);
    
    int nextPos=ftell(fptr);
    item.next=nextPos+1;
    
    fseek(fptr,contactPosition,SEEK_SET);
    fwrite(&item, sizeof(item),1,fptr);
    
    fseek(fptr,nextPos+1,SEEK_SET);
}


int CountContacts(FILE *fptr)
{
    int contacts = 0;
    record item;
    
    fseek ( fptr, 0, SEEK_SET );
    
    while(fread(&item,sizeof(item),1, fptr)>0)
    {
        
        fseek ( fptr, item.first_name_posn, SEEK_SET );
        char fname[10];
        fgets(fname,10, fptr);
        
        fseek ( fptr, item.last_name_posn, SEEK_SET );
        char lname [10];
        fgets(lname,10, fptr);
        
        fseek ( fptr, item.company_name_posn, SEEK_SET );
        char cname[20];
        fgets(cname,20, fptr);
        
        fseek ( fptr, item.email_posn, SEEK_SET );
        char email[30];
        fgets(email,30, fptr);
        
        fseek ( fptr, item.next, SEEK_SET );
        
        if(item.phone_number != -1)
        {
            contacts++;
        }
    }
    
    return contacts;
}

contact* GetAllRecords(FILE *fptr)
{
    int noOfRecords = CountContacts(fptr);
    contact contacts[noOfRecords];
    
    int i=0;
    record item;
    
    fseek ( fptr, 0, SEEK_SET );
    
    while(fread(&item,sizeof(item),1, fptr)>0)
    {
        fseek ( fptr, item.first_name_posn, SEEK_SET );
        char fname[10];
        fgets(fname,10, fptr);
        
        fseek ( fptr, item.last_name_posn, SEEK_SET );
        char lname [10];
        fgets(lname,10, fptr);
        
        fseek ( fptr, item.company_name_posn, SEEK_SET );
        char cname[20];
        fgets(cname,20, fptr);
        
        fseek ( fptr, item.email_posn, SEEK_SET );
        char email[30];
        fgets(email,30, fptr);
        
        fseek ( fptr, item.next, SEEK_SET );
        
        if(item.phone_number != -1)
        {
            contact c;
            c.phoneNumber = item.phone_number;
            strcpy(c.firstName, fname);
            strcpy(c.lastName, lname);
            strcpy(c.companyName, cname);
            strcpy(c.email, email);
            
            contacts[i] = c;
            printf("%d. %s %s", i + 1, contacts[i].firstName, contacts[i].lastName);
            i++;
        }
    }
    
    return contacts;
}

