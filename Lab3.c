/**
 * This program reads a text file and write words and their frequencies to another file.
 * The file name is provided using command line arguments. If the file name is not 
 * provided or the file is not readable, the program will exit and provide an error message.
 *
 * @author Liyao Zhang {@literal <zhanl217@wfu.edu>}
 * @date Oct. 5, 2020
 * @assignment Lab 3
 * @course CSC 250
 **/
 
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* global type and constant definitions */
#define MAX_STRING 20

typedef struct{
    char* word;
    int count;
} WordFreq;

/* function declarations */
void readFile(char* filename, char* output);
void sort(WordFreq* word_list, int num_words, char* output);
void printFreq(WordFreq* word_list, int num_words, char* output);

int main(int argc, char* argv[])
{
    char* filename = argv[1];
    char* output = argv[2];
    if(argc < 2){
        printf("Usage: %s filename \n", argv[0]);
        return 1;
    }
    
    readFile(filename, output);
    return 0;
}

void readFile(char* filename, char* output)
{
    int i;
    char ch;
    char buffer[MAX_STRING];
    FILE *file_ptr;
    int count = 0;
    WordFreq* word_list = NULL;
    int num_words = 0;
    int index = -1;
    
    /* read file and process one word at a time */
    file_ptr = fopen(filename, "r");
    if(!file_ptr){
        printf("Error -- Couldn't open file\n");
        exit(-1);
    }
    word_list = calloc(num_words, sizeof(WordFreq));
    while((ch = fgetc(file_ptr)) != EOF){
        if(isalpha(ch) && count <= 18){
            ch = tolower(ch);
            buffer[count] = ch;
            count++;
        }
        else if(!(isalpha(ch)) || count == 19){
            buffer[count] = '\0';
            
            /* skip null buffer */
            if(buffer[0] != '\0'){
                /* check if the word exists */
                for(i = 0; i < num_words; i++){
                    if(strcmp(word_list[i].word, buffer) == 0){
                        index = i;
                    }
                }
                
                /* new word found */
                if(index == -1){
                    num_words++;
                    word_list = realloc(word_list, num_words*sizeof(WordFreq));
                    word_list[num_words-1].word = malloc((count+1)*sizeof(char));
                    word_list[num_words-1].count = 0;
                    strcpy(word_list[num_words-1].word, buffer);
                    word_list[num_words-1].count++;
                }
                else{
                    word_list[index].count++;
                }
            }
            
            /* reset buffer and other indicators */
            for(i = 0; i < count; i++){
                buffer[i] = ' ';
            }
            count = 0;
            index = -1;
        }
        
    }
    fclose(file_ptr);
    printf("%s has %d unique words\n", filename, num_words);
    sort(word_list, num_words, output);
}

void sort(WordFreq* word_list, int num_words, char* output)
{
    int i,j;
    for(j = 0; j < num_words-1; j++){
        for(i = 0; i < num_words-1; i++){
            if(word_list[i].count < word_list[i+1].count){
                WordFreq Temp = word_list[i];
                word_list[i] = word_list[i+1];
                word_list[i+1] = Temp;
            }
        }
    }
    printFreq(word_list, num_words, output);
}

void printFreq(WordFreq* word_list, int num_words, char* output)
{
    int i;
    FILE *file_ptr;
    file_ptr = fopen(output, "w");
    for(i = 0; i < num_words; i++){
        fprintf(file_ptr, "%s %d\n", word_list[i].word, word_list[i].count);
        /* free memory */
        free(word_list[i].word);
    }
    free(word_list);
    fclose(file_ptr);
}
