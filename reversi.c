#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NONPLACE   (0U)
#define WHITE      (1U)
#define BLACK      (2U)
#define PRERESERVE (3U)
#define RESERVE    (4U)

#define OK         (0U)
#define NG         (1U)

/* direction */
#define UPPERLEFT  (0U)
#define UPPER      (1U)
#define UPPERRIGHT (2U)
#define RIGHT      (3U)
#define LOWERRIGHT (4U)
#define LOWER      (5U)
#define LOWERLEFT  (6U)
#define LEFT       (7U)

/* sort of function */
#define PUT_CHECK  (0U)
#define INPUT_PROC (1U)

/* prototype */
void draw(char board[8][8]);
char put_check(void);
void input_proc(void);
char reserve_check(char x, char y, char func);
void game_end(void);
char check_input(char *input);
void ret_reserve(void);
void change_turn(void);

/* global variable */
char board[8][8] = {{0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,2,1,0,0,0},
                    {0,0,0,1,2,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0}};
char myturn = BLACK;

void main (void) {
  char game_flag = 0U;
  char flag;

  while(game_flag<2){
    if ((put_check()) == OK){
      draw(board);
      input_proc();
      game_flag = 0U; /* clear game_flag */
    }
    else {
      change_turn();
      game_flag++;
    }
  }
  game_end();
}

char put_check(){
  char x;
  char y;
  char flag;

  for(y=1; y<9; y++){
    for(x=1; x<9; x++) {
      if(board[x-1][y-1] == NONPLACE) {
        if((reserve_check(x, y, PUT_CHECK)) == OK){
          flag = 0U;
          return flag;
        }
      }
    }
  }
  flag = 1U;
  return flag;
}

void input_proc(){
  char  coordinate[128];
  char ret = NG;
  int  x,y;

  if (myturn == BLACK){
    printf("\n 黒の番です 座標を入力してください(横縦)：");
  } 
  else {
    printf("\n 白の番です 座標を入力してください(横縦)：");
  }
  while (ret != OK ){
    scanf("%s",coordinate); /* input coordinate */
    if ( (ret = check_input(coordinate)) == OK ) {
      sscanf(coordinate,"%1d%1d",&x,&y);
      if ((ret = reserve_check(x, y, INPUT_PROC)) != OK ){
        printf("\n 配置できません 座標を再入力してください(横縦)：");
      }
      else {
        board[x-1][y-1] = myturn;
        change_turn();
      }
    }
    else {
      printf("\n 入力ミスです 座標を再入力してください(横縦)：");
    }
  }
  return;
}

void game_end(void){
  char black_num = 0U;
  char white_num = 0U;
  char x,y;

  draw(board);
  for(x=1; x<9; x++){
    for(y=1; y<9; y++){
      if(board[x-1][y-1] == BLACK){
        black_num++;
      }
      else if(board[x-1][y-1] == WHITE){
        white_num++;
      }
    }
  }
  printf("\n ゲーム終了です 黒%d 白%d ",black_num, white_num);
  if(black_num > white_num){
    printf("\n 黒の勝ちです \n");
  }
  else if (white_num > black_num){
    printf("\n 白の勝ちです \n");
  }
  else if (black_num == white_num){
    printf("\n 引き分けです \n");
  }
  else {
    /* no process */
  }
  system("pause");
}

char reserve_check(char x, char y, char func){
  char dir; /* direction */
  char dis; /* distance  */
  char a,b;
  char i,j;
  char ret = NG;

  if (board[x-1][y-1] != NONPLACE) {
    return ret;
  }
  for (dir=0; dir<8; dir++){
    for (dis=1; dis<9; dis++){
      switch(dir){
        case UPPERLEFT: /* dir=0 */
          a = x - dis;
          b = y - dis;
        break;
        case UPPER:     /* dir=1 */
          a = x;
          b = y - dis;
        break;
        case UPPERRIGHT:/* dir=2 */
          a = x + dis;
          b = y - dis;
        break;
        case RIGHT:     /* dir=3 */
          a = x + dis;
          b = y;
        break;
        case LOWERRIGHT:/* dir=4 */
          a = x + dis;
          b = y + dis;
        break;
        case LOWER:     /* dir=5 */
          a = x;
          b = y + dis;
        break;
        case LOWERLEFT: /* dir=6 */
          a = x - dis;
          b = y + dis;
        break;
        case LEFT:      /* dir=7 */
          a = x - dis;
          b = y;
        break;
        default:
        break;
      }
      if ((a > 8) || (b > 8) || (a < 1) || (b < 1)) {
        ret_reserve();
        break;
      }
      else if (    ((board[a-1][b-1] == BLACK) || (board[a-1][b-1] == WHITE))
                &&  (board[a-1][b-1] != myturn)) {
        board[a-1][b-1] = PRERESERVE;
      }
      else if (board[a-1][b-1] == myturn){
        for(i=0; i<8; i++){
          for(j=0; j<8; j++){
            if(board[i][j] == PRERESERVE){
              board[i][j] = RESERVE;
            }
          }
        }
        break;
      }
      else {
        ret_reserve();
        break;
      }
    }
  }
  for(a=0; a<8; a++){
    for(b=0; b<8; b++){
      if(board[a][b] == RESERVE){
        if (func == PUT_CHECK){ /* turn back */
          if(myturn == BLACK){
            board[a][b] = WHITE;
          }
          else {
            board[a][b] = BLACK;
          }
        }
        else {
          board[a][b] = myturn; /* change reserved pieces to my pieces */
        }
        ret = OK;
      }
    }
  }
  return ret;
}

void draw(char board[8][8]){
  char x,y;
  /* Draw board */
  printf("\n");
  printf("    1   2   3   4   5   6   7   8  ");
  printf("\n  +---+---+---+---+---+---+---+---+");
  for(y=0; y<8; y++){
    printf("\n%d |",y+1);
    for(x=0; x<8; x++){
      if(board[x][y]==NONPLACE){
        printf("   ");
      }
      else if(board[x][y]==WHITE){
        printf(" ●");
      }
      else if(board[x][y]==BLACK){
        printf(" ○");
      }
      else{
        printf("   ");
      }
      printf("|");
    }
    printf("\n  +---+---+---+---+---+---+---+---+");
  }
}

char check_input(char *input){
  char ret;
  if(strlen(input) != 2){
    ret = NG;
  }
  else if(strspn(input,"12345678") != strlen(input)){
    ret = NG;
  }
  else{
    ret = OK;
  }
  return ret;
}
void ret_reserve(){
  char i,j;
  for(i=0; i<8; i++){
    for(j=0; j<8; j++){
      if(board[i][j] == PRERESERVE){
        if(myturn == BLACK){
          board[i][j] = WHITE;
        }
        else {
          board[i][j] = BLACK;
        }
      }
    }
  }
}

void change_turn(void){
  if (myturn == BLACK){
    myturn = WHITE;
  }
  else {
    myturn = BLACK;
  }
}