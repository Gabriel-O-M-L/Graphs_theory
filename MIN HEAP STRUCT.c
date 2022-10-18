#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
    int vertice;
    int distancia;
}elemento;

elemento heap[1000];
int count_min = 0;

int def_filho_esquerda(int indice){
    return indice * 2;
}
int def_filho_direita(int indice){
    return (indice * 2 + 1);
}
int def_pai (int indice){
    return indice/2;
}
void subir_minimo(int indice){
    elemento aux;

    if(indice<= 1){
        return;
    }
    int pai = def_pai(indice);

    if (heap[indice].distancia < heap[pai].distancia){

        aux = heap[indice];
        heap[indice] = heap[pai];
        heap[pai] = aux;
        subir_minimo(pai);
    }
}
void desce_minimo(int indice){
    if(indice * 2 > count_min){
        return;
    }
    int esquerda = def_filho_esquerda(indice);
    int direita = def_filho_direita(indice);
    elemento aux;

    int menor = indice;

    if(esquerda <= count_min && heap[esquerda].distancia < heap[menor].distancia){
        menor = esquerda;
    }

    if(direita <= count_min && heap[direita].distancia < heap[menor].distancia){
        menor = direita;
    }

    if(menor ==  indice){
        return;
    }


    aux = heap[indice];
    heap[indice] = heap[menor];
    heap[menor] = aux;
    desce_minimo(menor);
}

int push(elemento x){
    count_min++;
    heap[count_min] = x;
    subir_minimo(count_min);
}

elemento pop(){
    elemento retorno = heap[1];
    if (count_min == 0){
        retorno.distancia = -1;
        retorno.vertice = -1;
        return retorno;
    }
    heap[1] = heap[count_min];
    count_min--;
    desce_minimo(1);
    return retorno;
}
int main(){
    push(8);
    push(5);
    push(7);
    push(3);
    elemento retorno;

    while (retorno.distancia!=-1){
        retorno = pop();
        if(retorno.distancia!=-1){
            printf("Vertice $d Distancia $d", retorno.vertice,retorno.distancia);
        }
    }
}