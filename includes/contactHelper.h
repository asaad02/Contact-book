#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Contact Structure*/
typedef struct {
    unsigned long phone_number;
    long first_name_posn;
    long last_name_posn;
    long company_name_posn;
    long email_posn;
    long next;
} record;

typedef struct
{
    unsigned long phoneNumber;
    char firstName[10];
    char lastName[10];
    char companyName[100];
    char email[100];
} contact;


/*Funtion initializations*/
FILE *open_file_to_readwrite(char finame[]);

void Delete(FILE *fptr, int selectedRecord);

void EditRecord(FILE *fptr, int selectedRecord);

void writeToFile(FILE *fptr);

int CountContacts(FILE *fptr);

contact* GetAllRecords(FILE *fptr);


