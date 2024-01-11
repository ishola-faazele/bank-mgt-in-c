#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bank.h"
#include "check_details.h"
#include "new_account.h"
#include "modify_details.h"

int modify_csv(struct Account*);

void modify_details() {
    char idToModify[9];
    char pinToModify[5];
    printf("\n\n\tCOMPUTERIZED  BANK MANAGEMENT SYSTEM\n");
    printf("\n\n\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\t\tCHANGE ACCOUNT DETAILS\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    
    printf("\n\n\tEnter your student id:\t");
    scanf("%8s", idToModify);

    printf("\n\n\tEnter your pin:\t");
    scanf("%4s", pinToModify);
    struct Account *accToModify = login(idToModify, pinToModify);

    if(accToModify != NULL) {
        printf("\n\n\tLogin successful.");
    }
    else{
        printf("\n\n\tUnable to login.");
        menu();
    }

    printf("\n\n\tPlease select an option to change:");
    printf("\n\n\t\t1. Name");
    printf("\n\n\t\t2. Phone number");
    printf("\n\n\t\t3. Address");
    printf("\n\n\t\t4. Pin");
    printf("\n\n\t\t5. Menu");

    int option;
    
    while (1) {
        printf("\n\n\tI want to change: \t");

        if(scanf("%i", &option) != 1) {
            printf("\n\n\tEnter a valid response (numeric option)");
        }        

        switch (option)
        {
        case 1:
            printf("\n\n\tEnter your new Name:\t");
            scanf("%59s", accToModify->name);
            modify_csv(accToModify);
            menu();
            break;
        case 2:
            printf("\n\n\tEnter your new Phone number:\t");
            scanf("%10s", accToModify->phoneNo);
            modify_csv(accToModify);
            menu();
            break;
        case 3:
            printf("\n\n\tEnter your new address:\t");
            scanf("%10s", accToModify->address);
            modify_csv(accToModify);
            menu();
            break;
        case 4:
            printf("\n\n\tEnter a new 4 digit pin:\t");
            scanf("%10s", accToModify->pin);
            modify_csv(accToModify);
            menu();
            break;
        case 5:
            menu();
            break;
        default:
            printf("\n\n\tEnter a valid response.");
            break;
        }

        if(option >= 1 && option <=5) {
            break;
        }
    }  
}

int modify_csv(struct Account* accToModify) {
    char* file_path = "all-account.csv";
    FILE *originalFile = fopen(file_path, "r");
    FILE *tempFile = fopen("temp.csv", "w");

    char* idToModify = accToModify->studentId;

    if (originalFile == NULL || tempFile == NULL) {
        fprintf(stderr, "\n\n\tError opening files.\n");
        exit(EXIT_FAILURE);
    }
    char line[1024];

    while (fgets(line, 1024, originalFile) != NULL) {
        char* token = strtok(line, ",");
        if(token != NULL && strcmp(token, idToModify) == 0)  {
            write_to_csv(tempFile, accToModify);
        }
        else {
            fputs(line, tempFile);
        }
    }
    fclose(originalFile);
    fclose(tempFile);

    if (remove(file_path) != 0 || rename("temp.csv", file_path) != 0) {
        fprintf(stderr, "\n\n\tError updating the file.\n");
        exit(EXIT_FAILURE);
    }
}