#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>



#include <stdint.h>



#include <stdlib.h>

enum{
    HEAP_ADD,
    HEAP_REMOVE,
    HEAP_FIND,
    HEAP_LIST
};



// i will not regret making all of these macros, macros are awesome! -John Noob



#define MAX_VARIABLE_NAME_LENGHT 64
unsigned int HEAP_HashVaribleName(char name[MAX_VARIABLE_NAME_LENGHT]){
    unsigned int res = 0;
    for(int c = 0; c <= strlen(name); c++){
        res += (unsigned int)name[c]; // this is dumb... reversed varible names anyone, no?
    }
    return res;
}


// MINNE
void* mem_alloc(void* data, int size){


    void *ptr = mmap ( NULL, size,
      PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );

    if(ptr == (void *)-1){
        puts("memory allocation failed");
        return (void *)-1;
    }
    memcpy(ptr, data, size);   // KOPIERA ÖVER MINNET, ALERT: SEGFAULT! (chorus of spaceballs theme) (no longer but props soon again <--)
    return ptr;
}


int mem_free(void* ptr, long int size){
    if(munmap(ptr, size) == 0){
        printf("dealloc %ld bytes, ptr points to adress: %p\n", size, ptr);
        return 0;
    }return 1;
}

struct Node{
    void* data;
    struct Node* next;
    unsigned int name;
}node_r;
// TEST DATA
struct Nodes{
    struct Node* start;
    int number_of_nodes;
    struct Node* node;
}nodes_r;
/* This is not a good idea, but i will do it anyway because I kinda like it*/

struct MTPL_Heap{
    int number_of_nodes;
    struct Nodes* nodes;
    struct Node* start;
    struct Node* JariPekare;
    struct Node* node;
    struct Node* prev;
};typedef struct MTPL_Heap MTPL_Heap;

// might aswell use fast, because union is going to be size of biggest data type, and we are going to alloc and truncate.
// watch out for that actualy, that might turn out to be an issue
union MTPL_Variable{
    // signed integer types
    int8_t int8;
    int16_t int16;
    int32_t int32;
    int64_t int64;
    // unsigned integer types
    uint8_t uint8;
    uint16_t uint16;
    uint32_t uint32;
    uint64_t uint64;

    // string type
    char* string; /* dynamic alloc */
    // char
    char character;
    // float types
    float float_t;
    double double_t;
};typedef union MTPL_Variable MTPL_Variable;
/*
    We also need to check what the architecture that we are on supports!
*/
#define INTEGER_8_TYPE 1
#define INTEGER_16_TYPE 2
#define INTEGER_32_TYPE 3
#define INTEGER_64_TYPE 4
#define UNSIGNED_INTEGER_8_TYPE 5
#define UNSIGNED_INTEGER_16_TYPE 6
#define UNSIGNED_INTEGER_32_TYPE 7
#define UNSIGNED_INTEGER_64_TYPE 8
#define STRING_TYPE 9
#define CHARACTER_TYPE 10



#define INTEGER_8_SIZE sizeof(int8_t)
#define INTEGER_16_SIZE sizeof(int16_t)
#define INTEGER_32_SIZE sizeof(int32_t)
#define INTEGER_64_SIZE sizeof(int64_t)
#define UNSIGNED_INTEGER_8_SIZE sizeof(uint8_t)
#define UNSIGNED_INTEGER_16_SIZE sizeof(uint16_t)
#define UNSIGNED_INTEGER_32_SIZE sizeof(uint32_t)
#define UNSIGNED_INTEGER_64_SIZE sizeof(uint64_t)









// and yet more defines
int number_of_nodes = 0;



struct Nodes* nodes = &nodes_r;
struct Node* start;
struct Node* JariPekare;
struct Node* node = &node_r;
struct Node* prev;

struct Node* LL_Create(void* pointer,char name[MAX_VARIABLE_NAME_LENGHT]){
    bool prev_flag = false;
    // good or bad,  to * or not to *, that is the biggest question off them all too mediocre C programmers
    if(number_of_nodes > 1){
        prev_flag = true;
    }
    if(prev_flag)
        prev = nodes->node;
    nodes->node = (struct Node*)mem_alloc(&nodes->node, sizeof(*nodes->node));
    if(prev_flag)
        prev->next = nodes->node;
    // // HACK (:<
    if(number_of_nodes == 1){ // if this is the first node
        start = nodes->node;
    }else if(number_of_nodes == 2){
        start->next = nodes->node;
    }
    nodes->node->data = pointer;
    nodes->node->name = HEAP_HashVaribleName(name);
    nodes->node->next = start;
    return start;
}
int LL_List(int n, struct Node* start){
    // puts("yee");
    struct Node* node = start;

    // puts("haw");
    for(int i = 1; i <= n; i++){
        // puts("boys");
        printf("N:(%d) CONTAINED_POINTER:%p VARIBLE_NAME_HASHED:%u\n", i, node->data, node->name);
        if(i == 1){
            node = start->next;
            continue;
        }

        node = node->next;
    }
    if(n == 0){
        puts("no nodes!");
    }

    return 0;
}

