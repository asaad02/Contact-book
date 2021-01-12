#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Contact Structure*/
struct contact {
	unsigned long phone_number;
	long first_name_posn;
	long last_name_posn;
	long company_name_posn;
	long email_posn;
	long next;
};


/*Funtion initializations*/
FILE *open_file_to_readwrite(char fname[]);

void writeToFile(FILE *fptr, struct contact item);


void retrieveFromFile(FILE *fptr, struct contact item, unsigned long phone);