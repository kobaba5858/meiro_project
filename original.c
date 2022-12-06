/*
    迷路ゲーム
    
*/

#include<stdio.h>  // 何の関数のためのインクルードか表示しておく(自分のため)
#include<stdlib.h> // 同上 
#include<termios.h>
#include<unistd.h>
#include<fcntl.h> 

#define GYO 10  // 迷路の行数
#define RETU 10 // 迷路の列数

 /* kbhitの定義 */
 int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar(); 

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
	return 0;
} 

// 迷路マップデータ
int meiro[GYO][RETU] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int px, py; // プレイヤーのxy座標
int goal_count; // 塗りつぶすべき床の数
int count;  //  塗りつぶした床の数

// マップ表示
void display_meiro(void){
    int x, y;
    for(y=0; y<GYO; y++){
        for(x=0; x<RETU; x++){
            if(x == px && y == py){ //  プレイヤーの位置のとき
                meiro[y][x] = 2;    //  塗りつぶす
                count++;            //  塗りつぶした数をカウント
                printf("人");       //  プレイヤー
            }
            else if(meiro[y][x] == 0)   //  移動可能な床
                printf("  ");           //  全角スペース
            else if(meiro[y][x] == 1)   //  壁
                printf("ww");
            else if(meiro[y][x] == 2)   //塗った床
                printf("xx");
        }
        printf("\n");
    }
    printf("cmd: ↑↓←→ ,restart: space\n");    //  操作説明
    printf("塗りつぶすべき床の数：%d\n", goal_count);  // 塗りつぶすべき床の数を表示
    printf("現在の塗りつぶした床の数：%d\n", count);  // 現在の塗りつぶした床の数を表示させる
}

// 初期状態に戻る
void return_start(void){
    int x, y;
    count = 0; /* 塗りつぶすべき床の数をリセット*/
    px = 1;     /* プレイヤーのx座標 */
    py = 1;     /* プレイヤーのy座標 */
    for(y=0; y<GYO; y++){
        for(x=0; x<RETU; x++){
            if(meiro[y][x] == 2){
                meiro[y][x] = 0;   // 塗りつぶした床をもとに戻す
            }
        }
    }
}

// 塗りつぶすべき床の数をカウント
void goal_count_check(void){
    int x, y;
    goal_count = 0;
    for(y=0; y<GYO; y++){
        for(x=0; x<RETU; x++){
            if(meiro[y][x] == 0){
                goal_count++;   // 移動可能な床の数をカウントする
            }
        }
    }
}


//  キー入力
void key_input(void){
    int key;
    while(1){   //  キーが入力されるのを待つ
        if( kbhit() ){
            key = getchar();
            break;
        }
    }

    if(key == 32){      /* spaceキー */
        return_start(); /* 最初の状態に戻る */
    }else if (key == 27){
            key = getchar();
                if(key == 91){
                    key = getchar();
                    if(key == 65 && meiro[py-1][px] == 0)          /* ↑キー */
                        py --;  /* 上に移動 */
                    else if(key == 66 && meiro[py+1][px] == 0)     /* ↓キー */
                        py ++;  /* 下に移動 */
                    else if(key == 67 && meiro[py][px+1] == 0)     /* →キー */
                        px ++;  /* 右に移動 */
                    else if(key == 68 && meiro[py][px-1]== 0)      /* ←キー */
                        px --;  /* 左に移動 */
                }
    else                    /* 上記以外のキーの場合 */
        key_input();        /* 再度キー入力受付 */
    }
}
   
int main(void){
    px = 1;     /* プレイヤーのx座標 */
    py = 1;     /* プレイヤーのy座標 */
    count = 0;  /* 塗りつぶした床の数 */

    goal_count_check();     /* 塗りつぶすべき床の数をカウントする */

/* ゲームループ */
    while(1){
        system("clear");      /* コンソール画面をクリア */
        display_meiro();       /* 迷路を表示 */

        if(count == goal_count){        /* 床を全て塗りつぶしたかのチェック */
            printf("全て塗れました！\n");
            break;
        }

        key_input();        /* キー入力受付 */
    }
    return 0;
}