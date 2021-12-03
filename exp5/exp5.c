#include <stdio.h>
#include <string.h>
#include <mpi.h>
#define BUFSIZE 32 
char m[5][20]={"\nHello","\nRVCE","\nCSE","\n7th Sem","\nHPC"};
int main(int argc,char **argv)
{
 char mess[32];
 int root=0;
 int tag =0;
 int myRank,numProcs,temp=1;
 MPI_Init(&argc,&argv);
 MPI_Status status;
 MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
 MPI_Comm_size(MPI_COMM_WORLD,&numProcs);
 if(myRank==0)
 {
  for(temp=1;temp<numProcs;temp++)
  {
   strcpy(mess,m[temp-1]);
   MPI_Send(&mess,BUFSIZE,MPI_CHAR,temp,tag,MPI_COMM_WORLD);
  } 
 }
 else
 {
  MPI_Recv(&mess,BUFSIZE,MPI_CHAR,root,tag,MPI_COMM_WORLD,&status);
  printf("%s is message process of rank %d sent to process of rank %d",mess,myRank,root);
 }
 MPI_Finalize();
 return 0;
}
