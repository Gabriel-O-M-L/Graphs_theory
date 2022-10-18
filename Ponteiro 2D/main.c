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
void aloca_vetor_in_lower(int **in_lower,int tamanho){
    in_lower = (int**) malloc(tamanho*sizeof(int*));
    for (int j = 0; j < tamanho; j++){
        in_lower[j] = (int *) malloc(2*sizeof(int));
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
void dfs(grafo *g,int vertice,int pai,int in_lower[][2]){
    g[vertice].visitado = 1;
    g[vertice].valor = vertice;
    in_lower[vertice][0] = count;
    in_lower[vertice][1] = count;
    count++;

    if(g[vertice].arestas==NULL){
        return ;
    }

    for(int i = 1; i < g[vertice].conta_arestas; i++){
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
void mst(grafo *g,int raiz,int qtd_vertices,int* vet_ordem,grafo* nova_arvore,int qtd_arestas,int in_lower[][2]){
    int counter = 0;
    int vet_count = 0;

    nova_arvore = (grafo*)calloc(qtd_vertices + 1, sizeof(grafo));
    for (int q = 0; q < qtd_vertices+1; q++) {
        for (int i = 0; i < g[q].conta_arestas; i++){
            if(g[q].arestas[i][1] == vet_ordem[count]){
                insere_aresta(nova_arvore,g[q].valor,g[q].arestas[i][0],g[q].arestas[i][1],qtd_arestas,0);

                counter = 0;
                for(int j = 0;j<=qtd_vertices;j++) {
                    if(nova_arvore[j].visitado==0){
                        dfs(nova_arvore, j, -1,in_lower);
                        counter++;
                    }
                }
                if(counter == 1){
                    return;
                }
                reseta_visitados(nova_arvore,qtd_vertices);
                vet_count++;
            }
        }
    }
}
void mostrar_arvore(grafo *nova_arvore,int tam){
    int contador = 0;
    for (int i = 0; i < tam; i++) {
        if(i==1){
            printf("\n Lista de Adjacencias do no : A");
        }
        if(i==2){
            printf("\n Lista de Adjacencias do no : B");
        }
        if(i==3){
            printf("\n Lista de Adjacencias do no : C");
        }
        if(i==4){
            printf("\n Lista de Adjacencias do no : D");
        }
        if(i==5){
            printf("\n Lista de Adjacencias do no : E");
        }
        if(i==6){
            printf("\n Lista de Adjacencias do no : F");
        }
        if(i!=0){
            printf("%d", nova_arvore[i].valor);
            for (int j = 0; j < nova_arvore[i].conta_arestas; j++){
                printf("No %d com peso %d", &nova_arvore[i].arestas[j][0],&nova_arvore[i].arestas[j][1]);
            }
        }
    }
}
int main(){
    grafo *gteste;
    int qtd_vertices = 6;
    int qtd_arestas = 28;
    int vet_ordem[qtd_arestas];
    int  index = 0;
    gteste = (grafo*)calloc(qtd_vertices+1, sizeof(grafo));


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

    grafo * nova_arvore;
    nova_arvore = (grafo*)calloc(qtd_vertices+1, sizeof(grafo));
    int in_lower[qtd_arestas+1][2];
    bubble_sort_vet_ordem(vet_ordem,qtd_arestas);
    dfs(gteste,1,-1,in_lower);
    reseta_visitados(gteste,qtd_vertices);
    mst(gteste,1,qtd_vertices,vet_ordem,nova_arvore,qtd_arestas,in_lower);

    mostrar_arvore(nova_arvore,qtd_vertices);

}