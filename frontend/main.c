

#include "readfile.h"





int main(int argc, char* argv[]){

    // check


    if(argv[argc-1] == NULL){
        return 1; // exit fail
    }
    FILE* file = readFile(argv[argc-1]);


    // start parsing the file


    return 0;
}
