#ifndef MEM_H
#define MEM_H

union Numbers{
    int integer;
    float floatingpoint;
};
union Strings{
    char* string; // yet to be allocated
};
union Stack{    // sizeof union pointer
    union Strings* strings;
    union Numbers* numbers;
};
// functiondefs


void* mtplAllocate();
void* mtplFree();


#endif
