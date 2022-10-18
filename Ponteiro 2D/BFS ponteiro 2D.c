#include <stdlib.h>
#include <stdio.h>

typedef struct grafo{
    int valor;
    int visitado;
    int **arestas;
    int conta_arestas;
}grafo;

int count = 0;
int top;

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
int push_fila(int *pilha,int x){
    top++;
    pilha[top] = x;
}
int pop_fila(int *pilha){
    if(top >= 0){
        int aux;
        aux = pilha[top];
        top--;
        return aux;
    }
}
void bfs(grafo *g,int vertice,int qtd_arestas){
    int retorna;
    int *pilha;
    pilha = (int*)malloc(sizeof(int)*qtd_arestas+1);

    push_fila(pilha,vertice);

    while(top > -1){
        retorna = pop_fila(pilha);
        if(g[retorna].visitado==0){
            g[retorna].visitado=1;
            printf("\n -> %d",retorna);
            for(int i=0;i<g[retorna].conta_arestas;i++){
                push_fila(pilha,g[retorna].arestas[i][0]);
            }
        }
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
int main(){
    grafo *gteste;
    int qtd_vertices,qtd_arestas, a, b;
    int i = 0;
    top = -1;


    scanf("%d %d", &qtd_vertices, &qtd_arestas);

    gteste = (grafo*)calloc(qtd_vertices+1, sizeof(grafo));

    while(i<qtd_arestas){
        scanf("%d %d", &a, &b);
        insere_aresta(gteste,a,b,qtd_arestas,0);
        i++;
    }

    //int in_lower[qtd_arestas+1][2];
    //aloca_vetor_in_lower(in_lower,qtd_vertices+1);

    //dfs(gteste,1,-1,in_lower);

    bfs(gteste,1,qtd_arestas);
}