#include <stdlib.h>
#include <stdio.h>

typedef struct grafo{
    int valor;
    int visitado;
    int **arestas;
    int conta_arestas;
}grafo;

int count = 0;

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
void dfs(grafo *g,int vertice,int pai,int in_lower[][2]){
    g[vertice].visitado = 1;
    g[vertice].valor = vertice;
    in_lower[vertice][0] = count;
    in_lower[vertice][1] = count;
    count++;

    if(g[vertice].arestas==NULL){
        return ;
    }

    for(int i = 0; i < g[vertice].conta_arestas; i++){
        if (g[g[vertice].arestas[i][0]].visitado == 0){
            dfs(g,g[g[vertice].arestas[i][0]].valor,g[vertice].valor,in_lower);
            if(in_lower[g[vertice].arestas[i][0]][1] > in_lower[g[vertice].valor][0]){
                printf("\nPONTE ENTRE %d e %d", vertice,g[g[vertice].arestas[i][0]].valor);
            }
            in_lower[vertice][1] = in_lower[vertice][1] < in_lower[g[vertice].arestas[i][0]][1] ? in_lower[vertice][1] : in_lower[g[vertice].arestas[i][0]][1];
        }
        else{
            if(g[g[vertice].arestas[i][0]].valor != pai){
                printf("\nback edge entre %d e %d\n", g[vertice].valor ,g[g[vertice].arestas[i][0]].valor);
                in_lower[vertice][1] = in_lower[vertice][1] < in_lower[g[vertice].arestas[i][0]][0] ? in_lower[vertice][1] : in_lower[g[vertice].arestas[i][0]][0];
            }
        }
    }
}
void dfs_subarvore(grafo *g,int vertice,int in_out[][2]){
    g[vertice].visitado = 1;
    in_out[vertice][0] = count;
    count++;

    if(g[vertice].arestas == NULL){
        return;
    }
    for (int i = 0; i < g[vertice].conta_arestas; i++) {
        if(g[g[vertice].arestas[i][0]].visitado==0){
            dfs_subarvore(g,g[g[vertice].arestas[i][0]].valor,in_out);
        }
        in_out[vertice][1]=count;
        count++;
    }
}

int main(){
    grafo *gteste;
    int qtd_vertices = 3;
    int qtd_arestas;
    gteste = (grafo*)calloc(qtd_vertices+1,sizeof(grafo));

    insere_aresta(gteste,1,2,1,1,0);

    int in_out[qtd_vertices+1][2];
    for (int i = 0; i < qtd_vertices+1; ++i) {
        in_out[i][0] = 0;
        in_out[i][1] = 0;
    }
    dfs_subarvore(gteste,1,in_out);

    if(in_out[1][0]< in_out[2][0] && in_out[1][1] > in_out[2][1]){
        printf("Verdade");
    } else{
        printf("falso");
    }

}