#include<stdio.h>

#define WHIDTH 5  // xで管理
#define HEIGHT 5  // yで管理

int main(void){
    int x, y;
    int meiro[HEIGHT][WHIDTH];

    FILE *test;

    test = fopen("test.txt","r");

    if(test == NULL){
    printf("ファイルを開けませんでした。\n");
    return 1;
    }

    for(y = 0; y < HEIGHT; y++){
      for(x = 0; x < WHIDTH; x++){
        fscanf(test, "%d", &meiro[y][x]);
      }
    }

    fclose(test);

    for(y = 0; y < HEIGHT; y++){
      for(x = 0; x < WHIDTH; x++){
        printf("test[%d][%d] = %d ", y, x, meiro[y][x]);
      }
      printf("\n");
    }
    
    return 0;
}