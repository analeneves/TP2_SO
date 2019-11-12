#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main(int argc, const char *argv[]){
    
    char* algorithm = (char*)malloc(strlen(*argv)+1);
    strcpy(algorithm,(*argv)+13); //para encontrar o valor " " correspondente na entrada
    
    char* filename = (char*)calloc(strlen(argv[2]),sizeof(char*));
    strcpy(filename, argv[2]);
    
    char *filePath = (char*)malloc(1024*sizeof(char));
    sprintf(filePath, "logs%s",filename); //logs é a pasta onde se encontram os arquivos de teste ".log"
    
    int pageSize = atoi(argv[3]);
    int memSize = atoi(argv[4]);

	if(pageSize >= 2 && pageSize <= 64){ //verificação tamanho da página que deve ser entre 2 e 64
		pageSize = pageSize * 1024;    
		
	}else{
        printf("Tente novamente, valores Page size tem que ser entre 2 e 64.\n");
		exit(1);
	}
		
	if(memSize >= 128 && memSize <= 16384 ){ //verificação tamanho da memória que deve ser entre 128 e 16384
		memSize = memSize * 1024;
		//printf("%i",memSize);
    
	}else{
        printf("Tente novamente, valores Memory size tem que ser entre 128 e 16384.\n");
        exit(1);
	} 
       
    FILE *file = fopen(filePath, "r"); //abertura do arquivo segundo o caminho, filePath
    int numPages = memSize/pageSize; //numero de páginas será sempre o tamanho da memória
                                    //dividido pelo tamanho das páginas
    
    Table *virtualMemory = newtable(&numPages);//é criada uma tabela com a memoria virtual
    Queue *principalMemory = newQueue(&memSize);//é criada uma fila com a memória principal
    unsigned int adress=0, shift = 0, temporary=0, y=0;
    int adress_sh, count1=0,flagright=0, pagerights, indice=0, pagefaults, pagedirty, time=0, count=0;
    char row;

    temporary = pageSize;
    while (temporary>1){
        temporary = temporary>>1;
        shift++;
    }
                                        //primeiro if para verificar se o algoritmo será o LRU
    if(strcmp(algorithm, "lru") == 1){//no strcmp, se == 1, significa que são iguais
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

        } else if (strcmp(algorithm,"nru") == 1){

        } else if (strcmp(algorithm,"segunda_chance") == 1){

        }
        //pagedirty++;
        pagedirty = pagerights - numPages;
        printf("\nExecutando o simulador...\n");
	    printf("Tamanho da memória física: %iKB\n", memSize/1024);
	    printf("Tamanho das páginas: %iKB\n", pageSize/1024);
    	printf("Nome da política de substituição: %s\n", algorithm);
        printf("Nome do do arquivo: %s\n", filename);
	    printf("Número de páginas: %i\n", numPages);
        printf("Número páginas lidas: %i\n",pagerights);
        printf("Número páginas escritas: %i\n", pagedirty);
        //printf("Númerro page faults: %i\n", pagefaults);
        //printf("Número count Memória Principal: %i\n", count); 
return 0;        
    }