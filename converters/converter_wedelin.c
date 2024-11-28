/*
・wedelinタイプのインスタンスをscpタイプのフォーマットに変換するプログラムです。
・コンパイルの方法は、

     % gcc -O2 -o wedelin2scp wedelin2scp.c

  です。実行ファイル 'wedelin2scp' ができます。
・使い方は、

     % gunzip -c sasjump.dat.gz | ./wedelin2scp

  です。
*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


/*** パラメータ *********************************************************/  
static int m;       /*** 要素数 ***/
static int n;       /*** 集合数 ***/

static int **row;   /*** i番目の要素が属する集合の番号 ***/
static int **col;   /*** j番目の集合に含まれる要素の番号 ***/
static int *cost;   /*** j番目の集合の重み ***/
static int *ncol;   /*** i番目の要素が属する集合数 ***/
static int *nrow;   /*** j番目の集合に含まれる要素数 ***/



/*** 関数 ****************************************************************/
void readscp(void);             /*** 問題の読み込み ***/
void output(void);              /*** 問題の出力 ***/
void *malloc_e(size_t size);    /*** エラー検出付きmalloc関数 ***/


/*** wedelinタイプ問題の読み込み *********************************************/
void readscp(void) {
  int i,j,k;
  //FILE *fp=stdin;
  FILE *fp;
  fp=fopen("sasjump.dat","r");
  
  fscanf(fp,"%d",&m);   /*** 要素数の読み込み ***/ 
  fscanf(fp,"%d",&n); /*** 集合数の読み込み ***/
  
  /*** 配列の確保 ***/
  row=(int **)malloc_e(m*sizeof(int *));
  col=(int **)malloc_e(n*sizeof(int *));
  cost=(int *)malloc_e(n*sizeof(int));
  ncol=(int *)malloc_e(m*sizeof(int));
  nrow=(int *)malloc_e(n*sizeof(int));
  
  /*** 問題の読み込み ***/
  for(i=0;i<m;i++) ncol[i]=0;
  for(j=0;j<n;j++) {
    fscanf(fp,"%d",&cost[j]);   /*** 重みの読み込み ***/
    fscanf(fp,"%d",&nrow[j]);   /*** nrow[j] の読み込み ***/
    col[j]=(int *)malloc_e(nrow[j]*sizeof(int));
    for(k=0;k<nrow[j];k++) {
      fscanf(fp,"%d",&col[j][k]);   /*** col[j][k] の読み込み ***/
      col[j][k]--;
      ncol[col[j][k]]++;
    }
  }
  for(i=0;i<m;i++) {
    row[i]=(int *)malloc_e(ncol[i]*sizeof(int)); 
    ncol[i]=0;
  }
  for(j=0;j<n;j++) {
    for(k=0;k<nrow[j];k++) {
      row[col[j][k]][ncol[col[j][k]]]=j;
      ncol[col[j][k]]++;
    }
  }
}


/*** scpタイプに変換した問題の出力 ***************************************/
void output(void) {
  int h,i,j;
  FILE *fptr;
  fptr=fopen("sasjump.txt","w");
  printf("%d %d\n",m,n);
  fprintf(fptr,"%d %d\n",m,n);
  for(j=0;j<n;j++) {
    printf("%d ",cost[j]);
    fprintf(fptr,"%d ",cost[j]);
  }
  printf("\n");
  fprintf(fptr,"\n");
  for(i=0;i<m;i++) {
    printf("%d\n",ncol[i]);
    fprintf(fptr,"%d\n",ncol[i]);
    for(h=0;h<ncol[i];h++) {
      printf("%d ",row[i][h]+1);
      fprintf(fptr,"%d ",row[i][h]+1);
    }
    printf("\n");
    fprintf(fptr,"\n");
  }
}


/*** エラー検出付きmalloc関数 *******************************************/
void *malloc_e(size_t size) {
  void *s;
  if ((s=malloc(size))==NULL) {
    fprintf(stderr, "malloc : Not enough memory.\n");
    exit(EXIT_FAILURE);
  }
  return s;
}



/*** メイン関数 *********************************************************/
int main(void) {
  readscp();
  printf("read\n");
  output();

  return EXIT_SUCCESS;
}


