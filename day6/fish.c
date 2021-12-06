
#include <stdint.h>
#include <stdio.h>

#define CYCLE_MAX			8
#define BIRTH_PUSHBACK		6
#define SIMULATE_DAYS 		256

typedef uint64_t LanternfishArray[9];

uint64_t sum(LanternfishArray arr) {
	uint64_t _s = 0;
	for(int i = 0; i < 9; ++i) _s += arr[i];

	return _s; 
}

uint64_t simulate(const char *path, int days) {
	FILE *file = fopen(path, "r");
	if (!file) {
		printf("\033[31;1m[Error] No such file '%s'\033[0m\n", path);
		return 0;
	}

	LanternfishArray lanternfish = { 0 };
	uint64_t day = 0;
	while(fscanf(file, "%zu,", &day) == 1)
		lanternfish[day]++;

	for(int i = 0; i < days; ++i) {
		uint64_t newborns = *lanternfish;
		for(int k = 1; k < 9; ++k) {
			lanternfish[k - 1] = lanternfish[k]; 
		}

		lanternfish[6] += newborns;
		lanternfish[8] = newborns;
	}

	fclose(file);
	return sum(lanternfish);
}

int main() {
	const int PROBLEM_1_SIM_LEN = 80;
	const int PROBLEM_2_SIM_LEN = 256;

	// Tests
	uint64_t test1 = simulate("demo.txt", 18);
	uint64_t test2 = simulate("demo.txt", PROBLEM_1_SIM_LEN);
	uint64_t test3 = simulate("demo.txt", PROBLEM_2_SIM_LEN);

	const uint64_t test1exp = 26;
	const uint64_t test2exp = 5934;
	const uint64_t test3exp = 26984457539;

	if(test1 != test1exp) { printf("\033[31;1m[Error] Test 1 failed\033[0m\n"); return -1; }
	if(test2 != test2exp) { printf("\033[31;1m[Error] Test 2 failed\033[0m\n"); return -1; }
	if(test3 != test3exp) { printf("\033[31;1m[Error] Test 3 failed\033[0m\n"); return -1; }

	printf("\033[32;1m[Passed all tests]\033[0m\n");

	// Solutions
	uint64_t problem1 = simulate("lanternfish.txt", PROBLEM_1_SIM_LEN);
	uint64_t problem2 = simulate("lanternfish.txt", PROBLEM_2_SIM_LEN);

	printf("After %d days will be %zu fish\n", PROBLEM_1_SIM_LEN, problem1);
	printf("After %d days will be %zu fish\n", PROBLEM_2_SIM_LEN, problem2);
	return 0;
}