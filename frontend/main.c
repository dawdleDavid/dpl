#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>


#include "readfile.h"

uint64_t string_lenght(const char* string){
  uint64_t len=0;
  while(string[len] != '\0'){
    len++;
  }
  return len;
}
uint8_t string_compare(const char* a, const char* b){
  if(string_lenght(a) > string_lenght(b)){
    return (string_lenght(a) - string_lenght(b));
  }else if(string_lenght(a) < string_lenght(b)){
    return (string_lenght(b) - string_lenght(a));
  }
  // test if strings are equal in lenght
  for(uint64_t i = 0; i <= string_lenght(b); i++){
    if(a[i] != b[i]){
      return 1;
    }
  }
  return 0;
}

int main(int argc, char* argv[]){

    // check
    if(argc > 2){
        if(string_compare(argc[argv-1], "--version") == 0){
            printf("%s\n", "v0.0002");
            exit(0);
        }
        if(string_compare(argc[argv-2], "-r") == 0){
            FILE* file = readFile(argv[argc-1]);

            if(file == (FILE*)1){
                fprintf(stderr, "could not open file\n");
                exit(1);
            }
            exit(0);
        }
    }else{
        fprintf(stderr, "to few arguments\n");
    }
    // start parsing the file


    return 0;
}
