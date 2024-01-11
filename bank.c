#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
#include "new_account.h"
#include "check_details.h"
#include "delete.h"

void menu();

int main() {
    menu();
    
}
void loadingAnimation() {
    printf("\tLoading");
    fflush(stdout); // the string in printf is first stored in the buffer
    // this prevents it from being stored and render immediately

    for (int i = 0; i < 4; ++i) {
        usleep(500000); // 0.5-second delay
        printf(".");
        fflush(stdout); 
    }

    printf("\n");
}
void transition() {
    system("cls");
    printf("\n\tTransitioning to the next screen...\n");
    loadingAnimation();
    system("cls");
}

void menu(void) { 
    int option; // the user's choice will be saved here.
    while(1) {
        system("cls"); // this clears up the terminal 
        system("color 02"); // this chooses the color 
        
        printf("\n\n\tCOMPUTERIZED  BANK MANAGEMENT SYSTEM\n");
        printf("\n\n\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\t\tMAIN MENU\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        printf("\n\n\tPlease select an option:");
        printf("\n\n\t\t1. Create a new account.");
        printf("\n\n\t\t2. Update the information of an existing account.");
        printf("\n\n\t\t3. Make transactions.");
        printf("\n\n\t\t4. Check the details of an existing account.");
        printf("\n\n\t\t5. Delete an existing account.");
        printf("\n\n\t\t6. Exit.");
        printf("\n\n\n\tThanks for choosing us :)");
        printf("\n\n\n");

        printf("\tI want to:\t");
        scanf("%d", &option); // takes the user's option
        printf("\n\n");

        switch(option) {
            case 1:
                transition();
                create_new_acc();
                break;
            case 2:
                transition();        
                
                break;
            case 3:
                transition();
                break;
            case 4:
                transition();
                check_details();
                break;
            case 5:
                askToDelete();
                transition();
                break;
            case 6:
                system("cls");
                exit(0);
                break;
            default:
                
                printf("Invalid option\n Choose an option from 1 to 6\n\n");
                Sleep(5000); // 0.5-second delay
                continue;
        }
        break;
    }
}

