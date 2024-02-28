




#include <stdio.h>
#include <stdlib.h>
#include "../head/parser.h"
#include "../head/strings.h"
#include <string.h>
/*
    Convert the data from string
    form to numbers that are
    easy to work with. data is
    expected to come in the form
    OPERATOR OPERAND.
*/

const char* key[4] = {
    "INTEGER",
    "FLOAT",
    "IF",
    "END"
};


// returns memory that has to be free'd
const char* findKeywords(char* buffer){

    const char list[ROW_LIMIT][ROW_LIMIT];    // goodby to memory eff


    char wordbuffer[256];


    int char_counter = 0;
    for(int c = 0; c <= string_lenght((const char*)buffer); c++){


        if(*(buffer + c) == ' '){
            // start reverse search trough the entire string
            for(int reverse = 0; reverse <= char_counter; reverse++){
                // asem chars into string...
                wordbuffer[reverse] = buffer[reverse];
            }
            memcpy(list, buffer, string_lenght(wordbuffer)); // idk, looks like a segfault to me
        }
        // add if not
        char_counter++;

    }
    return list;    // this is some bad stuff
}
// defacto main function of the parser
void mtplParse(FILE* file){

    // first pass, preprocessing...
    char buffer[ROW_LIMIT];

    char** words;
    while(fgets(buffer, sizeof(buffer), file)){
        // do something with the line that you just got

        words = findKeywords(buffer);


        // do stuff with the words of this line

        for(int i = 0; i <= sizeof(words); i++){
            printf("%s", words[i]);
        }

        // free memory associated with words

    }

}

