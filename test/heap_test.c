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
// MINNE



int choice = 0;


struct Node{
    void* data; // ATTENTION: memory address to allocated memory
    struct Node* next;
};
// TEST DATA
struct Nodes{
    struct Node* start;
    int number_of_nodes;
    struct Node* node;
};
struct Nodes nodes;
struct Node node;

struct Node* start;

struct Node* JariPekare;

//struct Node* node = start;


enum{
    HEAP_CREATE,
    HEAP_REMOVE,
    HEAP_LIST,
    HEAP_FIND
};


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


union Test{
    int mode;

    union Test* ptr;
};


struct Node* LL_Create(struct Nodes* nodes, int n, void* data){


    nodes->number_of_nodes = n;
    nodes->node = (struct Node*)mem_alloc(&nodes->node, sizeof(*nodes->node));    // ALERT: FIRST ALLOC HERE TO SET UP VARIBLES
    struct Node* start = nodes->node;       // start adress for linked list, BTW does this work like you think it does?
    struct Node* prev;



    for(int i = 1; i <= nodes->number_of_nodes; i++){


        nodes->node->data = data;



        prev = nodes->node;

        if(i == nodes->number_of_nodes){
            prev->next = start;
            continue;   // works like a break;
        }


        nodes->node = (struct Node*)mem_alloc(nodes->node, sizeof(struct Node));
        prev->next = nodes->node;  // ALERT:  next pointer
    }
    return start;
}
int LL_List(struct Nodes* nodes, int n, struct Node* start){
    // puts("yee");
    struct Node* node = start;

    // puts("haw");
    for(int i = 1; i <= n; i++){
        // puts("boys");
        printf("(%d) %p %p\n", i, &node->data, node->data);
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

int LL_Remove(struct Nodes* nodes, int n, struct Node* start, int choice){
    LL_List(nodes, n, start);

    struct Node* node = start;




    for(int i = 1; i <= n; i++){




        printf("(%d) %p %d\n", i, &node->data, node->data);
        if(i == (choice-1)){
            puts("ran");
            struct Node* temp = node->next;     // skapa temporär pekare till nästa nod
            node->next = temp->next;           //  flytta nuvarande nods pekare till temp
            mem_free(&temp, sizeof(temp));    //   fria minnet för temp;
            break;
        }
    /*
        if(i == 1){
            node = start->next;
            continue;

        }
    */
        node = node->next;
    }


    n--;
    return n;

}


/*

enum{
    HEAP_CREATE,
    HEAP_REMOVE,
    HEAP_LIST,
    HEAP_FIND
};
 */
unsigned int HEAP_Main(unsigned int opcode){

    printf("|---------------------------|\n|Q --> Quit                 |\n|R --> Remove Node          |\n|F --> Find Node (by value) |\n|C --> Create Node          |\n|L --> List Nodes           |\n|---------------------------|\n\n");



        // ALERT: INIT STRUCT BY DEF START ADRESS
        // ´nodes.start = nodes.node;

        int n;

        // temp data
        void* data = (void*)0xFF;

        puts("\n");
        switch(opcode){
            case 2343245:   // secret souce functionality
                /*This does not even clear memory... HAH*/
                break;
            case HEAP_CREATE:
                printf("Hur många noder vill ni skapa?: ");
                scanf("%d", &n);
                start = LL_Create(&nodes, n, data);
                break;
            case HEAP_LIST:
                LL_List(&nodes, n, start);
                break;

            case HEAP_REMOVE:
                LL_List(&nodes, n, start);
                printf("Witch list would you like to remove?: ");
                scanf("%d", &choice);
                if(choice == 1){
                    JariPekare = start->next;
                    mem_free(start, sizeof(node));
                    start = (struct Node*)JariPekare;
                    printf("\n\n%p\n", start);

                    n--;
                    break;
                }
                puts("ran LL_Remove");
                n = LL_Remove(&nodes, n, start, choice);
                break;
            /*
            case HEAP_FIND:
                printf("Sökt värde: ");
                scanf("%d", &choice);
                   struct Node* node = start;


                for(int i = 1; i <= n; i++){
                   if(choice == node->data){
                     printf("(%d) %p %d\n", i, &node->data, node->data);
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

            */
        }

    return 0;
}
int main(int argc, char* argv[]){

    // create some ghost functions to call heap main


    // DE-BUG tests
    HEAP_Main(HEAP_CREATE);
    HEAP_Main(HEAP_LIST);

    return 0;
}
