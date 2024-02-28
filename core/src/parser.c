#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include "../head/parser.h"
#include "../head/strings.h"
#include <string.h>
#include <stdbool.h>
/*
    Convert the data from string
    form to numbers that are
    easy to work with. data is
    expected to come in the form
    OPERATOR OPERAND.
*/

// debug
#include <assert.h>
// unit testing
#include <check.h>



const char* key[4] = {
    "INTEGER",
    "FLOAT",
    "IF",
    "END"
};

struct Memwrap{
    char words_list[ROW_LIMIT][ROW_LIMIT];
};

// returns memory that has to be free'd
struct Memwrap* findKeyword(struct Memwrap* memwrap, char* buffer){
    char word[ROW_LIMIT]; char words_list[ROW_LIMIT][ROW_LIMIT];

    int walk = -1,words=0;

    int word_index = 0;

    for(int character = 0; character <= strlen(buffer); character++){
        walk++;
        if(buffer[character] == ' ' || buffer[character] == '\n'){
            for(int index = (character-walk); index <= character; index++){
                word[word_index] = buffer[index];
                word_index++;
            }
            strcpy(words_list[words], word);
            words++;

            // clean the array...

            for(int i = 0; i <= ROW_LIMIT; i++){
                word[i] = (char)0;
            }

            walk = 0; word_index = 0;
        }

    }
    for(int i = 0; i <= ROW_LIMIT; i++){
        strcpy(memwrap->words_list[i], words_list[i]);
    }
    return memwrap;
}
// defacto main function of the parser!
void mtplParse(FILE* file){

    struct Memwrap memwrap; struct Memwrap* memwrap_p;

    if(file == (FILE*)NULL){
        perror("");
    }

    puts("we ran this..");
    // first pass, preprocessing...
    char buffer[ROW_LIMIT];

    //char* word;
    //while(true){


    char* row = fgets(buffer, 256, file);

    if(row == (char*)NULL){
        printf("end\n");
            //break;
    }
        // do something with the line that you just got
    memwrap_p = findKeyword(&memwrap, row);



    printf("%s\n", memwrap_p->words_list[0]);
    //}
}
