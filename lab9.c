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

    //gotta make sure the file is able to be opened first
    if ((input = fopen("sherlock.txt", "r+")) == NULL){ //the file pointer opens the file in update mode (read and write)
        puts("Can't find the file!");       
        exit(1);
    } 

    //the output is created if not existing and overwritten every time
    output = fopen("southie-sherlock.txt", "w+");
    char sentence[5000]; //this is the char array that contains the quotation
    char non[5000];

    //this is required to get the first part of non quotation
    fscanf(input, "%[^\"]", non);
    fprintf(output, "%s", cleanQuote(non));

    int multi = 0; //this tracks if the quotation is multiparagraph

    //this will loop through the whole text
    //while printing back and forth between
    //quote and non-quote
    while (!feof(input)){ //go through the text file until EOF
        fscanf(input, "\"%[^\"]\"", sentence); //store dialogues without quotation marks into sentence array
        //loop through the whole dialogue to check for multi-paragraph. 
        //multi-paragraph:
        // " jdsfklafdskjflafjlk
        //   skfjlsadkjfslfksajf
        //   jdsakflsafkdsjf.
        //
        // " jdsfkljsaldskfjsflsakf
        //   sjkfldsakjfljlfkjflsak
        //   dslkflsakjfdsfkdsajflfkj."
        //
        //   as shown above, there are multiple quotation marks for one dialogue.
        //   this messes up the scanner format for dialogue
        int i;
        for (i = 0; i < 5000; i++){ 
            if (sentence[i] == '\r' && sentence[i + 1] == '\r'){ //if the extracted is multiparagraph
                sentence[i] = '\0'; //end the extraction after the punctuation mark
                //the input pointer is currently at the middle quotation mark
                //the pointer needs to go back 
                //so that the space between the end of paragraph and next paragraph
                //can be extracted
                fseek(input, -3, SEEK_CUR); 
                multi = 1; //this is used to indicate that this is part of multi-paragraph
            }
        }
        
        //if multi-paragraph, don't print out quotation mark at end
        fprintf(output, multi ? "\"%s" : "\"%s\"", cleanQuote(sentence));

        //this scans for text between quotation marks
        fscanf(input, "%[^\"]", non);
        fprintf(output, "%s", cleanQuote(non));
        multi = 0; //tracker reset
    }

    fclose(input); //always close the pointer
    fclose(output);
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

//this function takes in the dialogue without quotation mark
//and changes certain words into southie accent
char * changeQuote(char quote[]){
}
