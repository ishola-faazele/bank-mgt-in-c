/*we start by creating an include guard
to include means to use the declarations of the header file 
in your source file
we don't want to multiple inclusion -- this prevents the declarations of the 
header file from being processed multiple times in the a single source file
*/

#ifndef NEW_ACCOUNT_H
#define NEW_ACCOUNT_H 
#include "bank.h"
void create_new_acc(void);
int write_to_csv(FILE* ,struct Account*);
int valid_input(char*, char*);

#endif