#include <stdio.h>
#include <stdlib.h>

int heap[100];
int count = 0;

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
    int aux;

    if(indice<= 1){
        return;
    }
    int pai = def_pai(indice);

    if (heap[indice] < heap[pai]){

        aux = heap[indice];
        heap[indice] = heap[pai];
        heap[pai] = aux;
        subir_minimo(pai);
    }
}
void desce_minimo(int indice){
    if(indice * 2 > count){
        return;
    }
    int esquerda = def_filho_esquerda(indice);
    int direita = def_filho_direita(indice);
    int aux;

    int menor = indice;

    if(esquerda <= count && heap[esquerda] < heap[menor]){
        menor = esquerda;
    }

    if(direita <= count && heap[direita] < heap[menor]){
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

int push(int x){
    count++;
    heap[count] = x;
    subir_minimo(count);
}

void pop(){
    if (count == 0){
        return;
    }

    printf("\n %d", heap[1]);
    heap[1] = heap[count];
    count--;
    desce_minimo(1);

}
int main(){
    push(8);
    push(5);
    push(7);
    push(3);

    for(int i = 0; i < 4; i++){
        pop();
    }
}