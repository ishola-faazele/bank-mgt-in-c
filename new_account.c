#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include "bank.h"
#include "new_account.h"
#include "check_details.h"

int write_to_csv(FILE* file, const struct Account *account) {
    
    fprintf(file, "%s,%s,%s,%02d/%02d/%04d,%s,%c,%s,%s,%f,%02d/%02d/%04d\n", 
        account->studentId, account->ghanaId,account->name,account->birthDate.day,account->birthDate.month,account->birthDate.year,
        account->phoneNo,account->gender,account->address, account->pin, account->balance,
        account->creationDate.day,account->creationDate.month,account->creationDate.year
    );

    fclose(file);
    return 0;
}


int valid_input(char* pattern, char* input) 
{   // create a regex_t structure
    regex_t regex;

    // compile the regex
    int reti = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);

    // checks if the compilation was successful
    if(reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // execute the regex
    reti = regexec(&regex, input,0, NULL, 0);

    if (!reti) {
        printf("\t\tInput is valid!\n");
        return 0;
    } else if (reti == REG_NOMATCH) {
        printf("\t\tInput does not match the required pattern.\n");
        return 1;
    } else {
        char error_message[100];
        regerror(reti, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "Regex match failed: %s\n", error_message);
        return 1;
    }
    
    //frees the regex_t structure
    regfree(&regex);

    
    return 0;
}


void create_new_acc(void) {

    printf("\n\n\tCOMPUTERIZED  BANK MANAGEMENT SYSTEM\n");
    printf("\n\n\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\t\tACCOUNT CREATION MENU\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    struct Account new_account;
    printf("\n\n\tALL INPUTS ARE CASE INSENSTIVE.\n\n\n");

    // identification
    char* ghanaCardPattern = "^gha-[0-9]{9}-[0-9]$";
    do {
        
        printf("\tEnter your Ghana Card ID in the form 'gha-xxxxxxxxx-x':\t");
        if (scanf("%16s", new_account.ghanaId) != 1) {
            printf("\t\tInvalid Ghana ID");
        }

    } while (valid_input(ghanaCardPattern, new_account.ghanaId) != 0);
    
    char* studentIdPattern = "[0-9]{8}$";
    do {
        printf("\n\n\tEnter your 8-digit Student ID: eg. xxxxxxxx\t");
        if(scanf("%9s", new_account.studentId) != 1 ){
            printf("\t\tInvalid Student ID");
        }
    } while( valid_input(studentIdPattern, new_account.studentId) != 0);


    //personal information
    printf("\n\n\tEnter your full name:\t");
    scanf("%59s", new_account.name);

    printf("\n\n\tEnter your date of birth in this format DD/MM/YYYY:\t");
    scanf("%d/%d/%d", &new_account.birthDate.day, &new_account.birthDate.month, &new_account.birthDate.year);


    printf("\n\n\tEnter phone number eg. 020173020:\t");
    scanf("%11s", new_account.phoneNo);

    printf("\n\n\tWhat is your gender? m/f:\t");
    scanf(" %c", &new_account.gender);


    printf("\n\n\tEnter digital address:\t");
    scanf("%12s", new_account.address);
    

    // account info

    printf("\n\n\tEnter a pin:\t");
    scanf("%5s", new_account.pin);

    printf("\n\n\tEnter initial deposit:\t");
    scanf("%f", &new_account.balance);

    printf("\n\n\tEnter today's date in this format DD/MM/YYYY:\t");
    scanf("%i/%i/%i", &new_account.creationDate.day, &new_account.creationDate.month, &new_account.creationDate.year);

    printf("\n\n");

    FILE *file = fopen("all-accounts.csv", "a+");
    if (file == NULL) {
        perror("\tError opening file");
        return 1;
    }

    int write = write_to_csv(file,&new_account);

    if(write == 0) {
        system("cls");
        int option;
        printf("\n\n\tCongrats. You've successfully created an account.");
        printf("\n\n\tPlease select an option:");
        printf("\n\n\t\t1. Return to Main menu.");
        printf("\n\n\t\t2. Check Account Details.");
        printf("\n\n\t\t3. Exit  app.\n\n");

        printf("\n\n\tI want to:\t");
        scanf("%d", &option); 

        do{
            if(option == 1) {
                transition();
                menu();
            }
            else if (option == 2) {
                check_details();
                transition();
                }
            else if(option == 3) {
                exit(0);
            }
            else {
                printf("\tInvalid option");
            }
        } while(option !=1 || option !=2);  
        system("cls");
    }

    else {
        printf("\n\tUnable to create acccount");
    }
}
