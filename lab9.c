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

//function prototypes
char * cleanQuote(char quote[]); //replaces '\r' with '\n'
void changeQuote(char quote[], FILE * output);
int isVowel(char c); //returns 1 if vowel, 0 if non-vowel

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
    char non[5000]; //this is the char array that contains the text other than dialogue

    //this is required to get the first part of non quotation
    fscanf(input, "%[^\"]", non);
    fprintf(output, "%s", cleanQuote(non));

    int multi = 0; //this tracks if the quotation is multiparagraph

    //this will loop through the whole text after the initial non-quote
    //while printing back and forth between
    //quote and non-quote
    while (!feof(input)){ //go through the text file until EOF
        fscanf(input, "\"%[^\"]\"", sentence); //store dialogues without quotation marks into sentence array
        //
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
        //

        //loop through the whole dialogue (sentence char array) to check for multi-paragraph. 
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
        if (multi == 1){
            fprintf(output, "\"");
            changeQuote(cleanQuote(sentence), output);
            fseek(output, -1, SEEK_CUR); 
        }
        else{
            fprintf(output, "\"");
            changeQuote(cleanQuote(sentence), output);
            fseek(output, -1, SEEK_CUR); 
            fprintf(output, "\"");
        }

        /* //this scans for text between quotation marks */
        fscanf(input, "%[^\"]", non);
        fprintf(output, "%s", cleanQuote(non));
        multi = 0; //tracker reset
    }

    //always close the pointer
    fclose(input); 
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
void changeQuote(char quote[], FILE * output){
    //split the quotation into tokens
    char * token;

    //the delimiter is newline and whitespace
    token = strtok(quote, " \n");

    //go through every word
    while (token != NULL){
        int n = strlen(token); //length of token
        char word[n + 3]; //the converted word
        int punc = 0; //tracker if word has punctuation at end
        char punctuation[100]; //contains the punctuation at the end of word

        //if there is punctuation at the end
        if (ispunct(token[n - 1])){
            punc = 1; //mark the loop that it has punctuation
            punctuation[0] = token[n - 1]; //get the punctuation
            punctuation[1] = '\0'; //null-terminating to complete the construction of string 
            strcpy(word, token); //copy the word
            word[n - 1] = '\0'; //remove the punctuation so it doesn't mess with southie accent conversion
        }
        else{
            punc = 0; //no punctuation
            strcpy(word, token); //resume regularly
        }

        int m = strlen(word); //new length of the word
        
        //this is basically the if-else branch for basic rules and exceptions
        //for southie-accent
        //pretty self-explanatory
        if (strstr(token, "very") != NULL){
            strcpy(word, "wicked");
            //adds punctuation at end if the tracker says so
            if (punc){
                strcat(word, punctuation);
            } 
        } 
        else if (strstr(token, "Very") != NULL){
            strcpy(word, "Wicked");
            if (punc){
                strcat(word, punctuation);
            }
        }
        else if (word[m - 1] == 'a' && m != 1){
            char add[] = "r";
            strcat(word, add);
            if (punc){
                strcat(word, punctuation);
            }
        }
        else if (word[m - 1] == 'r' && word[m - 2] == 'o' && word[m - 3] == 'o'){
            word[m - 1] = '\0';
            char add[] = "wah";
            strcat(word, add);
            if (punc){
                strcat(word, punctuation);
            } 
        }
        else if (word[m - 1] == 'R' && word[m - 2] == 'O' && word[m - 3] == 'O'){
            word[m - 1] = '\0';
            char add[] = "WAH";
            strcat(word, add);
            if (punc){
                strcat(word, punctuation);
            } 
        }
        else if (word[m - 1] == 'r' && word[m - 2] == 'e' && word[m - 3] == 'e'){
            word[m - 1] = '\0';
            char add[] = "yah";
            strcat(word, add);
            if (punc){
                strcat(word, punctuation);
            } 
        }
        else if (word[m - 1] == 'R' && word[m - 2] == 'E' && word[m - 3] == 'E'){
            word[m - 1] = '\0';
            char add[] = "YAH";
            strcat(word, add);
            if (punc){
                strcat(word, punctuation);
            } 
        }
        else if (word[m - 1] == 'r' && word[m - 2] == 'i'){
            word[m - 1] = '\0';
            char add[] = "yah";
            strcat(word, add);
            if (punc){
                strcat(word, punctuation);
            }
        }
        else if (word[m - 1] == 'R' && word[m - 2] == 'I'){
            char add[] = "YAH";
            word[m - 1] = '\0';
            strcat(word, add);
            if (punc){
                strcat(word, punctuation);
            }
        }
        else if (strchr(word, 'r') != NULL){
            int i;
            for (i = 1; i < m; i++){
                if (word[i] == 'r' && isVowel(word[i - 1])){
                    word[i] = 'h';
                }
            }            

            if (punc){
                strcat(word, punctuation);
            }
        }
        //no changes to be done.
        else{
            strcpy(word, token);
        }
        //write the word to the output file
        fprintf(output, "%s ", word);
        token = strtok(NULL, " \n"); //advance to the next tokenized word
        //reset the jawns
        memset(word, 0, sizeof word);
        memset(punctuation, 0, sizeof punctuation);
        punc = 0;
    }    
}

//returns 1 if vowel, 0 if non-vowel
int isVowel(char c){
    switch(c){
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            return 1;
        default:
            return 0;
    }
}
