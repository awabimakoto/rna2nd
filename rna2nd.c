#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
void fill(int n, int *seqn, int **s, int **w, int k);
void traceback(int i, int j, int **s, int **w, char *seq);
int max(int i, int j, int **s);
int main(){
  char *seq;
  seq=(char *)malloc(sizeof(char)*1000);
  int n;
  int i;
  int j;
  int k;
  printf("Input minimal hairpin length:");
  scanf("%d",&k);
  printf("Input sequence:");
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
  int **s,**w;
  s=(int **)malloc(sizeof(int *)*n);
  w=(int **)malloc(sizeof(int *)*n);
  for(i=0;i<n;i++){
    s[i]=(int *)malloc(sizeof(int)*n);
    w[i]=(int *)malloc(sizeof(int)*n);
    memset(*(s+i),0,sizeof(int)*n);}
  fill(n,seqn,s,w,k);
  printf("The sequence is: %s\nBase pair(s) found:\n",seq);
  traceback(0,n-1,s,w,seq);
  return 0;}
void fill(int n, int *seqn, int **s, int **w, int k){
  int i=0;
  int j=0;
  while(++k<n){
    j=k-1;
    while(++j<n){
      i=j-k;
      if(*(seqn+i)+*(seqn+j)==3)
	*(*(w+i)+j)=1;
      else
	*(*(w+i)+j)=0;
      if(*(*(s+i+1)+j-1)+*(*(w+i)+j)>max(i,j,s))
	*(*(s+i)+j)=*(*(s+i+1)+j-1)+*(*(w+i)+j);
      else
	*(*(s+i)+j)=max(i,j,s);}}
}
void traceback(int i, int j, int **s, int **w, char *seq){
  int k;
  if(i<j)
    if(*(*(s+i)+j)==*(*(s+i+1)+j))
      traceback(i+1,j,s,w,seq);
    else if(*(*(s+i)+j)==*(*(s+i)+j-1))
      traceback(i,j-1,s,w,seq);
    else if(*(*(s+i)+j)==*(*(s+i+1)+j-1)+*(*(w+i)+j)){
      printf("%d(%c) - %d(%c)\n",i+1,*(seq+i),j+1,*(seq+j));
      traceback(i+1,j-1,s,w,seq);}
 else
   for(k=i+1;k<j-1;k++)
     if(*(*(s+i)+j)==*(*(s+i)+k)+*(*(s+k+1)+j)){
       traceback(i,k,s,w,seq);
       traceback(k+1,j,s,w,seq);
       break;}
}
int max(int i, int j, int **s){
  int k;
  int tmp=0;
  for(k=i;k<j;k++)
    if(tmp<*(*(s+i)+k)+*(*(s+k+1)+j))
      tmp=*(*(s+i)+k)+*(*(s+k+1)+j);
  return tmp;}
