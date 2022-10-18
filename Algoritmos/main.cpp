#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX(x,y) ((x>y)?x:y)
int recursive_knap(int W, int arr_v[],int arr_w[], int n){
    if (W == 0 || n == 0){
        return 0;
    }
    if (arr_w[n-1] >= W){
        return recursive_knap(W,arr_v,arr_w,n - 1);
    }
    else{
        return MAX(arr_v[n - 1] + recursive_knap(W - arr_w[n - 1],arr_v, arr_w, n - 1),recursive_knap(W, arr_v, arr_w, n - 1));
    }
}

int main() {
    int W;
    int *item_W;
    int *item_V;
    char name[256];
    FILE *file;


    printf("Digite o peso maximo\n");
    scanf("%d", &W);

    fflush(stdin);

    printf("Digite o nome do arquivo\n");
    fgets(name,256,stdin);

    name[strlen(name)-1] = '\0';

    file = fopen(name,"r");
    if(file == NULL){
        printf("erro");
        system("pause");
        return 1;
    }
    char ch;
    int linesCount = 0;
    while(!feof(file)) {
        ch= fgetc(file);
        if(ch=='\n'){
            linesCount++;
        }
    }
    item_V = (int*)malloc(sizeof(int)*linesCount);
    item_W = (int*)malloc(sizeof(int)*linesCount);
    fseek(file,0,SEEK_SET);
    int i = 0;
    while(!(feof(file))){
        fscanf(file, "%d;%d", &item_V[i], &item_W[i]);
        printf("%d %d\n", item_V[i], item_W[i]);
        i++;
    }
    int n = (sizeof(item_V)/sizeof (item_V[0]));


    printf("o valor maximo carregavel e %d",recursive_knap(W,item_V,item_W,n)) ;



}
