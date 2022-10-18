#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX(x,y) ((x>y)?x:y)
int max(int a, int b) { return (a > b) ? a : b; }

int recursive_knap(int W, int arr_v[],int arr_w[], int n, int *comb, int iterator){
    if (W == 0 || n == 0){
        return 0;
    }
    if (arr_w[n-1] > W){
        return recursive_knap(W,arr_v,arr_w,n - 1, comb, iterator);
    }
    else{
        if(MAX(arr_v[n - 1] + recursive_knap(W - arr_w[n - 1],arr_v, arr_w, n - 1, comb, iterator),recursive_knap(W, arr_v, arr_w, n - 1, comb, iterator)) == recursive_knap(W, arr_v, arr_w, n - 1, comb, iterator)){
            return recursive_knap(W, arr_v, arr_w, n - 1, comb, iterator);
        }
        else{
            comb[iterator] = arr_v[n-1];
            iterator++;
            return arr_v[n - 1] + recursive_knap(W - arr_w[n - 1],arr_v, arr_w, n - 1, comb, iterator);
        }
        }
}
int dynamic(int W,int arr_v[],int arr_w[], int n,int *comb, int iterator){
    int x,y;
    int K[n+1][W+1];
    for(x = 0;x <= n;x++){
        for(y = 0; y <= W;y++){
            if(x == 0 || y == 0){
                K[x][y] = 0;
            }
            else if(arr_w[x - 1] <= y){
                int i = K[x-1][y];
                int j = arr_v[x-1] + K[x-1][y - arr_w[x - 1]];
                if(i > j){
                    K[x][y] = i;
                }
                else{
                    comb[iterator] = j;
                    iterator++;
                    K[x][y] = j;
                }
            }
            else{
                K[x][y] = K[x-1][y];
            }
        }
    }
    return K[n][W];
}
int dynamic_subset(int sum, int arr_v[], int n){
    int K[n+1][sum+1];
    for(int i = 0; i <= n; i++){
        K[i][0] = 1;
    }
    for(int j=0; j<= sum; j++){
        K[0][j] = 0;
    }
    for(int x = 1; x <= n; x++){
        for(int y = 1; y<= sum; y++ ){
            if(y < arr_v[x - 1]){
                K[x][y] = K[x-1][y];
            }
            if(y >= arr_v[x - 1]){
                K[x][y] = (K[x-1][y]) || (arr_v[x-1] + K[x-1][y - arr_v[x-1]]);
            }
        }

    }
    return K[n][sum];
}
int issubset(int W, int arr_v[],int n){
    if(n == 0){
        return 1;
    }
    if(W == 0){
        return 0;
    }
    if(arr_v[n -1] > W){
        return issubset(W,arr_v,n - 1);
    }

    return max(issubset(W,arr_v,n - 1),+ issubset(W - arr_v[n - 1],arr_v,n - 1) );

}



int main() {
    int W;
    int *item_W;
    int *item_V;
    char name[256];
    FILE *file;
    int *comb;
    int iterator = 0;


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
        i++;
    }

    size_t n = linesCount+1;
    comb = (int*)malloc(sizeof(int)*n);
    printf("o valor maximo carregavel e %d\n", dynamic_subset(W,item_V, n));

    for(int j = 0;j < sizeof(comb)/sizeof(comb[0]);j++){
        printf("%d \t", comb[j]);
    }


}
