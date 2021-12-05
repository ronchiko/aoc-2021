
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE	1000

int main(void) {
	FILE *lines = fopen("lines.txt", "r"); 
	
	int *board = calloc(SIZE * SIZE, sizeof(int));
	
	int x1, x2, y1, y2;
	while(fscanf(lines, "%d,%d -> %d,%d\n", &x1, &y1, &x2, &y2) == 4) {
		if(x1 == x2) {
			for(int y=min(y1, y2);y<=max(y2, y1);++y) board[y * SIZE + x1]++; 
		}else if(y1 == y2)
			for(int x=min(x1, x2);x<=max(x1, x2);++x) board[y1 * SIZE + x]++;
		else{
			int tb = y2 - y1;
			int lr = x2 - x1;
			int len = max(abs(tb), abs(lr));
			tb = tb > 0 ? 1 : -1; lr = lr > 0 ? 1 : -1;
			for(int i=0;i<=len;++i) board[(y1 + tb * i) * SIZE + (x1 + lr * i)]++;
		}
	}

	int results = 0;
	for(int i = 0; i < SIZE * SIZE; ++i) {
		if(board[i] > 1) ++results;
	}

	printf("%d collisions\n", results);

	fclose(lines);
	return 0;
}