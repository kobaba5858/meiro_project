#include<stdio.h>

int main(void){
  int x, y;
  int meiro[10][10];
  
  FILE *test;

  test = fopen("test.txt","r");
  
  if(test == NULL){
    printf("ファイルを開けませんでした。\n");
    return 1;
  }

  for(y = 0; y<10; y++){
    for(x = 0; x<10; x++){
      fscanf(test, "%d", &meiro[y][x]);
    }
  }

  fclose(test);

  for(y = 0; y<10; y++){
     for(x = 0; x<10; x++){
      printf("%d", meiro[y][x]);
     }
     printf("\n");
   }
  return 0;
}
