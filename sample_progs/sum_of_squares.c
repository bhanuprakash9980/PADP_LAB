#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{	int i;
	float a[100],b[100],sum=0.0;
	for(i=0;i<100;i++)
		a[i] = b[i] =i;
	#pragma omp parallel for(+:sum)
	for(i=0;i<100;i++)
		sum = sum + (a[i] * b[i]);
	printf("Sum = %f\n",sum);
}