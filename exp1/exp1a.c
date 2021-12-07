//Bhanu Prakash
//1RV18CS039
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define SEED 35791246

void main(int argc,char **argv)
{
	
 int n=0,i,count=0;
 int n_threads=1;
 double z,pi,x,y;
double st =0.0, end=0.0;
printf("iter/threads\t");

for(i=1;i<=8;i*=2)
printf("pi\t\t%d\t\t",i);
for (n=1000;n<=1000000;n*=10)
{ 
 n_threads=1;
printf("\n%d\t",n);
	while(n_threads<=8){
 count=0;
 
	

 srand(SEED);
 st =0.0;
 end=-1.0;
 st = omp_get_wtime();
 omp_set_num_threads(n_threads);
 

 #pragma omp parallel for

 for (i = 1; i <n ;i++) {
  x=(double)rand()/RAND_MAX;
  y=(double)rand()/RAND_MAX;
  z=x*x+y*y;
  if(z<=1) count++;
}
pi=(double)count/n*4;
end = omp_get_wtime();
printf("%lf\t",pi);
printf("%lf\t",end-st);
n_threads=n_threads*2;

}}
 
	
}
