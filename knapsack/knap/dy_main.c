#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int max(int x, int y){return (x > y) ? x:y ;}

int dynamic_knap(int W, int arr_v[],int arr_w[], int n){
    int i,j;
    int K[n + 1][W+1];
    for(i++;i <= n;i++){
        for(j = 0; j <= W; j++){
            if(i == 0 || j == 0)
                K[i][j] = 0;
            else if(arr_w[i-1] <= j){
                K[i][j] = max(arr_v[i] + K[i - 1][arr_w[j-arr_w[i-1]]], K[i-1][j]);
            }
            else{
                K[i][j] = K[i-1][j];

            }
        }
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
    W = 50;
    fflush(stdin);

    printf("Digite o nome do arquivo\n");
    fgets(name,256,stdin);

    name[strlen(name)-1] = '\0';

    file = fopen(name,"r");
    if(file == NULL){
        printf("erro");
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

    size_t n = linesCount+1;
    printf("o valor maximo carregavel e %d", dynamic_knap(W,item_V,item_W, n));
    return 0;
}
