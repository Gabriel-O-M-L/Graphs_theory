#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    struct lista* lista_adj;
} vertice;

typedef struct lista
{
    int qtd;
    struct registro* inicio;
} lista;

typedef struct registro
{
    int valor;
    int peso;
    int aresta;
    int insert;
    struct registro* prox;
} registro;


int incluir_ordenado_lista(lista* l, int x, int peso, int aresta,int insert);
registro* aloca_registro();
lista* aloca_lista();
void push(vertice* v, int x, int peso, int aresta,int insert);
void dfs(vertice* vertices, int x, int pai);
vertice *mst(vertice* vertices, int  qtd_vertices, int raiz, vertice* nova_arvore,int *vet_ordem);
int remover_registro_da_lista(int valor_para_apagar, lista* l);
void reseta_visitados(vertice * vertices, int qtd_vertices);
void mostrar_lista(lista *l);
void mostrar_lista_dos_vertices(vertice *v, int tam);
void bubble_sort (int vetor[], int n);

int main()
{
    int qtd_vertices, qtd_arestas, i, a, b, c, cont = 0;
    vertice* vertices;
    vertice* nova_arvore;
    int *vet_ordem;

    scanf("%d %d", &qtd_vertices, &qtd_arestas);

    vertices = (vertice*)calloc(qtd_vertices + 1, sizeof(vertice));
    nova_arvore = (vertice*)calloc(qtd_vertices + 1, sizeof(vertice));
    vet_ordem = (int*)malloc(sizeof(int)*qtd_arestas);

    i = 0;

    while (i < qtd_arestas)
    {

        scanf("%d %d %d", &a, &b, &c);
        push(&vertices[a], b, c, a,i);
        push(&vertices[b], a, c, b,i);
        vet_ordem[i] = c;
        i++;
    }
    bubble_sort(vet_ordem,qtd_arestas);
    nova_arvore = mst(vertices, qtd_vertices, 1,nova_arvore,vet_ordem);
    printf("\n%d\n",nova_arvore[1].lista_adj->inicio->valor);
    mostrar_lista_dos_vertices(nova_arvore,qtd_vertices);

    return 0;
}

