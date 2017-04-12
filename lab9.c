//Hyunseung Do
//31 March 2017
//CIS2107
//Lab 9
//Practice on writing functions for String processing

//header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char * cleanQuote(char quote[]); //replaces '\r' with '\n'
char * changeQuote(char quote[]); //turn normal accent to southie accent

int main(void){
    FILE * input; //this is the file pointer to the sherlock.txt
    FILE * output; //this is the file pointer to the southie-sherlock.txt
    FILE * quote;
    FILE * nonQuote;

    //gotta make sure the file is able to be opened first
    if ((input = fopen("sherlock.txt", "r+")) == NULL){ //the file pointer opens the file in update mode (read and write)
        puts("Can't find the file!");       
        exit(1);
    } 

    //the output is created if not existing and overwritten every time
    output = fopen("southie-sherlock.txt", "w+");
    quote = fopen("quotes.txt", "w+");
    nonQuote = fopen("non.txt", "w+");
    char sentence[5000]; //this is the char array that contains the quotation
    char non[5000];

    //this is required to get the first part of non quotation
    fscanf(input, "%[^\"]", non);
    fprintf(output, "%s", cleanQuote(non));
    fprintf(nonQuote, "%s", cleanQuote(non));

    //this will loop through the whole text
    //while printing back and forth between
    //quote and non-quote
    int multi = 0;
    while (!feof(input)){
        fscanf(input, "\"%[^\"]\"", sentence);
        int i;
        for (i = 0; i < 5000; i++){
            if (sentence[i] == '\r' && sentence[i + 1] == '\r'){
                sentence[i] = '\0';
                fseek(input, -3, SEEK_CUR);
                multi = 1;
            }
        }
        
        fprintf(output, multi ? "\"%s" : "\"%s\"", cleanQuote(sentence));
        fprintf(quote, "%s", cleanQuote(sentence));

        fscanf(input, "%[^\"]", non);
        fprintf(output, "%s", cleanQuote(non));
        fprintf(nonQuote, "%s", cleanQuote(non));

        multi = 0;
    }

    fclose(input); //always close the pointer
    fclose(output);
    fclose(quote);
    fclose(nonQuote);
}


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


char * changeQuote(char quote[]){
}
