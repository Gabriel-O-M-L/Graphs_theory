#include <stdio.h>
#include <stdlib.h>

int count = 1;

typedef struct elemento{
    int vertice;
    int distancia;
}elemento;

elemento heap[1000];
int count_min = 0;
typedef struct vertice
{
    int visitado;
    int distancia;
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
    int peso;
    struct registro *prox;
} registro;

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

int push_fila(elemento x){
    count_min++;
    heap[count_min] = x;
    subir_minimo(count_min);
}

elemento pop_fila(){
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

int empty(){
    if (count_min == 0){
        return 1;
    }else{
        return 0;
    }
}
void init_dist(vertice *vertices,int nro_vertices){
    for(int i=0;i<nro_vertices;i++){
        vertices[i].distancia = 9999;
    }
}
void djikstra(vertice *vertices,int raiz,int nro_vertices){
    init_dist(vertices,nro_vertices+1);
    vertices[raiz].distancia = 0;
    int current;
    int distancia_atual;
    elemento ele_aux;
    registro * aux;

    ele_aux.distancia = 0;
    ele_aux.vertice = raiz;
    push_fila(ele_aux);

    while(!empty()){
        ele_aux = pop_fila();
        current = ele_aux.vertice;
        distancia_atual = ele_aux.distancia;
        // printf("\n%d %d\n", distancia_atual,current);

        if(vertices[current].lista_adj==NULL){
            printf("\nVertice  desconectado\n");
            return;
        }

        aux = vertices[current].lista_adj->inicio;

        while(aux!=NULL){

            if(distancia_atual + aux->peso < vertices[aux->valor].distancia){
                vertices[aux->valor].distancia = distancia_atual + aux->peso;
                ele_aux.distancia = vertices[aux->valor].distancia;
                ele_aux.vertice = aux->valor;
                push_fila(ele_aux);
            }
            aux=aux->prox;
        }
    }
};

int incluir_ordenado_lista(lista *l, int x,int peso);
registro *aloca_registro();
lista *aloca_lista();
void push(vertice *v, int x,int peso);
void dfs(vertice * vertices , int x,int pai);
int min(int x, int y);

int main()
{
    int qtd_vertices, qtd_arestas,i,a,b,c,cont=0;
    vertice * vertices;

    elemento aux;

    scanf("%d %d",&qtd_vertices,&qtd_arestas);

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    i = 0;

    while(i<qtd_arestas)
    {
        scanf("%d %d %d",&a,&b,&c);
        push(&vertices[a],b,c);
        push(&vertices[b],a,c);
        i++;
    }

    djikstra(vertices,1,qtd_vertices);

    for (i = 1;i<qtd_vertices+1;i++){
        printf("\nDISTANCIA DO NO RAIZ ATE %d = %d",i,vertices[i].distancia);
    }
    //registro * aux_list;
    //aux_list =  vertices[1].lista_adj->inicio;
    //while (aux_list!= NULL){
    //    printf("ELEMENTO: %d DISTANCIA :%d", aux_list->valor,aux_list->peso);
    //    aux_list = aux_list->prox;
    //}

    dfs(vertices,1,-1);

    return 0;
}

void push(vertice *v, int x,int peso)
{
    if (v->lista_adj == NULL)
        v->lista_adj = aloca_lista();
    incluir_ordenado_lista(v->lista_adj, x,peso);
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

int incluir_ordenado_lista(lista *l, int x,int peso)
{
    if (l == NULL)
        return 0;

    registro *novo, *aux = NULL, *ant = NULL;
    novo = aloca_registro();
    novo->valor = x;
    novo->peso = peso;

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
                   // printf("PONTE ENTRE %d e %d", x,aux->valor);
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