void push(vertice* v, int x, int peso, int aresta,int insert)
{
    if (v->lista_adj == NULL)
        v->lista_adj = aloca_lista();
    incluir_ordenado_lista(v->lista_adj, x, peso, aresta,insert);
}
lista* aloca_lista()
{
    lista* novo;
    novo = (lista*)calloc(1, sizeof(lista));
    return novo;
}
registro* aloca_registro()
{
    registro* novo;
    novo = (registro*)calloc(1, sizeof(registro));
    return novo;
}
int incluir_ordenado_lista(lista* l, int x, int peso, int aresta, int insert)
{
    if (l == NULL)
        return 0;

    registro* novo, * aux = NULL, * ant = NULL;
    novo = aloca_registro();
    novo->valor = x;
    novo->peso = peso;
    novo->aresta = aresta;
    novo->insert = insert;

    if (l->inicio == NULL)
    {
        l->inicio = novo;
    }
    else
    {
        int inserido = 0;
        aux = l->inicio;
        while (aux != NULL && !inserido)
        {

            if (aux->valor == novo->valor)
            {
                return 0;
            }

            if (aux->valor < novo->valor)
            {
                ant = aux;
                aux = aux->prox;
            }
            else
            {
                if (ant == NULL)
                    l->inicio = novo;
                else
                    ant->prox = novo;

                novo->prox = aux;
                inserido = 1;
            }
        }
        if (!inserido)
        {
            ant->prox = novo;
            inserido = 1;
        }
    }
    l->qtd++;
    return 1;
}
void dfs(vertice* vertices, int x, int pai)
{
    registro* aux;
    vertices[x].visitado = 1;

    if (vertices[x].lista_adj == NULL) {
        return;
    }

    aux = vertices[x].lista_adj->inicio;

    while(aux!=NULL)
    {
        if (vertices[aux->valor].visitado==0)
        {
            dfs(vertices,aux->valor,x);
        }
        else
        {
            if (aux->valor != pai)
            {
                remover_registro_da_lista(aux->valor, vertices[x].lista_adj);
                remover_registro_da_lista(x, vertices[aux->valor].lista_adj);


            }
        }
        aux = aux->prox;
    }

}
void reseta_visitados(vertice * vertices, int qtd_vertices)
{

    int i;
    for(i=1;i<=qtd_vertices;i++)
    {
        vertices[i].visitado=0;
    }
}
vertice *mst(vertice* vertices, int qtd_vertices, int raiz, vertice* nova_arvore,int *vet_ordem) {
    registro* aux;
    registro temp;
    int counter = 0;
    int percorre = raiz;
    int vet_count = 0;
   
    nova_arvore = (vertice*)calloc(qtd_vertices + 1, sizeof(vertice));
    aux = vertices[raiz].lista_adj->inicio;

    aux = vertices[raiz].lista_adj->inicio;
    percorre = raiz;
    while (counter != 1)
    {
        while (aux != NULL  && percorre< qtd_vertices+1) {
            if(aux->peso == vet_ordem[vet_count]){
                push(&nova_arvore[aux->valor], aux->aresta, aux->peso, aux->valor,0);
                push(&nova_arvore[aux->aresta], aux->valor, aux->peso, aux->aresta,0);

                counter = 0;
                for(int j = 0;j<=qtd_vertices;j++) {
                    if(nova_arvore[j].visitado==0){
                        dfs(nova_arvore, j, -1);
                        counter++;
                    }
                }
                reseta_visitados(nova_arvore,qtd_vertices);
                vet_count++;
            }
            if(aux->prox !=NULL){
                aux = aux->prox;
            }
             else
            {
                percorre++;
                if(percorre<qtd_vertices+1){
                    aux = vertices[percorre].lista_adj->inicio;
                }
            }

        }
        reseta_visitados(nova_arvore,qtd_vertices);
        percorre = 1;
        aux = vertices[percorre].lista_adj->inicio;
    }
    return nova_arvore;
}
int remover_registro_da_lista(int valor_para_apagar, lista* l)
{
    if (l == NULL)
    {
        printf("\nLista inexistente");
        return 0;
    }

    if (l->inicio == NULL)
    {
        printf("\nLista vazia");
        return 0;
    }

    registro* aux = l->inicio, * ant = NULL;
    int encontrou = 0;
    while (aux != NULL && encontrou == 0)
    {
        if (aux->valor == valor_para_apagar) {

            if (ant == NULL)
                l->inicio = aux->prox;
            else
                ant->prox = aux->prox;

            free(aux);
            l->qtd--;
            encontrou = 1;
        }
        else
        {
            ant = aux;
            aux = aux->prox;
        }
    }

    if (encontrou)
        return 1;
    else
        return 0;

}
void mostrar_lista_dos_vertices(vertice *v, int tam)
{
    int i;
    for (i = 0; i < tam; i++)
    {
        if (v[i].lista_adj != NULL)
        {
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
            mostrar_lista(v[i].lista_adj);

        }
    }
}
void mostrar_lista(lista *l){
    registro *aux;

    if (l == NULL)
    {
        printf("\n Lista nula");
        return;
    }

    if (l->inicio == NULL)
    {
        printf("\n Lista vazia");
        return;
    }

    aux = l->inicio;
    while (aux != NULL)
    {
        if(aux->valor==1){
            printf("\n -> A");
        }
        if(aux->valor==2){
            printf("\n -> B");
        }
        if(aux->valor==3){
            printf("\n -> C");
        }
        if(aux->valor==4){
            printf("\n -> D");
        }
        if(aux->valor==5){
            printf("\n -> E");
        }
        if(aux->valor==6){
            printf("\n -> F");
        }
        aux = aux->prox;
    }
}
void bubble_sort (int *vetor, int n) {
    int k, j, aux;

    for (k = 1; k < n; k++) {

        for (j = 0; j < n - 1; j++) {

            if (vetor[j] > vetor[j + 1]) {
                aux          = vetor[j];
                vetor[j]     = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}