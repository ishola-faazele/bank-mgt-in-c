#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bank.h"
#include "check_details.h"


struct Account* login(char* studentId, char* pin) {
    char* file_path = "all-accounts.csv";
    FILE *file = fopen(file_path, "r");
    if(file == NULL) {
        fprintf(stderr, "Error opening file");
        return NULL;
    }
    int maxSize = 1024;
    
    char line[maxSize];
    struct Account *result = NULL;
    

    while (fgets(line, maxSize, file) != NULL) {

        struct Account currentAccount;
       
        int parsedFields = sscanf(line, "%8[^,],%19[^,],%59[^,],%d/%d/%d,%10[^,], %c,%11[^,],%4[^\n],%f,%d/%d/%d",
                         currentAccount.studentId, currentAccount.ghanaId, currentAccount.name,
                         &currentAccount.birthDate.day, &currentAccount.birthDate.month, &currentAccount.birthDate.year,
                         currentAccount.phoneNo, &currentAccount.gender, currentAccount.address,
                         currentAccount.pin, &currentAccount.balance,
                         &currentAccount.creationDate.day, &currentAccount.creationDate.month, &currentAccount.creationDate.year);

        
        if (parsedFields == 14 && strcmp(currentAccount.studentId, studentId) == 0 && strcmp(currentAccount.pin, pin) == 0) {
            result = malloc(sizeof(struct Account));
            if (result != NULL) {
                memcpy(result, &currentAccount, sizeof(struct Account));
            }
            break;
        }
    }
    fclose(file);
    return result;


    /* ALTERNATIVE APPROACH
    int idIndex = -1;
    int pinIndex = -1;
    
    if(fgets(line, maxSize, file) != NULL) {
        char* token = strtok(line,",");
        int index1 = 0;
        int index2 = 0;

        while (token != NULL) { 
            if (strcmp(token, "studentId") == 0) { 
                idIndex = index1; 
                break;
            }
            token = strtok(NULL, ","); 
            index1++;
        }

        if (idIndex == -1) {
            fprintf(stderr, "Column 'studentId' not found in the CSV file.\n");
            fclose(file);
            return 1;
        }

        while (token != NULL) { 
            if (strcmp(token, "pin") == 0) { 
                pinIndex = index2; 
                break;
            }
            token = strtok(NULL, ","); 
            index2++;
        }

        if (pinIndex == -1) {
            fprintf(stderr, "Column 'pin' not found in the CSV file.\n");
            fclose(file);
            return 1;
        }
        
    }
    else{
        fprintf(stderr, "Error reading the file.\n");
    }
    while (fgets(line, maxSize, file) != NULL) { 

        char* token = strtok(line, ","); 
        int current_id_index = 0; 
        int current_pin_index = 0;

        while (token != NULL) { 
            if (current_id_index == idIndex && strcmp(token, studentId) == 0) { // uses index to check if the current token is in the studentId column and it is the assigned studentId
                char* token = strtok(line, ",");

                while (token != NULL) { 
                    if(current_pin_index == pinIndex && strcmp(token, pin) == 0) {
                        char* token = strtok(line, ",");

                        while (token != NULL) { 
                            printf("%s", token);
                            token = strtok(NULL, ",");
                        }

                        fclose(file);
                        printf("Login successful\n\n");
                        return 0;
                    }
                    token = strtok(NULL, ",");
                    current_pin_index++;
                }
            }
            token = strtok(NULL, ",");
            current_id_index++;
    }*/
}


int check_details(void) {
    int option;
    char studentIdToFind[9];
    char pinToFind[5];
    
    printf("\n\n\tCOMPUTERIZED  BANK MANAGEMENT SYSTEM\n");
    printf("\n\n\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\tCHECK DETAILS MENU\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n");
    printf("\t\tEnter your student id:\t");
    scanf("%59s",studentIdToFind);
    printf("\n\n");
    printf("\t\tEnter your pin:\t");
    scanf("%4s", pinToFind);
    printf("\n\n");

    struct Account *foundAccount = login(studentIdToFind, pinToFind);

    if (foundAccount != NULL) {
        printf("\t\t━━━━ACCOUNT FOUND:━━━━\n\n");
        printf("\t\tStudent ID: %s\n\n", foundAccount->studentId);
        printf("\t\tGhana ID: %s\n\n", foundAccount->ghanaId);
        printf("\t\tName: %s\n\n", foundAccount->name);
        printf("\t\tBirth Date: %02d/%02d/%04d\n\n", foundAccount->birthDate.day, foundAccount->birthDate.month, foundAccount->birthDate.year);
        printf("\t\tPhone No: %s\n\n", foundAccount->phoneNo);
        printf("\t\tGender: %c\n\n", foundAccount->gender);
        printf("\t\tAddress: %s\n\n", foundAccount->address);
        printf("\t\tPin: %s\n\n", foundAccount->pin);
        printf("\t\tBalance: %.2f\n\n", foundAccount->balance);
        printf("\t\tCreation Date: %02d/%02d/%04d\n\n", foundAccount->creationDate.day, foundAccount->creationDate.month, foundAccount->creationDate.year);
        free(foundAccount);
    } else {
        printf("\t\tAccount not found.\n\n");
    }

    printf("\n\n\n\tSelect an option: \n\n");
    printf("\t\t1. Exit.\n\n");
    printf("\t\t2. Return to main menu.\n\n");
    printf("\t\t3. Change Account details.\n\n");
    printf("\tI want to:\t");
    scanf("%i", &option);
    while (1) {
        switch (option) {
            case 1: 
                exit(0);
                break;
    
            case 2:
                transition();
                menu();
                break;

            case 3:
                transition();
                break;
            default:
                printf("Invalid input. Select one from option 1 to 3");
                break;
        }
        break;
    }
    
    

    return 0;
}
