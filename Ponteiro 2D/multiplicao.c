#include <stdlib.h>
#include <stdio.h>

typedef struct grafo{
    int valor;
    int visitado;
    int **arestas;
    int conta_arestas;
}grafo;

int qtd_vertices_comp = 0;

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
void insere_aresta(grafo *g,int origem,int destino,int qtd_arestas,int contador){
    g[origem].valor = origem;
    if (g[origem].arestas == NULL){
        aloca_aresta(g,qtd_arestas,origem);
    }
    g[origem].arestas[g[origem].conta_arestas][0] = destino;
    g[origem].conta_arestas = g[origem].conta_arestas+1;
    bubble_sort(g[origem].arestas,qtd_arestas);
    contador++;
    if(contador == 1){
        insere_aresta(g,destino,origem,qtd_arestas,contador);
    }
}
void dfs(grafo *g,int vertice){
    g[vertice].visitado = 1;
    qtd_vertices_comp++;

    if(g[vertice].arestas == NULL){
        return;
    }
    for (int i = 0; i < g[vertice].conta_arestas; i++) {
        if(g[g[vertice].arestas[i][0]].visitado==0){
            dfs(g,g[g[vertice].arestas[i][0]].valor);
        }
    }
}
int main(){
    grafo *gteste;
    int qtd_vertices;
    int a,b;
    int qtd_arestas;
    int conta_componete = 0;
    int amostras;
    int multi = 1;

    scanf("%d", &amostras);
    for (int i = 0; i < amostras; i++) {
        scanf("%d %d", &qtd_vertices,&qtd_arestas);
        gteste = (grafo*)calloc(qtd_vertices+1,sizeof(grafo));
        for (int j = 0; j < qtd_arestas; j++) {
            scanf("%d %d", &a,&b);
            insere_aresta(gteste,a,b,qtd_arestas,0);
        }
        for (int l = 1; l <= qtd_vertices; l++) {
            if(gteste[l].visitado == 0){
                dfs(gteste,l);
                multi = multi*qtd_vertices_comp;
                conta_componete++;
                qtd_vertices_comp = 0;
            }
        }
        printf("\n%d %d", conta_componete, multi);
        conta_componete = 0;
        multi = 1;
        free(gteste);
    }
}