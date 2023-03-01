#include <stdio.h>
int main() {
	int n;
	scanf("%d", &n);
	int nOri = n;	
	int nRev = 0;
	while (n % 10) {
		nRev *= 10;	
		nRev += n % 10;
		n /= 10;
	}

	if (nOri == nRev) {
		printf("Y\n");
	} else {
		printf("N\n");
	}
	return 0;
}
