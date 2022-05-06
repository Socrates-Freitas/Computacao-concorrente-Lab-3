#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h> // Necessária para a geração de floats aleatórios
#include "timer.h"



typedef struct{
    int threadId;
    long long int dimensao;
    float maiorValor, menorValor;
} Arg;

float *vetorReais;
int numThreads;



void imprimirVetor(float *vetor, long long int dimensao){
    printf("[");
    for(long long int i = 0; i < dimensao; i++){
        printf(" %f",vetor[i]);
        if(i < dimensao - 1){
            printf(",");
        }
    }
    printf("]\n");
}

void maioreEMenoresValoresSequencial(long long int dimensao, Arg* retorno){
    retorno->maiorValor = vetorReais[0];
    retorno->menorValor = vetorReais[0];
    for(long long int i = 1; i < dimensao; i++){
        if(vetorReais[i] < retorno->menorValor){
            retorno->menorValor = vetorReais[i];
        }
        if(vetorReais[i] > retorno->maiorValor){
            retorno->maiorValor = vetorReais[i];
        }
    }
}


void *maioreEMenoresValoresConcorrente(void *args){
    Arg *argumento = (Arg*) args;

    Arg *retorno;
    retorno = (Arg*) malloc(sizeof(Arg));

    int tamanhoBloco, inicio, fim;

    tamanhoBloco = argumento->dimensao / numThreads;
    inicio = argumento->threadId * tamanhoBloco;
    if(argumento->threadId == numThreads - 1){
        fim = argumento->dimensao;
    } else{
        fim = inicio + tamanhoBloco;
    }


    retorno->menorValor = vetorReais[argumento->threadId];
    retorno->maiorValor = vetorReais[argumento->threadId];


    for(long long i = inicio; i < fim; i++){
        if(vetorReais[i] < retorno->menorValor){
            retorno->menorValor = vetorReais[i];
        }
        if(vetorReais[i] > retorno->maiorValor){
            retorno->maiorValor = vetorReais[i];
        }
    }


    pthread_exit((void *) retorno);

}


// Retorna um float aleatorio entre 0 e 1
float randomFloat(){
    return (( (float)rand()) / ((float)RAND_MAX) );
}

float getRandomFloatFromInterval(float inicio, float fim){
    return randomFloat() * (fim - inicio) + inicio;
}


void inicializarVetor(float *vetor,long long int dimensao){
    for(long long int i = 0; i < dimensao; i++){
           vetor[i] = getRandomFloatFromInterval(0,10000000000);  
    }
}


int main(int argc, char* argv[]){
    
    srand(time(NULL)); // inicia uma seed para floats aleatorios

    // Pega a entrada
    long long int dimensao;
    pthread_t *identificadores;
    Arg *argumentos;
    double inicio, fim, tempoSequencial, tempoConcorrente;
    float  menorValorConcorrente, maiorValorConcorrente;
    Arg *retornoSequencial, *retornoConcorrente;

    if(argc < 3){
        puts("Colocar apenas <número de threads> <tamanho do vetor>\n");
        return 2;
    }

    dimensao = atoll(argv[2]);
    numThreads = atoi(argv[1]);


    // inicializar os vetores 
    vetorReais = (float *) malloc(dimensao * sizeof(float));
    if(vetorReais == NULL){
        puts("Erro Malloc!!!\n");
        return 2;
    }

    identificadores = (pthread_t *) malloc(numThreads * sizeof(pthread_t));
    if(identificadores == NULL){
        puts("Erro Malloc!!!\n");
        return 2;
    }

    argumentos = (Arg *) malloc(numThreads * sizeof(Arg));
    if(argumentos == NULL){
        puts("Erro Malloc!!!\n");
        return 2;
    }

    inicializarVetor(vetorReais,dimensao);
    
    retornoSequencial = (Arg*)malloc(sizeof(Arg));



    /* Execução Sequencial */
    GET_TIME(inicio);

    maioreEMenoresValoresSequencial(dimensao, retornoSequencial);

    GET_TIME(fim);
    tempoSequencial = fim - inicio;

   // imprimirVetor(vetorReais,dimensao);


    printf("Tempo de execução sequencial(Menor Valor: %f | Maior Valor: %f): %lf Segundos\n\n",retornoSequencial->menorValor,retornoSequencial->maiorValor,tempoSequencial);
    

    /* Execução concorrente */ 
    GET_TIME(inicio);

    for( int i =0; i < numThreads; i++){
        (argumentos + i)->dimensao = dimensao;
        (argumentos + i)->threadId = i;

        if(pthread_create ((identificadores + i),NULL, maioreEMenoresValoresConcorrente,(void*) (argumentos+i)) ){
            printf("Erro Pthread_create!\n");
            return 2;
        }
    }


    // dar join nas coisas, e comparar os resultados de cada thread

    menorValorConcorrente = vetorReais[0];
    maiorValorConcorrente = vetorReais[0];

    for(int i = 0; i < numThreads; i++){
        if(pthread_join( *(identificadores + i),(void**) &retornoConcorrente) ){
            printf("Erro Pthread_join\n");
            return 2;
        }
        if(retornoConcorrente->menorValor < menorValorConcorrente){
            menorValorConcorrente = retornoConcorrente->menorValor;
        }
        if(retornoConcorrente->maiorValor > maiorValorConcorrente){
            maiorValorConcorrente = retornoConcorrente->maiorValor;
        }
        
        free(retornoConcorrente);

    }

    GET_TIME(fim);

    tempoConcorrente = fim - inicio;
    printf("Tempo de execução concorrente(Menor Valor: %f | Maior Valor: %f | %d thread(s)): %lf Segundos\n\n",menorValorConcorrente,maiorValorConcorrente,numThreads,tempoConcorrente);


    printf("Gannho de desempenho: %lf\n",tempoSequencial/tempoConcorrente);


    // Dar free nas coisas
    free(vetorReais);
    free(identificadores);
    free(argumentos);
    free(retornoSequencial);

      
    return 0;
}


