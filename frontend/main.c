

#include "readfile.h"
#include <stdio.h>
#include <errno.h>



int main(int argc, char* argv[]){

    // check


    if(argv[argc-1] == NULL){
        fprintf(stderr, "no files found, stop");
        return 1; // exit fail
    }
    FILE* file = readFile(argv[argc-1]);


    // start parsing the file


    return 0;
}
