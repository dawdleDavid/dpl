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

#define SIZE_INTEGER 4
#define SIZE_FLOAT 4
#define MAX_VARIBLE_NAME_LENGHT 64
unsigned int HEAP_HashVaribleName(char name[MAX_VARIBLE_NAME_LENGHT]){
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
        exit(-1);
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

union Test{
    int mode;

    union Test* ptr;
};
int number_of_nodes = 0; // use like errno?

struct Nodes* nodes = &nodes_r;

struct Node* start = &node_r;

struct Node* JariPekare;

struct Node* node = &node_r;

struct Node* prev;

struct Node* LL_Create(void* pointer,char name[MAX_VARIBLE_NAME_LENGHT]){

    // good or bad,  to * or not to *, that is the biggest question off them all too mediocre C programmers
    printf("%p\n", nodes->node);

    prev = nodes->node;
    nodes->node = (struct Node*)mem_alloc(&nodes->node, sizeof(*nodes->node));
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
            mem_free(&temp, sizeof(*temp));    //   fria minnet för temp;
            break;
        }
        node = node->next;
    }
    n--;
    return n;
}



unsigned int Terminal_Interface(unsigned int opcode, void* data_ptr, char varname[MAX_VARIBLE_NAME_LENGHT]){
    int choice = 0;
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
                printf("Sökt värde: ");
                scanf("%d", &choice);
                   struct Node* node = start;


                for(int i = 1; i <= number_of_nodes; i++){
                   if(choice == node->name){
                     printf("(%d) %p %p\n", i, &node->data, node->data);
                     break;
                   }
                if(i == 1){
                    node = start->next;
                    continue;
                }
                    node = node->next;
                }
                printf("värde finns ej");
                break;
        }
    return 0;
}



int main(int argc, char* argv[]){

    /* just cut your losses and use malloc...*/
    void* void_ptr = malloc(SIZE_INTEGER);
    void* new = malloc(SIZE_INTEGER);



    //void* data_ptr = (void*)0x456;
    Terminal_Interface(HEAP_ADD, void_ptr, "43");
    Terminal_Interface(HEAP_ADD, new, "anothertest");
    Terminal_Interface(HEAP_ADD, void_ptr, "test");


    Terminal_Interface(HEAP_LIST, NULL, NULL);


    free(void_ptr);
    free(new);

    return 0;
}
// (cd /home/david/Projekts/GY-EX && git add --all && git commit -m "för om gör rätt" && git push -u origi master)
// https://developers.redhat.com/articles/the-gdb-developers-gnu-debugger-tutorial-part-1-getting-started-with-the-debugger
// gcc heap_test.c -g -g3 -o heap -O0
