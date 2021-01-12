#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/contactHelper.h"


/*Main method*/

int main ()
{
    FILE *fptr;
    
    int selectedRecord;
    
    /*Calling open_file_to_readwrite*/
    fptr=open_file_to_readwrite("bin/myContactList.db");
    
    while(1)
    {
        int noOfRecords = CountContacts(fptr);
        printf("Number of contacts = %d\n\n", noOfRecords);
        
        contact *contacts= GetAllRecords(fptr);
        
        printf("\n\nAction: ");
        
        char input1;
        scanf(" %c", &input1);
        
        if(input1 == 'A')
            writeToFile(fptr);
        else if(input1 == 'X')
            break;
        else
        {
            selectedRecord = input1 - '0';
            
            printf("Contact #%d:\n", selectedRecord);
            printf("Phone Number: %lu\n", contacts[selectedRecord - 1].phoneNumber);
            printf("First Name: %s\n", contacts[selectedRecord - 1].firstName);
            printf("Last Name: %s\n", contacts[selectedRecord - 1].lastName);
            printf("Company Name: %s\n", contacts[selectedRecord - 1].companyName);
            printf("Email: %s\n", contacts[selectedRecord - 1].email);
            printf("\n\nAction: ");
            
            
            char input2;
            scanf(" %c", &input2);
            
            if(input2 == 'R')
                continue;
            else if(input2 == 'E')
            {
                Edit(fptr, selectedRecord);
                continue;
            }
            else
            {
                Delete(fptr, selectedRecord);
                continue;
            }
        }
    }
    
    fclose ( fptr );
    return 0;
}