int LL_Remove(int n, struct Node* start, int choice){
    LL_List(n, start);

    struct Node* node = start;
    for(int i = 1; i <= n; i++){
        printf("(%d) %p %p\n", i, &node->data, node->data);
        if(i == (choice-1)){
            puts("ran");
            struct Node* temp = node->next;     // skapa temporär pekare till nästa nod
            node->next = temp->next;           //  flytta nuvarande nods pekare till temp
            mem_free(&temp, sizeof(*temp));   //   fria minnet för temp;
            break;
        }
        node = node->next;
    }
    n--;
    return n;
}



MTPL_Heap* HEAP_Main(unsigned int opcode, void* data_ptr, char varname[MAX_VARIABLE_NAME_LENGHT]){
    unsigned int choice = 0;
        puts("\n");
        switch(opcode){
            case HEAP_ADD:
                number_of_nodes++; // one at a time
                start = LL_Create(data_ptr, varname);
                break;
            case HEAP_LIST:
                LL_List(number_of_nodes, start);
                break;

            case HEAP_REMOVE:
                LL_List(number_of_nodes, start);
                printf("Witch list would you like to remove?: ");
                scanf("%d", &choice);
                if(choice == 1){
                    JariPekare = start->next;
                    mem_free(start, sizeof(node));
                    start = (struct Node*)JariPekare;
                    printf("\n\n%p\n", start);

                    number_of_nodes--;
                    break;
                }
                puts("ran LL_Remove");
                number_of_nodes = LL_Remove(number_of_nodes, start, choice);
                break;

            case HEAP_FIND:
                choice = HEAP_HashVaribleName(varname);
                struct Node* node = start;
                for(int i = 1; i <= number_of_nodes; i++){
                    if(choice == node->name){
                        // Edit struct and return



                        printf("N:(%d) CONTAINED_POINTER:%p VARIBLE_NAME_HASHED:%u\n", i, node->data, node->name);
                        break;
                    }
                    if(i == 1){
                        node = start->next;
                        continue;
                    }
                    node = node->next;
                }
                break;
        }
    return (MTPL_Heap*)0;
}

/*

struct Nodes* nodes = &nodes_r;
struct Node* start;
struct Node* JariPekare;
struct Node* node = &node_r;
struct Node* prev;

 */
MTPL_Heap* HEAP_Init(){

    struct Node node;
    struct Nodes nodes;


    MTPL_Heap* heap = (MTPL_Heap*)mem_alloc(heap, sizeof(MTPL_Heap));

    heap->nodes = &nodes;
    heap->node = &node;
    heap->number_of_nodes = 0;


    return heap;
}

uint_least8_t HEAP_Add(uint_least8_t vartype, uint_least8_t size, MTPL_Variable* variable){

    // ALLOC mem
    void* variable_mem = (void*)mem_alloc(variable_mem, size);
    // Check mem
    if(variable_mem == (void *)-1){
        return 1;
    }
        // gigant switch statement time?
    switch(vartype){
        case INTEGER_8_TYPE:

            break;
        case INTEGER_16_TYPE:

            break;
        case INTEGER_32_TYPE:

            break;
        case INTEGER_64_TYPE:

            break;
        case STRING_TYPE:

            break;
        case CHARACTER_TYPE:

            break;

    }

    // put value in mem
    memcpy(variable_mem, )

    if(HEAP_Main(HEAP_ADD, variable_mem, "43") == 0){
        return 0;
    }
    return 1;
}
int HEAP_Remove(){


    return 0;
}
int HEAP_Clean(){
    return 0;
}


int HEAP_Get(char name[MAX_VARIABLE_NAME_LENGHT]){



    return 0;
}




int main(int argc, char* argv[]){

    /* just cut your losses and use malloc... TODO: Remove the illgal!*/
    void* void_ptr = malloc(SIZE_INTEGER);
    void* new = malloc(SIZE_INTEGER);



    //void* data_ptr = (void*)0x456;
    HEAP_Main(HEAP_ADD, void_ptr, "43");
    HEAP_Main(HEAP_ADD, new, "anothertest");
    HEAP_Main(HEAP_ADD, void_ptr, "test");
    HEAP_Main(HEAP_ADD, void_ptr, "eat my");

    HEAP_Main(HEAP_FIND, void_ptr, "43");



    HEAP_Main(HEAP_LIST, NULL, NULL);


    free(void_ptr);
    free(new);

    return 0;
}
// (cd /home/david/Projekts/GY-EX && git add --all && git commit -m "för om gör rätt" && git push -u origi master)
// https://developers.redhat.com/articles/the-gdb-developers-gnu-debugger-tutorial-part-1-getting-started-with-the-debugger
// gcc heap_test.c -g -g3 -o heap -O0
