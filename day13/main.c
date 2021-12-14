
#include <string.h>
#include <stdlib.h>
#include <stdio.h> 

int *realloc2d(int *src, int *w, int *h, int nw, int nh) {

	const int width = max(*w, nw);
	const int height = max(*h, nh);

	if (width <= *w && height <= *h) {
		return src;
	}

	int *new = malloc(height * width * sizeof(int));
	memset(new, 0,  height * width * sizeof(int));
	for(int i = 0; i < *h; ++i) {
		for(int j = 0; j < *w; ++j) {
			new[i * width + j] = src[i * *w + j];
		}
	}

	*w = width; *h = height;

	free(src);
	return new;
}

void fold_horizontal(int *arr, int *w, int *h, int y) {
	const int width = *w; 
	
	for(int i = 1; i < *h - y; ++i) {
		for(int j = 0; j < width; ++j) {
			arr[(y - i) * width + j] += arr[(y + i) * width + j];
		}
	}

	*h = *h >> 1;
}

int *fold_vertical(int *arr, int *w, int *h, int x) {	
	const int width = *w; 
	int *n = malloc(sizeof(int) * (width >> 1) * *h);

	for(int i = 0; i < *h; ++i) {
		for(int j = 0; j <= (width >> 1); ++j) {
			n[(i + 1) * (width >> 1) - j] = arr[i * width + j + x] + arr[i * width + x - j];
		}
	}

	free(arr);
	*w = width >> 1;
	return n;
}

int count(int *arr, int w, int h) {
	int sum = 0;
	for(int i = 0; i < h; ++i) {
		for(int j = 0; j < w; ++j) {
			if(arr[i * w + j] != 0) ++sum;
		}
	}

	return sum;
}


int main() {
	FILE *file;
	
	errno_t err = fopen_s(&file, "main.txt", "r");
	if(err != 0) {
		printf("Failed to open file\n");
		return -1;
	}

	int w = 0, h = 0;
	int *arr = NULL;

	int x, y;
	while (fscanf_s(file, "%d,%d", &x, &y)) {
		arr = realloc2d(arr, &w, &h, x + 1, y + 1);
		
		arr[x + y * w] = 1;
	}

	
	for(;;) {
		char axis;  int value;

		fscanf_s(file, "fold along %c", &axis);
		fscanf_s(file, "=%d", &value);
		
		switch (axis)
		{
		case 'y':
			fold_horizontal(arr, &w, &h, value);
			break;
		case 'x':
			arr = fold_vertical(arr, &w, &h, value);
			break;
		default:
			printf("Invalid axis %c\n", axis);
			break;
		}

		if(getc(file) == EOF) break;
	}

	printf("final %d\n", count(arr, w, h));
	for(int i = 0; i < h; ++i) {
		for(int j = 0; j < w; ++j) {
			
			printf("%c", arr[i * w + j] != 0 ? '#' : '.');
		}
		printf("\n");
	}

	free(arr);
	fclose(file);
}