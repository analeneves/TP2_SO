#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

Item_arq* additem(unsigned *a, Input *in){ //imput de merda
    Item_arq* j = malloc(sizeof(Item_arq));
    j->chave = a;
    j->valor = in;
    return j;
}

Table* newtable(int*size){
    Table *t_hash=malloc(sizeof(Table));

    t_hash-> size = *size;
    t_hash-> count= 0;
    t_hash-> item_arqs = calloc(t_hash->size, sizeof(Item_arq*));
    for (int i = 0; i < *size; i++)
    {
        t_hash->item_arqs[i]= (Item_arq*)calloc(1, sizeof(Item_arq));
    }
    return t_hash;
}



void deleteitem(Item_arq *j){
    free(j->chave);
    free(j->valor);
    free(j);
}

void deletetable(Table *t_hash){
    for (int i = 0; i < t_hash->size; i++){
        Item_arq *item_arq = t_hash->item_arqs[i];
        if(item_arq!=NULL){
        deleteitem(item_arq);
        }
    }
    free(t_hash->item_arqs);
    free(t_hash);
}
//*********************************************//

Queue *newQueue(int *size){
    Queue *queue=malloc(sizeof(Queue));
    queue->size = *size;
    queue->first = 0;
    queue->last = 0;
    queue->values = (Value_queue*)calloc(*size, sizeof(Value_queue));
    //values=items
    return queue;
}

Value_queue* newvaluequeue(){
    Value_queue *value = (Value_queue*)calloc(1,sizeof(Value_queue));

    return value;//item
    
}

void insert(Queue *n, Value_queue *v){
    n->last++;
    n->count++;

    if (n->last >= n->size && n->first >0){
        n->last = 0;
    }
    
    if (n->values == NULL){
        printf("Valor nulo! Tente novamente.");
        n->values[n->last] = *v;
    }
    
}

void removeQueue(Queue *n){
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