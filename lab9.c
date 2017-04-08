//Hyunseung Do
//31 March 2017
//CIS2107
//Lab 9
//Practice on writing functions for String processing

//header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    FILE * fp; //this is the file pointer to the sherlock.txt
    FILE * fp2;

    //gotta make sure the file is able to be opened first
    if ((fp = fopen("sherlock.txt", "r+")) == NULL){ //the file pointer opens the file in update mode (read and write)
        puts("Can't find the file!");       
        exit(1);
    } 
    
    fp2 = fopen("new.txt", "w+");

    char sentence[1000]; //this is the char array that contains the quotation

    fscanf(fp, "%*[^\"]%c", sentence);
    int pos1 = ftell(fp);
    printf("%s\n", sentence);
    fscanf(fp, "%*[^\"]%c", sentence);
    int pos2 = ftell(fp);
    printf("%s\n", sentence);
    printf("%d %d\n", pos1, pos2);
     
    fscanf(fp, "%*[^\"]%c", sentence);
    int pos3 = ftell(fp);
    printf("%s\n", sentence);
    fscanf(fp, "%*[^\"]%c", sentence);
    int pos4 = ftell(fp);
    printf("%s\n", sentence);
    printf("%d %d\n", pos3, pos4);


    fclose(fp); //always close the pointer
    fclose(fp2);
}

/* 
 * %*[^\"]%c
 *
 * %*[^\"] reads from stream until \ is encountered. it stops right before
 * %c reads the actual \
 * */
