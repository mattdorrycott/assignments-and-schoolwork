#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1024

int main() {
	double stopTime;
	double startTime;
	startTime = clock();
	static float A[N][N];
	static float B[N][N];
	static float C[N][N];
	srand(time(0));
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			A[i][j] = rand()/(float)RAND_MAX*5;
			B[i][j] = rand()/(float)RAND_MAX*5;
			C[i][j] = 0;
		}
	}
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			for(int k=0; k<N; k++) {
				C[i][k] += A[j][k] * B[j][k];
			}
		}
	}
	stopTime = clock();
	printf("Time Consumed: %.3f\n", (stopTime-startTime)/CLOCKS_PER_SEC);
	/*
	printf("\nA = \n");
	for(int i=0; i<N; i++) {
		for(int j=0; j<N;j++) {
			printf("%.3f ", A[i][j]);
		}
		printf("\n");
	}
	printf("\nB = \n");
	for(int i=0; i<N; i++) {
		for(int j=0; j<N;j++) {
			printf("%.3f ", B[i][j]);
		}
		printf("\n");
	}
	printf("\nA*B = \n");
	for(int i=0; i<N; i++) {
		for(int j=0; j<N;j++) {
			printf("%.3f ", C[i][j]);
		}
		printf("\n");
	}
	*/
}
