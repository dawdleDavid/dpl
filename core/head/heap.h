#ifndef HEAP_H
#define HEAP_H

struct Varible_s{
    void* data;
    unsigned char type; // types as found in the enum
    struct Varible_s* next;
};
struct Varibles_s{
    struct Varible_s* start;
    int number_of_Varibles_s;
    struct Varible_s* Varible_s;
};
void* mem_alloc(void* data, int size);
int mem_free(void* ptr, long int size);
#endif
