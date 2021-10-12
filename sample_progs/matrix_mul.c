// C program to multiply two matrices.

#include <stdio.h>

const int MAX = 100;

// Function to print Matrix
void printMatrix(int M[][MAX], int rowSize, int colSize)
{
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++)
			printf("%d ", M[i][j]);

		printf("\n");
	}
}

// Function to multiply two matrices A[][] and B[][]
void multiplyMatrix(int row1, int col1, int A[][MAX],
					int row2, int col2, int B[][MAX])
{
	int i, j, k;

	// Matrix to store the result
	int C[MAX][MAX];

	// Check if multiplication is Possible
	if (row2 != col1) {
		printf("Not Possible\n");
		return;
	}

	// Multiply the two
	for (i = 0; i < row1; i++) {
		for (j = 0; j < col2; j++) {
			C[i][j] = 0;
			for (k = 0; k < row2; k++)
				C[i][j] += A[i][k] * B[k][j];
		}
	}

	// Print the result
	printf("\nResultant Matrix: \n");
	printMatrix(C, row1, col2);
}

// Driven Program
int main()
{
	int row1, col1, row2, col2, i, j;
	int A[MAX][MAX], B[MAX][MAX];

	// Read size of Matrix A from user
	printf("Enter the number of rows of First Matrix: ");
	scanf("%d", &row1);
	printf("%d", row1);
	printf("\nEnter the number of columns of First Matrix: ");
	scanf("%d", &col1);
	printf("%d", col1);

	// Read the elements of Matrix A from user
	printf("\nEnter the elements of First Matrix: ");
	for (i = 0; i < row1; i++) {
		for (j = 0; j < col1; j++) {
			printf("\nA[%d][%d]: ", i, j);
			scanf("%d", &A[i][j]);
			printf("%d", A[i][j]);
		}
	}

	// Read size of Matrix B from user
	printf("\nEnter the number of rows of Second Matrix: ");
	scanf("%d", &row2);
	printf("%d", row2);
	printf("\nEnter the number of columns of Second Matrix: ");
	scanf("%d", &col2);
	printf("%d", col2);

	// Read the elements of Matrix B from user
	printf("\nEnter the elements of First Matrix: ");
	for (i = 0; i < row2; i++) {
		for (j = 0; j < col2; j++) {
			printf("\nB[%d][%d]: ", i, j);
			scanf("%d", &B[i][j]);
			printf("%d", B[i][j]);
		}
	}

	// Print the Matrix A
	printf("\n\nFirst Matrix: \n");
	printMatrix(A, row1, col1);

	// Print the Matrix B
	printf("\nSecond Matrix: \n");
	printMatrix(B, row2, col2);

	// Find the product of the 2 matrices
	multiplyMatrix(row1, col1, A, row2, col2, B);

	return 0;
}
