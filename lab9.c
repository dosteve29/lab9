//Hyunseung Do
//31 March 2017
//CIS2107
//Lab 9
//Practice on writing functions for String processing

//header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * cleanQuote(char quote[]); //replaces '\r' with '\n'

int main(void){
    FILE * input; //this is the file pointer to the sherlock.txt
    FILE * output; //this is the file pointer to the new.txt, the output text with the Southie accent dialogues

    //gotta make sure the file is able to be opened first
    if ((input = fopen("sherlock.txt", "r+")) == NULL){ //the file pointer opens the file in update mode (read and write)
        puts("Can't find the file!");       
        exit(1);
    } 
    
    output = fopen("southie-sherlock.txt", "w+");
    char sentence[5000]; //this is the char array that contains the quotation

    fscanf(input, "%*[^\"]%c", sentence);
    int pos1 = ftell(input);
    rewind(input);

    fprintf(output, "%s", cleanQuote(fgets(sentence, pos1, input)));
    pos1 = ftell(input);
    printf("%d\n", pos1);

    

    fclose(input); //always close the pointer
    fclose(output);
}

/* 
 * %*[^\"]%c <= to get the quotation mark in the beginning
 * %*[^\"]\"%[^\"] <= to get the dialogue in the quotation without the quotation marks
 *
 * %*[^\"] reads from stream until " is encountered. it stops right before
 * %c reads the actual "
 * */

//the text file uses carriage-return character, '\r' to make new line
//however, this creates interruption with printf
//the function replaces '\r' with '\n' in given char array
char * cleanQuote(char quote[]){
    int i;
    for (i = 0; i < 5000; i++){
        if (quote[i] == '\r'){
            quote[i] = '\n';
        }
    }

    return quote;
}
