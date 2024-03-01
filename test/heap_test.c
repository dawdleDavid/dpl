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
        res += (unsigned int)name[c]; // this is dumb... BUT IT WORKS
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
};
// TEST DATA
struct Nodes{
    struct Node* start;
    int number_of_nodes;
    struct Node* node;
};

union Test{
    int mode;

    union Test* ptr;
};

struct Nodes nodes;

struct Node* start;

struct Node* JariPekare;

struct Node** node = &start;

struct Node* LL_Create(struct Nodes* nodes, int n, void* pointer /*char name[MAX_VARIBLE_NAME_LENGHT]*/){


    nodes->number_of_nodes = n;                 // good or bad, idk to * or not to *, that is the biggest question oif them all for mediocre C programmers
    nodes->node = (struct Node*)mem_alloc(&nodes->node, sizeof(*nodes->node));    // ALERT: FIRST ALLOC HERE TO SET UP VARIBLES
    struct Node* start = nodes->node;       // start adress for linked list, BTW does this work like you think it does?
    struct Node* prev;



    for(int i = 1; i <= nodes->number_of_nodes; i++){


        nodes->node->data = pointer;
        /*nodes->node->name = HEAP_HashVaribleName(name);*/


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
        printf("N:(%d) NODE_ADDRESS:%p CONTAINED_POINTER:%p VARIBLE_NAME_HASHED:%u\n", i, &node, node->data, node->name);
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




        printf("(%d) %p %p\n", i, &node->data, node->data);
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



unsigned int Terminal_Interface(unsigned int opcode, int numberofnodes, void* data_ptr /*char varname[MAX_VARIBLE_NAME_LENGHT]*/){
    int choice = 0;

        int n;
        puts("\n");
        switch(opcode){
            case HEAP_ADD:
                n = numberofnodes;
                start = LL_Create(&nodes, n, data_ptr/*,varname*/);
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

            case HEAP_FIND:
                printf("Sökt värde: ");
                scanf("%d", &choice);
                   struct Node* node = start;


                for(int i = 1; i <= n; i++){
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
    return n;
}
int main(int argc, char* argv[]){
    unsigned int n = 0;

    //void* data_ptr = (void*)mem_alloc(data_ptr, SIZE_INTEGER);

    void* data_ptr = (void*)0x456;
    Terminal_Interface(HEAP_ADD, 3, data_ptr);
    //Terminal_Interface(HEAP_ADD, 3, data_ptr);
    Terminal_Interface(HEAP_LIST, 0, NULL);

    return 0;
}
// (cd /home/david/Projekts/GY-EX && git add --all && git commit -m "för om gör rätt" && git push -u origi master)
