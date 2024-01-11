#include <stdio.h>
#ifndef NEW_ACCOUNT_H
#define NEW_ACCOUNT_H 
struct Date {
    int month, day, year;
};

struct Account {
    //identification
    char studentId[9];
    char ghanaId[20];

    //personal information
    char name[60];
    struct Date birthDate;
    char phoneNo[11];
    char gender;
    char address[12];

    char pin[5];
    float balance;
    struct Date creationDate;
};

void menu(void);
void transition(void);
void loadingAnimation(void);
#endif