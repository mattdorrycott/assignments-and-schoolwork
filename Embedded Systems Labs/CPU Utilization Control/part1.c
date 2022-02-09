#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	double start, end;
	start = clock();
	int result = 0;
	const long int repeating_time = 500000000;
	for(long int i=0; i<repeating_time; i++) {
		if(result > 1000) {
			result -= 1;
		}
		else {
			result += 1;
		}
	}
	end = clock();
	printf("\nExecution Time: %.5f\n", (end-start)/CLOCKS_PER_SEC);
	return 0;
}
