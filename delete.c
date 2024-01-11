#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bank.h"
#include "check_details.h"
#include "delete.h"

int delete_account(char *file_path, char* idToDelete) {
    FILE *originalFile = fopen(file_path, "r");
    FILE *newFile = fopen("temp.csv", "w");

    if (originalFile == NULL || newFile == NULL) {
        fprintf(stderr, "\n\tError opening files.\n");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    while (fgets(line, 1024, originalFile) != NULL) {
        char* token = strtok(line, ",");
        if(token!=NULL && strcmp(token, idToDelete) != 0) {
            fputs(line, newFile);
        }
    }
    fclose(originalFile);
    fclose(newFile);

    if (remove(file_path) != 0 || rename("temp.csv", file_path) != 0) {
        fprintf(stderr, "Error updating the file.\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int askToDelete() {
    char idToDel[9];
    char pinToDel[5];
    
    
    printf("\n\n\tCOMPUTERIZED  BANK MANAGEMENT SYSTEM\n");
    printf("\n\n\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\tCHECK DETAILS MENU\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n\t\tEnter your student id:\t");
    scanf("%8s",idToDel);
    printf("\n\n\t\tEnter your pin:\t");
    scanf("%4s", pinToDel);
    

    struct Account *foundAccount = login(idToDel, pinToDel);
    if(foundAccount!= NULL) {
        char option;
        
        do {
            printf("\n\n\tAre you sure you want to delete your account? y/n:\t");
            scanf(" %c", &option);
            if(option == 'y') {
                int del = delete_account("all_account.csv", idToDel);
                if(del == 0) {
                    printf("\n\n\tAccount has successfully been deleted.\nIt was nice having you\n\n");
                    exit(0);
                }
                else {
                    printf("\n\n\tAccount couldn't be deleted.");
                    menu();
                }
            }
            else if(option == 'n') {
                menu();
            }
            else {
                printf("\n\n\tEnter a valid response.");
            }
        } while(option !='y'|| option !="n");
    }
}


