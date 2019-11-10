#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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