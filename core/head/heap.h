#ifndef HEAP_H
#define HEAP_H

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
int number_of_nodes = 0; // use like errno?



struct Nodes* nodes = &nodes_r;
struct Node* start;
struct Node* JariPekare;
struct Node* node = &node_r;
struct Node* prev;



#endif
