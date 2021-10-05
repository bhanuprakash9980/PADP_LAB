#include<stdio.h>
#include<omp.h>
int main(int argc,char* argv[])
{ int nt=8;
 omp_set_num_threads(nt);
	#pragma omp parallel
	printf("Hello World!\n");
}