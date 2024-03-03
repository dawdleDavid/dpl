#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>

// debug
#include <assert.h>
// unit testing
#include <check.h>

#include "../head/heap.h"
#include "../head/parser.h"
#include "../head/strings.h"




const char* vardefs[10] = {
    "int8 ",
    "int16 ",
    "int32 ",
    "int64 ",
    "uint8 ",
    "uint16 ",
    "uint32 ",
    "uint64 ",
    "float ",
    "lfloat ",
};

// returns memory that has to be free'd
struct Tape* findKeyword(struct Tape* memwrap, char* buffer){
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
    int i = 0; // ha, didn't know that works...
    for(;i <= ROW_LIMIT; i++){
        strcpy(memwrap->words_list[i], words_list[i]);
        if(strstr(memwrap->words_list[i], "\n") != NULL){
            break;
        }
    }
    return memwrap;
}
// defacto main function of the parser!
void mtplParse(FILE* file){
    struct Tape memwrap; struct Tape* memwrap_p;

    if(file == (FILE*)NULL){
        perror("");
    }

    puts("we ran this..");
    char buffer[ROW_LIMIT];


    uint32_t p_counter = 0;




    /* Acctual parsing starts here... */
    while(true){
        char* row = fgets(buffer, ROW_LIMIT, file);

        p_counter++;
        printf("PC: %d\n", p_counter);
        if(row == (char*)NULL){
            printf("EOF\n");
            break;
        }
            // do something with the line that you just got
        memwrap_p = findKeyword(&memwrap, row);
        char varc[ROW_LIMIT];
        // extract value from string

        for( int index = 0;index <= ROW_LIMIT; index++){
            printf("%s\n", memwrap_p->words_list[index]);



            assert(memwrap_p->words_list[index] != NULL);

            if(strstr(memwrap_p->words_list[index], "\n") != NULL){
                break;
            }
            for(int vari = 0; vari <= 9; vari++){ /* assert for the win i guess!*/
                assert(vardefs[vari] != NULL);
                if(strcmp(memwrap_p->words_list[index], vardefs[vari]) == 0){ // oh, i guess that space is to my
                    if(index < ROW_LIMIT){
                        strcpy(varc, memwrap_p->words_list[index+1]);
                        break;
                    }

                }
            }
        }

        printf("->%s\n", varc);
    }//endwhile
}
