//Hyunseung Do
//31 March 2017
//CIS2107
//Lab 9
//Practice on writing functions for String processing

//header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findNextQuote(FILE *fPtr);

int main(void){
    FILE * fp; //this is the file pointer to the sherlock.txt

    //gotta make sure the file is able to be opened first
    if ((fp = fopen("sherlock.txt", "r+")) == NULL){ //the file pointer opens the file in update mode (read and write)
        puts("Can't find the file!");       
        exit(1);
    } 
    char sentence[1000]; //this is the char array that contains the quotation
    
    //finding the location of quotation marks
    fscanf(fp, "%*[^\"]%c", sentence); //search until quotation mark
    int pos = ftell(fp); //gets the location of it
    fscanf(fp, "%*[^\"]%c", sentence); //search until another quotation mark
    int pos2 = ftell(fp); //gets the location of it
    int pos3 = findNextQuote(fp);
    int pos4 = findNextQuote(fp);
    printf("%d %d\n", pos, pos2); //testing the locations of quotation marks
    printf("%d %d\n", pos3, pos4); //testing the locations of quotation marks

    fseek(fp, pos, SEEK_SET);
    fgets(sentence, pos2 - pos, fp);
    printf("%s\n", sentence);
    memset(sentence, 0, sizeof(sentence));

    fseek(fp, pos3, SEEK_SET);
    fgets(sentence, pos4 - pos3, fp);
    printf("%s\n", sentence);
    
    /* //use memset to directly change the letters of the word */ 
    /* memset(sentence, 'h', 7); */
    /* printf("%s\n", sentence); //testing the effect of memset */

    fclose(fp); //always close the pointer
}

int findNextQuote(FILE *fPtr){
    FILE *ptr = fPtr;
    char trash[2];
    fscanf(ptr, "%*[^\"]%c", trash);
    return ftell(ptr);
}
