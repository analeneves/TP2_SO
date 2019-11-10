#define LENGTH 10
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main(int argc, char const *argv[]){
    if (argc<5){
        printf("Verifique se escreveu a entrada corretamente! Tente de novo.");
        exit(1);
    }
    
   
    
    char *algorithm = ( char* )calloc( strlen(argv[1]),  sizeof( char* ) );
    char *filename = ( char* )calloc( strlen(argv[2]),  sizeof( char* ) );
    char *filePath = ( char* )calloc( 1024,  sizeof( char* ) );
    int pageSize = atoi(argv[3]);
    int memSize = atoi(argv[4]);

    strcpy( algorithm, argv[1] );
    strcpy( filename, argv[2] );

	if(pageSize >=2 && pageSize <= 64){
		pageSize = pageSize * 1024;
		
	}else{
		printf("ERRO, tente novamente pois Page Size deve ser entre 2 e 64.\n");
		return 0;
	}
		
	if(memSize >= 128 && memSize <= 16384 ){
		memSize = memSize * 1024;
		
	}else{
		printf("ERRO, tente novamente pois Page Size deve ser entre 128 e 16384.\n");
		return 0;
	}
	
	if(strcmp(algorithm, "lru") && strcmp(algorithm, "nru") && strcmp(algorithm,"segunda_chance")){
		printf("ERRO: O algoritmo deve ser lru, nru ou segunda_chance.");
		return 0;	
	}

    
    FILE *file = fopen(filePath, "r");
    int numPages = memSize/pageSize;
    Table *virtualMemory = newtable(&numPages);

    Queue *principalMemory = newQueue(&memSize);
    int adress, shift = 0, temporary, y;
    int adress_sh, count1=0,flagright=0, pagerights=0, indice, pagefaults=0, pagedirty=0, time=0;
    char row;

    temporary = pageSize;
    while (temporary>1){
        temporary = temporary>>1;
        shift++;
    }
    

    if (!strcmp(algorithm, "lru")){
        while (!feof(file)){
            fscanf(file, "%x %c", &adress, &row);
            adress_sh = adress >> shift;
            indice = adress_sh % virtualMemory->size;
            flagright = 0;
            
            if(virtualMemory->item_arqs[indice]->next == NULL){
                pagefaults++;

                Value_queue *x = newvaluequeue();
                x->offset = adress_sh;
                insert(principalMemory, x);

                Input *in = (Input*)calloc(1,sizeof(Input));
                in->referenced_pages = x->offset;
                in->last_access = time;
                in->altered = 0;
                in->pres_absent_pages = 1;

                virtualMemory->item_arqs[indice]->next = additem(&adress_sh, in);
            }else{
                Item_arq *prox = virtualMemory->item_arqs[indice];
                for ( ; prox->next != NULL; prox->next){
                    if (prox->next->valor->referenced_pages == adress_sh && prox->next->valor->pres_absent_pages == 1){
                        flagright = 1;
                        pagerights++;
                    } else if (prox->next->valor->referenced_pages == adress_sh && prox->next->valor->pres_absent_pages == 0){
                        prox->next->valor->last_access = time;
                        prox->next->valor->altered=1;
                        prox->next->valor->pres_absent_pages = 1;

                        int indice2 = principalMemory->values[principalMemory->first].offset;
                        indice2=indice2%virtualMemory->size;

                        for ( ; prox->next!=NULL; prox=prox->next){
                            if (prox->next->valor->referenced_pages == adress_sh){
                                prox->next->valor->last_access = time;
                                prox->next->valor->altered = 1;
                                prox->next->valor->pres_absent_pages = 0;
                            }
                        }

                        removeQueue(principalMemory);
                        pagefaults++;
                        pagedirty++;
                        Value_queue *x = newvaluequeue();
                        x->offset = adress;
                        insert(principalMemory, x);
                        
                    }else{ 
                        continue;
                    }
     
                }
                
                if (flagright != 1){
                    if (principalMemory->count == principalMemory->size){
                        int indice2 = principalMemory->values[principalMemory->first].offset;
                        indice2 = indice2%virtualMemory->size;
                        for ( ; prox->next != NULL ; prox=prox->next){
                            if (prox->next->valor->referenced_pages == adress_sh){
                                prox->next->valor->last_access = time;
                                prox->next->valor->altered = 1;
                                prox->next->valor->pres_absent_pages = 0;
                            }
                            
                        }
                        removeQueue(principalMemory);
                    }
                    pagefaults++;
                    Value_queue *x = newvaluequeue();
                    x->offset = adress;
                    insert(principalMemory, x);

                    Input *in = (Input*)calloc(1,sizeof(Input));
                    in->referenced_pages = x->offset;
                    in->last_access = time;
                    in->altered = 0;
                    in->pres_absent_pages = 1;

                    prox->next = additem(&adress_sh, in);
                }
                            
            } time++;
            
            }

        } else if (!strcmp(algorithm,"nru")){

        } else if (!strcmp(algorithm,"segunda_chance")){

        }


        printf("\nExecutando o simulador...\n");
	    printf("Tamanho da memória física: %iKB\n", memSize);
	    printf("Tamanho das páginas: %iKB\n", pageSize/1024);
    	printf("Tecnica de substiruição: %s\n", algorithm);
	    printf("Número de páginas: %i\n", numPages);
	    printf("Númerro page faults: %i\n", pagefaults);
        printf("Númerro page rights: %i\n", pagerights);
        printf("Númerro page dirty: %i\n", pagedirty);
        printf("Número count Memória Principal: %i\n", count1);
	   // printf("Operacoes de leitura: %i\n", reads);
	    //printf("Operacoes de escrita: %i\n", writes);
	   // printf("Page hits: %i\n", hits);
	    //printf("Page misses: %i\n", misses);
	   // printf("Numero de writebacks: %i\n", writebacks);
	    //printf("Taxa de page fault: %f%% \n", faults/writes*100);
        
        

return 0;        
    }