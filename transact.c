#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bank.h"
#include "check_details.h"
#include "modify_details.h"

int transact() {

    char idToTransact[9];
    char pinToTransact[5];

    printf("\n\n\tCOMPUTERIZED  BANK MANAGEMENT SYSTEM\n");
    printf("\n\n\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\t\tMAKE TRANSACTIONS\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n\tEnter your student id:\t");
    scanf("%8s", idToTransact);

    printf("\n\n\tEnter your pin:\t");
    scanf("%4s", pinToTransact);
    struct Account *accToTransact = login(idToTransact, pinToTransact);

    if(accToTransact != NULL) {
        printf("\n\n\tLogin successful.");
    }
    else{
        printf("\n\n\tUnable to login.");
        menu();
    }


    int option;

    printf("\n\n\tSelect an option:");
    printf("\n\n\t\t1. Make deposit.");
    printf("\n\n\t\t2. Make withdrawal.");

    printf("\n\n\t\t3. Return to main menu");

   
    do
    {
        printf("\n\n\tI want to:");
        if(scanf("%i", option) != 0) {
            printf("\n\n\tInvalid input. Enter a numeric response from 1-3");
        }
        if(option == 1) {
            break;
        }
        else if(option == 2) {
            break;
        }
        else if (option ==3) {
            menu();
        }
        else{
            printf("\n\n\t Enter a valid response.");
        }
    } while (option !=1 || option !=2 || option!=3);
    
}