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
   
    int algorithm = argv[1];
    int filePath = argv[2];
    int pageSize = atoi(argv[3]);
    int memSize = atoi(argv[4]);

	if(pageSize < 2 || pageSize > 64){	
		printf("ERRO: O tamanho de cada página deve estar entre 2 e 64.");
		return 0;
	}
		
	if(memSize < 128 || memSize > 16384){
		printf("ERRO: O tamanho da memória deve estar entre 128 e 16384.");
		return 0;
	}	
	
	if(strcmp(algorithm, "nru") && strcmp(algorithm, "lru") && strcmp (algorithm, "segunda_chance")){
		printf("ERRO: O algoritmo deve ser lru, nru ou segunda_chance.");
		return 0;	
	}
return 0;
}


