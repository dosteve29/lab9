//Hyunseung Do
//31 March 2017
//CIS2107
//Lab 9
//Practice on writing functions for String processing

//header files
#include <stdio.h>

int main(void){
    FILE * textPtr; //this is the file pointer to the sherlock.txt
    /* FILE * outPtr; //this is the file pointer to the output.txt */

    textPtr = fopen("sherlock.txt", "r+");

    fclose(textPtr);
}
