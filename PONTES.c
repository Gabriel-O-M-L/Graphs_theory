#include <stdio.h>
#include <stdlib.h>

int count = 0;

typedef struct vertice
{
    int visitado;
    int in;
    int lower;
    struct lista *lista_adj;
} vertice;

typedef struct lista
{
    int qtd;
    struct registro *inicio;
} lista;

typedef struct registro
{
    int valor;
    struct registro *prox;
} registro;

int incluir_ordenado_lista(lista *l, int x);
registro *aloca_registro();
lista *aloca_lista();
void push(vertice *v, int x);
void dfs(vertice * vertices , int x,int pai);
int min(int x, int y);

int main()
{
    int qtd_vertices, qtd_arestas,i,a,b,cont=0;
    vertice * vertices;

    scanf("%d %d",&qtd_vertices,&qtd_arestas);

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    i = 0;

    while(i<qtd_arestas)
    {
        scanf("%d %d",&a,&b);
        push(&vertices[a],b);
        push(&vertices[b],a);
        i++;
    }

    dfs(vertices,1,-1);

    return 0;
}

void push(vertice *v, int x)
{
    if (v->lista_adj == NULL)
        v->lista_adj = aloca_lista();
    incluir_ordenado_lista(v->lista_adj, x);
}

lista *aloca_lista()
{
    lista *novo;
    novo = (lista *)calloc(1, sizeof(lista));
    return novo;
}

registro *aloca_registro()
{
    registro *novo;
    novo = (registro *)calloc(1, sizeof(registro));
    return novo;
}

int incluir_ordenado_lista(lista *l, int x)
{
    if (l == NULL)
        return 0;

    registro *novo, *aux = NULL, *ant = NULL;
    novo = aloca_registro();
    novo->valor = x;

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

void dfs(vertice * vertices , int x,int pai)
{
    registro * aux;
    vertices[x].visitado=1;
    vertices[x].in = count;
    vertices[x].lower = count;
    count++;

    if (vertices[x].lista_adj==NULL){
        return;
    }

    aux = vertices[x].lista_adj->inicio;

    while(aux!=NULL)
    {
        if(aux->valor != pai){
            if(vertices[aux->valor].visitado == 1){

                //printf("\nBack Edge");
                vertices[x].lower = min(vertices[x].lower, vertices[aux->valor].in);
            }else{
                dfs(vertices,aux->valor,x);

                if(vertices[aux->valor].lower > vertices[x].in){
                    printf("PONTE ENTRE %d e %d", x,aux->valor);
                }
                vertices[x].lower = min(vertices[x].lower,vertices[aux->valor].lower);
            }
        }
        aux = aux->prox;
    }

}
int min(int x, int y){
    return x < y ? x : y;
}