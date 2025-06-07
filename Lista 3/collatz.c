#include <stdio.h>
#include <stdint.h>

int collatz(int32_t n){
	int i = 0; // To count how many steps it takes to get to 1
	
	if( n <= 1){
		return -1;
	}

	do {
		i++;

		if (n & 1){
			n = n*3 + 1;
		} else {
			n /= 2;
		}

	}while (n > 1);

	return i;
}

int main(){

	int32_t n;

	scanf("%d", &n);

	int res = collatz(n);

	if( res == -1 ){
		printf("entrada invalida.\n");
	} else {
		printf("%d\n", res);
	}

	return 0;
}
