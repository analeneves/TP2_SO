#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"

Table* newtable(int*size){
    Table* t_hash=malloc(sizeof(Table));

    t_hash-> size = *size;
    t_hash-> count= 0;
    t_hash-> item_arq = calloc(t_hash->size, sizeof(Item_arq*));
    for (int i = 0; i < *size; i++)
    {
        t_hash->item_arq[i]= (Item_arq*)calloc(1, sizeof(Item_arq));
    }
    return t_hash;
}

Item_arq* additem(unsigned *a, Input *in){
    Item_arq* j = malloc(sizeof(Item_arq));
    j->chave = a;
    j->valor = in;
    return j;
}

void deleteitem(Item_arq *j){
    free(j->chave);
    free(j->valor);
    free(j);
}

void deletetable(Table *t_hash){
    for (int i = 0; i < t_hash->size; i++)
    {
        Item_arq *item_arq = t_hash->item_arq[i];
        if(item_arq!=NULL)
        deleteitem(item_arq);
    }
    free(t_hash->item_arq);
    free(t_hash);
}

Value_queue* newvaluequeue(){
    Value_queue *value = (Value_queue*)calloc(1,sizeof(Value_queue));

    return value;
}

Queue *newQueue(int *size){
    Queue *queue=malloc(sizeof(Queue));
    queue->size = *size;
    queue->first = 0;
    queue->last = 0;
    queue->values = (Value_queue*)calloc(*size, sizeof(Value_queue));
    
    return queue;
}

void insert(Queue *n, Value_queue *a){
    n->last++;
    n->count++;

    if (n->last >= n->size && n->first >0){
        n->last = 0;
    }
    
    if (n->values == NULL){
        printf("Valor nulo! Tente novamente.");
        n->values[n->last] = *a;
    }
    
}

void remove(Queue *n){
    n->first++;
    n->count--;
    if (n->first == n->size){
        n->first = 0;
    }
}

void deletequeue(Queue *n){
    if(n->first != n->last){
        for (int j = 0; j < n->last; j++){
            free(&n->values[j]);
        }
    }
    free(n);
}