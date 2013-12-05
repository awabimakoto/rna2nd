#include<stdio.h>
#include<ctype.h>
#include<string.h>
void fill(int n, int *seqn, int **s);
int max(int i, int j, int **s);
void main(){
  char *seq;
  seq=(char *)malloc(sizeof(char)*50);
  int n;
  int i;
  int j;
  printf("input sequence:");
  scanf("%s",seq);
  n=strlen(seq);
  for(i=0;i<n;i++)
    seq[i]=toupper(seq[i]);
  i=-1;
  while(++i<n)
    if(seq[i]!='U' && seq[i]!='C' && seq[i]!='A' && seq[i]!='G'){
      j=i;
      while(++j<=n)
	seq[j-1]=seq[j];
      n--;}
  int seqn[n];
  for(i=0;i<n;i++)
    switch(seq[i]){
    case 'A':
      seqn[i]=0;break;
    case 'C':
      seqn[i]=1;break;
    case 'G':
      seqn[i]=2;break;
    case 'U':
      seqn[i]=3;break;}
  int **s;
  s=(int **)malloc(sizeof(int *)*n);
  for(i=0;i<n;i++){
    s[i]=(int *)malloc(sizeof(int)*n);
    memset(*(s+i),0,sizeof(int)*n);}
  fill(n,seqn,s);
  for(i=0;i<n;i++){
    for(j=0;j<n;j++)
      printf("%d",*(*(s+i)+j));
    printf("\n");
  }
}
void fill(int n, int *seqn, int **s){
  int i=0;
  int j=0;
  int k=0;
  int v;
  while(++k<n){
    j=k-1;
    while(++j<n){
      i=j-k;
      if(*(seqn+i)+*(seqn+j)==3)
	v=1;
      else
	v=0;
      if(*(*(s+i+1)+j-1)+v>max(i,j,s))
	*(*(s+i)+j)=*(*(s+i+1)+j-1)+v;
      else
	*(*(s+i)+j)=max(i,j,s);}}
}
int max(int i, int j, int **s){
  int k;
  int tmp=0;
  for(k=i;k<j;k++)
    if(tmp<*(*(s+i)+k)+*(*(s+k+1)+j))
      tmp=*(*(s+i)+k)+*(*(s+k+1)+j);
  return tmp;}
