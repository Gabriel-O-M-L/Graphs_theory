#include <stdlib.h>
#include <stdio.h>

typedef struct grafo{
    int valor;
    int visitado;
    int **arestas;
    int dist_raiz;
    int conta_arestas;
}grafo;

int heap[1000][2];
int count_min = 0;

void bubble_sort (int **vetor, int tamanho) {
    int k, j, aux,peso;
    for (k = 1; k < tamanho; k++) {
        for (j = 0; j < tamanho - 1; j++) {
            if (vetor[j][0] > vetor[j + 1][0]) {
                aux  = vetor[j][0];
                peso = vetor[j][1];
                vetor[j][0]  = vetor[j + 1][0];
                vetor[j][1]  = vetor[j + 1][1];
                vetor[j+1][0] = aux;
                vetor[j+1][1] = peso;
            }
        }
    }
}
void aloca_aresta(grafo *g,int qtd_arestas, int x){
    g[x].arestas = (int**) malloc(qtd_arestas*sizeof(int*));
    for (int j = 0; j < qtd_arestas; j++){
        g[x].arestas[j] = (int *) malloc(2*sizeof(int));
    }
    g[x].conta_arestas = 0;
}
void insere_aresta(grafo *g,int origem,int destino,int peso,int qtd_arestas,int contador){
    g[origem].valor = origem;
    if (g[origem].arestas == NULL){
        aloca_aresta(g,qtd_arestas,origem);
    }
    g[origem].arestas[g[origem].conta_arestas][0] = destino;
    g[origem].arestas[g[origem].conta_arestas][1] = peso;
    g[origem].conta_arestas = g[origem].conta_arestas+1;
    bubble_sort(g[origem].arestas,qtd_arestas);
    contador++;
    if(contador == 1){
        insere_aresta(g,destino,origem,peso,qtd_arestas,contador);
    }
}
void sobe_heap(int indice){
    int posicao;
    int peso;
    int pai;

    if(indice <= 1){
        return;
    }
    pai = indice/2;

    if(heap[indice][1]<heap[pai][1]){
        posicao = heap[indice][0];
        peso = heap[indice][1];
        heap[indice][0] = heap[pai][0];
        heap[indice][1] = heap[pai][1];
        heap[pai][0] = posicao;
        heap[pai][1] = peso;
        sobe_heap(pai);
    }
}
void desce_heap(int indice){
    int direita;
    int esquerda;
    int menor;
    int posicao;
    int peso;

    if(indice*2 > count_min){
        return;
    }
    direita = indice*2+1;
    esquerda = indice*2;
    menor = indice;

    if(esquerda <= count_min){
        if(heap[esquerda][1]<heap[menor][1]){
            menor = esquerda;
        }
    }
    if(direita <= count_min){
        if(heap[direita][1]<heap[menor][1]){
            menor = direita;
        }
    }
    if(menor == indice){
        return;
    }
    posicao = heap[indice][0];
    peso = heap[indice][1];
    heap[indice][0] = heap[menor][0];
    heap[indice][1] = heap[menor][1];
    heap[menor][0] = posicao;
    heap[menor][1] = peso;
    desce_heap(menor);
}
void push_fila(int x,int peso){
    count_min++;
    heap[count_min][0] = x;
    heap[count_min][1] = peso;
    sobe_heap(count_min);
}
void pop_fila(int aux[1][2]){
    aux[0][0] = heap[1][0];
    aux[0][1] = heap[1][1];
    if(count_min != 0){
        heap[1][0] = heap[count_min][0];
        heap[1][1] = heap[count_min][1];
        count_min--;
        desce_heap(1);
    } else{
        aux[0][1] = -1;
        aux[0][0] = -1;
    }
    return;
}

void djiks(grafo *g,int raiz,int nro_vertices){
    int atual;
    int distancia_atual;
    int aux[1][2];
    for(int i = 0; i<nro_vertices+1;i++){
        g[i].dist_raiz = INT_MAX;
    }
    g[raiz].dist_raiz = 0;
    g[raiz].valor = raiz;
    aux[0][1] = 0;
    aux[0][0] = raiz;
    push_fila(aux[0][0],aux[0][1]);

    while (count_min!=0){
        pop_fila(aux);
        atual = aux[0][0];
        distancia_atual = aux[0][1];

        if(g[atual].arestas == NULL){
            return;
        }

        for(int i = 0; i < g[atual].conta_arestas; i++){
            if(distancia_atual + g[atual].arestas[i][1] < g[g[atual].arestas[i][0]].dist_raiz){
                g[g[atual].arestas[i][0]].dist_raiz = distancia_atual + g[atual].arestas[i][1];
                aux[0][1] = g[g[atual].arestas[i][0]].dist_raiz;
                aux[0][0] = g[atual].arestas[i][0];
                push_fila(aux[0][0],aux[0][1]);
            }
        }
    }
}
int main(){
    grafo *gteste;
    int qtd_vertices = 6;
    int qtd_arestas = 5;
    gteste = (grafo*)calloc(qtd_vertices+1, sizeof(grafo));

    insere_aresta(gteste,1,2,6,qtd_arestas,0);
    insere_aresta(gteste,1,3,9,qtd_arestas,0);
    insere_aresta(gteste,1,4,11,qtd_arestas,0);
    insere_aresta(gteste,1,5,5,qtd_arestas,0);
    insere_aresta(gteste,1,6,9,qtd_arestas,0);
    insere_aresta(gteste,2,3,3,qtd_arestas,0);
    insere_aresta(gteste,2,4,6,qtd_arestas,0);
    insere_aresta(gteste,2,5,5,qtd_arestas,0);
    insere_aresta(gteste,2,6,2,qtd_arestas,0);
    insere_aresta(gteste,3,5,4,qtd_arestas,0);
    insere_aresta(gteste,3,6,4,qtd_arestas,0);
    insere_aresta(gteste,4,5,5,qtd_arestas,0);
    insere_aresta(gteste,4,6,6,qtd_arestas,0);
    insere_aresta(gteste,5,6,8,qtd_arestas,0);

    djiks(gteste,1,qtd_arestas);
    for (int i = 1;i<qtd_vertices+1;i++){
        printf("\nDISTANCIA DO NO RAIZ ATE %d = %d",i,gteste[i].dist_raiz);
    }
}