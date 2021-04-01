/**
 * This program reads a text file and prints the top 5 most frequent letters (upper or lower case)
 * and the top 5 most frequent digits that are in the file. If the file has less than 5 unique letters
 * and/or digits the top list is adjusted accordingly. The file name is provided using command line 
 * arguments. If the file name is not provided or the file is not readable, the program will exit
 * and provide an error message.
 *
 * @author Liyao Zhang {@literal <zhanl217@wfu.edu>}
 * @date Sept. 20, 2020
 * @assignment Lab 2
 * @course CSC 250
 **/
#include <ctype.h>
#include <stdio.h>
#define MAX_STRING_SIZE 20
#define MAX_LIST_SIZE 200

struct Char_Freq {
    char ch;
    int count;
};

/* function declarations */
void readFile(char* filename);
void sort(struct Char_Freq Letter[], struct Char_Freq Digit[]);
void printFreq(struct Char_Freq Letter[], struct Char_Freq Digit[]);


void readFile(char* filename){
    int i, j;
    struct Char_Freq Letter[26];
    struct Char_Freq Digit[10];
    char ch;
    FILE *file_ptr;
    
    /* initialize struct values */
    for(i = 0; i < 26; i++){
        Letter[i].ch = (char) (i + 'a');
        Letter[i].count = 0;
    }
    
    for(j = 0; j < 10; j++){
        Digit[j].ch = (char) (j + '0');
        Digit[j].count = 0;
    }
    
    /* read file and process one character at a time */
    file_ptr = fopen(filename, "r");
    while((ch = fgetc(file_ptr)) != EOF){
        if(isalpha(ch)){
            ch = tolower(ch);
            Letter[ch - 'a'].count++;
        }
        
        if(isdigit(ch)){
            Digit[ch - '0'].count++;
        }
    }
    
    sort(Letter, Digit);
    
    fclose(file_ptr);
}

void sort(struct Char_Freq Letter[], struct Char_Freq Digit[]){
    int i, j;
    for(j = 0; j < 25; j++){
        for(i = 0; i < 25; i++){
            if(Letter[i].count < Letter[i+1].count){
                struct Char_Freq Temp = Letter[i];
                Letter[i] = Letter[i+1];
                Letter[i+1] = Temp;
            }
        }
    }
    
    for(j = 0; j < 9; j++){
        for(i = 0; i < 9; i++){
            if(Digit[i].count < Digit[i+1].count){
                struct Char_Freq Temp = Digit[i];
                Digit[i] = Digit[i+1];
                Digit[i+1] = Temp;
            }
        }
    }
    
    printFreq(Letter, Digit);
}

void printFreq(struct Char_Freq Letter[], struct Char_Freq Digit[]){
    int i, j, k;
    int mark1 = 5;
    int mark2 = 5;
    for(k = 0; k < 5; k++){
        if(Letter[k].count == 0){
            mark1 = k;
            break;
        }
    }
    
    for(k = 0; k < 5; k++){
        if(Digit[k].count == 0){
            mark2 = k;
            break;
        }
    }
    
    if(mark1 == 0){
        printf("No letters were found \n");
    }
    if(mark2 == 0){
        printf("No digits were found \n");
    }
    
    printf("alpha top %d out of 26 \n", mark1);
    printf("------------------------------------ \n");
    for(i = 0; i < mark1; i++){
        printf("[%c] %d \n", Letter[i].ch, Letter[i].count);
    }
    printf("\n");
    printf("digit top %d out of 10 \n", mark2);
    printf("------------------------------------ \n");
    for(j = 0; j < mark2; j++){
        printf("[%c] %d \n", Digit[j].ch, Digit[j].count);
    }
}

int main(int argc, char* argv[]){
    char* filename = argv[1];
    if(argc < 2){
        printf("Usage: %s filename \n", argv[0]);
        return 1;
    }
    
    readFile(filename);
    return 0;
}
