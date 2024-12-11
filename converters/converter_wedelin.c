/*
$B!&(Bwedelin$B%?%$%W$N%$%s%9%?%s%9$r(Bscp$B%?%$%W$N%U%)!<%^%C%H$KJQ49$9$k%W%m%0%i%`$G$9!#(B
$B!&%3%s%Q%$%k$NJ}K!$O!"(B

     % gcc -O2 -o wedelin2scp wedelin2scp.c

  $B$G$9!#<B9T%U%!%$%k(B 'wedelin2scp' $B$,$G$-$^$9!#(B
$B!&;H$$J}$O!"(B

     % gunzip -c sasjump.dat.gz | ./wedelin2scp

  $B$G$9!#(B
*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


/*** $B%Q%i%a!<%?(B *********************************************************/  
static int m;       /*** $BMWAG?t(B ***/
static int n;       /*** $B=89g?t(B ***/

static int **row;   /*** i$BHVL\$NMWAG$,B0$9$k=89g$NHV9f(B ***/
static int **col;   /*** j$BHVL\$N=89g$K4^$^$l$kMWAG$NHV9f(B ***/
static int *cost;   /*** j$BHVL\$N=89g$N=E$_(B ***/
static int *ncol;   /*** i$BHVL\$NMWAG$,B0$9$k=89g?t(B ***/
static int *nrow;   /*** j$BHVL\$N=89g$K4^$^$l$kMWAG?t(B ***/



/*** $B4X?t(B ****************************************************************/
void readscp(void);             /*** $BLdBj$NFI$_9~$_(B ***/
void output(void);              /*** $BLdBj$N=PNO(B ***/
void *malloc_e(size_t size);    /*** $B%(%i!<8!=PIU$-(Bmalloc$B4X?t(B ***/


/*** wedelin$B%?%$%WLdBj$NFI$_9~$_(B *********************************************/
void readscp(void) {
  int i,j,k;
  //FILE *fp=stdin;
  FILE *fp;
  fp=fopen("sasjump.dat","r");
  
  fscanf(fp,"%d",&m);   /*** $BMWAG?t$NFI$_9~$_(B ***/ 
  fscanf(fp,"%d",&n); /*** $B=89g?t$NFI$_9~$_(B ***/
  
  /*** $BG[Ns$N3NJ](B ***/
  row=(int **)malloc_e(m*sizeof(int *));
  col=(int **)malloc_e(n*sizeof(int *));
  cost=(int *)malloc_e(n*sizeof(int));
  ncol=(int *)malloc_e(m*sizeof(int));
  nrow=(int *)malloc_e(n*sizeof(int));
  
  /*** $BLdBj$NFI$_9~$_(B ***/
  for(i=0;i<m;i++) ncol[i]=0;
  for(j=0;j<n;j++) {
    fscanf(fp,"%d",&cost[j]);   /*** $B=E$_$NFI$_9~$_(B ***/
    fscanf(fp,"%d",&nrow[j]);   /*** nrow[j] $B$NFI$_9~$_(B ***/
    col[j]=(int *)malloc_e(nrow[j]*sizeof(int));
    for(k=0;k<nrow[j];k++) {
      fscanf(fp,"%d",&col[j][k]);   /*** col[j][k] $B$NFI$_9~$_(B ***/
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


/*** scp$B%?%$%W$KJQ49$7$?LdBj$N=PNO(B ***************************************/
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


/*** $B%(%i!<8!=PIU$-(Bmalloc$B4X?t(B *******************************************/
void *malloc_e(size_t size) {
  void *s;
  if ((s=malloc(size))==NULL) {
    fprintf(stderr, "malloc : Not enough memory.\n");
    exit(EXIT_FAILURE);
  }
  return s;
}



/*** $B%a%$%s4X?t(B *********************************************************/
int main(void) {
  readscp();
  printf("read\n");
  output();

  return EXIT_SUCCESS;
}


