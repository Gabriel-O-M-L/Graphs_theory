#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int x, int y){return x > y ? x : y;}
int dyn(int W, int arr_v[], int arr_w[],int n, int x[]){
    int i,j;
    int iterator;
    int K[n+1][W+1];
    for(i = 0; i<=n;i++){
        for(j = 0; j<=W;j++){
            if(i == 0 || j == 0){
                K[i][j] = 0;
            }
            else if(arr_w[i-1] <= j){
                if(max(K[i-1][j], arr_v[i-1] + K[i-1][j - arr_w[i-1]]) == K[i-1][j]){
                    K[i][j] = K[i-1][j];
                }
                else{
                    x[j] = arr_v[i-1];
                    j++;
                    x[j] = K[i-1][j - arr_w[i-1]];
                    j = 0;
                    K[i][j] = arr_v[i-1] + K[i-1][j - arr_w[i-1]];

                }
            }
            else{
                K[i][j] = K[i-1][j];
            }
        }
    }
    return K[n][W];
}
int main(){
    int item_v[] = {60,100,120};
    int item_w[] = {10,20,30};
    int linecount = 0;
    int W =50;
    int i = 0;

    int n = sizeof(item_v)/sizeof(item_v[0]);

    int comb;
    comb = (int*)malloc(sizeof(int)*n);

    printf("%d \t", dyn(W,item_v,item_w,n,comb));
    for(int i = 0; i < n; i++){
        printf("%d ", comb[i]);
    }
}
