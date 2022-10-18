#include <stdlib.h>
#include <stdio.h>

typedef struct grafo{
    int valor;
    int visitado;
    int **arestas;
    int conta_arestas;
}grafo;

void bubble_sort (int **vetor, int tamanho) {
    int k, j, aux,peso;
    for (k = 1; k < tamanho; k++) {
        for (j = 0; j < tamanho - 1; j++) {
            if (vetor[j][0] > vetor[j + 1][0] && vetor[j+1][0] != 0) {
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
void bubble_sort_vet_ordem (int *vetor, int tamanho) {
    int k, j,aux;
    for (k = 1; k < tamanho; k++) {
        for (j = 0; j < tamanho - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                aux  = vetor[j];
                vetor[j]  = vetor[j + 1];
                vetor[j+1] = aux;
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
void apaga_aresta(int **g,int apagar,int conta_aresta){
    for (int i = 0; i < conta_aresta; i++) {
        if(g[i][0] = apagar){
            g[i][0] = INT_MAX;
            g[i][1] = INT_MAX;
            bubble_sort(g,conta_aresta);
        }
    }
}
void dfs(grafo *g,int vertice,int pai){
    g[vertice].visitado = 1;
    g[vertice].valor = vertice;

    if(g[vertice].arestas==NULL){
        return ;
    }

    for(int i = 0; i < g[vertice].conta_arestas; i++){
        if (g[g[vertice].arestas[i][0]].visitado == 0){
            dfs(g,g[g[vertice].arestas[i][0]].valor,g[vertice].valor);
            }
        else{
            if(g[g[vertice].arestas[i][0]].valor != pai){
                printf("delete");
                apaga_aresta(g[g[vertice].arestas[i][0]].arestas,g[vertice].valor,g[vertice].conta_arestas);
                apaga_aresta(g[vertice].arestas,g[vertice].arestas[i][0],g[vertice].conta_arestas);
            }
        }
    }
}
void reseta_visitados(grafo *g, int qtd_vertices)
{
    int i;
    for(i=1;i<=qtd_vertices;i++)
    {
        g[i].visitado=0;
    }
}
void mst(grafo *g,int qtd_vertices,int* vet_ordem,grafo* nova_arvore,int qtd_arestas){
    int counter = 0;
    int vet_count = 0;

    for (int q = 1; q <= qtd_vertices; q++) {
        for (int i = 0; i < g[q].conta_arestas; i++){
            if(g[q].arestas[i][1] == vet_ordem[vet_count]){
                insere_aresta(nova_arvore,g[q].valor,g[q].arestas[i][0],g[q].arestas[i][1],qtd_arestas,0);

                counter = 0;
                for(int j = 1;j<qtd_vertices;j++) {
                    if(nova_arvore[j].visitado==0){
                        dfs(nova_arvore, j, -1);
                        counter++;
                    }
                }
                if(counter == 1){
                    return;
                }
                reseta_visitados(nova_arvore,qtd_vertices);
                vet_count++;
            }
            if(q == qtd_vertices){
                  q = 1;
            }
        }
    }
}
void mostrar_arvore(grafo *nova_arvore,int tam){
    int contador = 0;
    for (int i = 0; i < tam+1; i++) {
        if(i==1){
            printf("\nLista de Adjacencias do no : A");
        }
        if(i==2){
            printf("\nLista de Adjacencias do no : B");
        }
        if(i==3){
            printf("\nLista de Adjacencias do no : C");
        }
        if(i==4){
            printf("\nLista de Adjacencias do no : D");
        }
        if(i==5){
            printf("\nLista de Adjacencias do no : E");
        }
        if(i==6){
            printf("\nLista de Adjacencias do no : F");
        }
        if(i!=0){
            for (int j = 0; j < nova_arvore[i].conta_arestas; j++){
                printf("\n-> No %d com peso %d", nova_arvore[i].arestas[j][0],nova_arvore[i].arestas[j][1]);
            }
        }
    }
}
int main(){
    grafo *gteste;
    grafo * nova_arvore;
    int qtd_vertices = 6;
    int qtd_arestas = 5;
    int vet_ordem[14];
    int  index = 0;
    gteste = (grafo*)calloc(qtd_vertices+1, sizeof(grafo));
    nova_arvore = (grafo*)calloc(qtd_vertices+1, sizeof(grafo));


    insere_aresta(gteste,1,2,6,qtd_arestas,0);
    vet_ordem[index] = 6;
    insere_aresta(gteste,1,3,9,qtd_arestas,0);
    vet_ordem[index++] = 9;
    insere_aresta(gteste,1,4,11,qtd_arestas,0);
    vet_ordem[index++] = 11;
    insere_aresta(gteste,1,5,5,qtd_arestas,0);
    vet_ordem[index++] = 5;
    insere_aresta(gteste,1,6,9,qtd_arestas,0);
    vet_ordem[index++] = 9;
    insere_aresta(gteste,2,3,3,qtd_arestas,0);
    vet_ordem[index++] = 3;
    insere_aresta(gteste,2,4,6,qtd_arestas,0);
    vet_ordem[index++] = 6;
    insere_aresta(gteste,2,5,5,qtd_arestas,0);
    vet_ordem[index++] = 5;
    insere_aresta(gteste,2,6,2,qtd_arestas,0);
    vet_ordem[index++] = 2;
    insere_aresta(gteste,3,5,4,qtd_arestas,0);
    vet_ordem[index++] = 4;
    insere_aresta(gteste,3,6,4,qtd_arestas,0);
    vet_ordem[index++] = 4;
    insere_aresta(gteste,4,5,5,qtd_arestas,0);
    vet_ordem[index++] = 5;
    insere_aresta(gteste,4,6,6,qtd_arestas,0);
    vet_ordem[index++] = 6;
    insere_aresta(gteste,5,6,8,qtd_arestas,0);
    vet_ordem[index++] = 8;

    bubble_sort_vet_ordem(vet_ordem,qtd_arestas);
    mst(gteste,qtd_vertices,vet_ordem,nova_arvore,qtd_arestas);
    mostrar_arvore(nova_arvore,qtd_vertices);

}