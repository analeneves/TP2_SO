#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

//adicionar um item na tabela
Item_arq* additem(unsigned *a, Input *in){ 
    Item_arq* j = malloc(sizeof(Item_arq));
    j->chave = a;
    j->valor = in;
    return j;
}
//função para criar uma nova tabela
Table* newtable(int*size){
    Table *t_hash=malloc(sizeof(Table)); //t_hash é o tamanho da hash

    t_hash-> size = *size;
    t_hash-> count= 0;
    t_hash-> item_arqs = calloc(t_hash->size, sizeof(Item_arq*));
    for (int i = 0; i < *size; i++)
    {
        t_hash->item_arqs[i]= (Item_arq*)calloc(1, sizeof(Item_arq));
    }
    return t_hash;
}
//deletar itens da tabela a partir das chaves e valores
void deleteitem(Item_arq *j){
    free(j->chave);
    free(j->valor);
    free(j);
}
//deletar a tabela 
void deletetable(Table *t_hash){
    for (int i = 0; i < t_hash->size; i++){
        Item_arq *item_arq = t_hash->item_arqs[i];
        if(item_arq!=NULL){
        deleteitem(item_arq);
        }
    }
    free(t_hash->item_arqs); //free na tabela que contém os arquivos
    free(t_hash);//free na tabela
}
//*********************************************//
//criação de uma nova fila
Queue *newQueue(int *size){
    Queue *queue=malloc(sizeof(Queue));
    queue->size = *size;
    queue->first = 0;
    queue->last = 0; //para criação da fila precisamos do tamanho 
                    //e valor de primeiro, ultimo
    queue->values = (Value_queue*)calloc(*size, sizeof(Value_queue));
    
    return queue;
}
//adicionar novo valor na fila
Value_queue* newvaluequeue(){
    Value_queue *value = (Value_queue*)calloc(1,sizeof(Value_queue));

    return value;
    
}
//inserir valores na fila
void insert(Queue *n, Value_queue *v){
    n->last++;
    n->count++;

    if (n->last >= n->size && n->first >0){
        n->last = 0;
    }
    
    if (n->values == NULL){//verifica se os valores são nulos
        printf("Valor nulo! Tente novamente.");
        n->values[n->last] = *v;
    }
    
}
//remove valores da fila
void removeQueue(Queue *n){
    n->first++;
    n->count--;
    if (n->first == n->size){
        n->first = 0;
    }
}
//deleta a fila, para uma criação de outra ser feita
void deletequeue(Queue *n){
    if(n->first != n->last){
        for (int j = 0; j < n->last; j++){
            free(&n->values[j]);
        }
    }
    free(n);//free é feito nos valores n da fila
}