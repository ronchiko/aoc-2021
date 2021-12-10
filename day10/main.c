
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

char OPENER_TO_CLOSER[] = {
	['('] = ')',
	['['] = ']',
	['{'] = '}',
	['<'] = '>'
};

int CORRUPTION_PENALTIES[] = {
	[')'] = 3,
	[']'] = 57,
	['}'] = 1197,
	['>'] = 25137
};

int INCOMPLETE_PENALTIES[] = {
	[')'] = 1,
	[']'] = 2,
	['}'] = 3,
	['>'] = 4
};

void IncompleteOrCorrupted(const char *line, int *corruption, int64_t *incomplete) {
	char stack[256] = { 0 }; 
	int current = -1;

	for(const char *c = line; *c; ++c) {
		switch(*c) {
		case '(': case '[': case '{': case '<':
			stack[++current] = OPENER_TO_CLOSER[*c];
			break;
		default:
			if (stack[current] != *c) {
				*corruption += CORRUPTION_PENALTIES[*c];
				return;
			}
			--current;
			break;
		}
	}
	
	*incomplete = 0;
	while (current >= 0)
		*incomplete = *incomplete * 5 + INCOMPLETE_PENALTIES[stack[current--]];  
}

int compareInts(const void *a, const void *b) { 
	int64_t a64 = *(int64_t *)a,  b64 = *(int64_t *)b; 
	return a64 > b64 ? 1 : b64 > a64 ? -1 : 0;
}

int main() {
	FILE *file = fopen("main.txt", "r");

	char line[512]; 
	int corruptionScore = 0;
	int64_t incompletes[200], len = 0;
	while (fscanf(file, "%511s\n", line) > 0) {
		int64_t incomplete = 0;
		IncompleteOrCorrupted(line, &corruptionScore, &incomplete);

		if (incomplete > 0) {
			incompletes[len++] = incomplete;
		}
	}

	qsort(incompletes, len, sizeof(int64_t), &compareInts);

	printf("The total corruption score is %d\n", corruptionScore);
	printf("The incompletes score is %lld\n", incompletes[len >> 1]);

	fclose(file);
	return 0;
}