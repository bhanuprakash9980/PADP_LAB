//Bhanu Prakash
//1RV18CS039
#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{int n_t,size;
 for(size = 250; size<= 1000; size+=250)
 { printf("SIZE = %d\n\n",size);
	 for(n_t=1;n_t<=8;n_t*=2)
	{printf("# of threads = %d\t",n_t);
		int r=size,c=size,i,j,count=0,sum=0,k;
		int **arr1 = (int **)malloc(r* sizeof(int*));
		for(i=0;i<r;i++)
			arr1[i] = (int *)malloc(c*sizeof(int*));
			int **arr2 = (int **)malloc(r* sizeof(int*));
		for(i=0;i<r;i++)
			arr2[i] = (int *)malloc(c*sizeof(int*));
			int **arr3 = (int **)malloc(r* sizeof(int*));
		for(i=0;i<r;i++)
			arr3[i] = (int *)malloc(c*sizeof(int*));
for(i=0;i<r;i++)
	for(j=0;j<c;j++)
		arr1[i][j]=count++;
	for(i=0;i<r;i++)
	for(j=0;j<c;j++)
		arr2[i][j]=count++;	
		double x = omp_get_wtime();
		omp_set_num_threads(n_t);
		#pragma omp parallel for private(j,k)
		for(i=0;i<r;i++)
	for(j=0;j<c;j++)
		for(k=0;k<r;k++)
			arr3[i][j]+=arr1[i][k]*arr2[k][j];
	double y = omp_get_wtime();	
		printf("%lf\n",y-x);
		
	}}
	
 return 0;
}