#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int max(int x, int y){return (x > y) ? x:y ;}

int subsetsum(int total_sum,int arr_v[], int n){
    if(total_sum == 0){
        return 1;
    }
    if( n== 0){
        return 0;
    }
    if(arr_v[n-1] > total_sum){
        return subsetsum(total_sum, arr_v, n-1);
    }
    else{
        return max(subsetsum(total_sum, arr_v, n-1), subsetsum(total_sum - arr_v[n - 1], arr_v, n-1));
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
    fseek(file,0,SEEK_SET);
    int i = 0;
    while(!(feof(file))){
        fscanf(file, "%d", &item_V[i]);
        i++;
    }

    size_t n = linesCount+1;
    printf("o valor maximo existe ? %d", subsetsum(W,item_V, n));
    return 0;
}
