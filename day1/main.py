

from typing import Generator, Optional


def load_data(path: str) -> Generator[str, None, None]:
	prev: Optional[int] = None
	with open(path, 'r') as input:	
		while current := input.readline():
			current = int(current)
			if prev:
				yield prev, current
			prev = current


def problem_1():
	times  = 0
	for prev, current in load_data('input.txt'):
		if prev < current:
			times += 1

	print('[1] Sunk {} times'.format(times))


def problem_2():
	times = 0
	with open('input.txt', 'r') as input:
		lines = [int(depth) for depth in input.readlines()]
		groups = [lines[i:i+3] for i in range(0, len(lines) - 2)]
		
		for prev, current in zip(groups, groups[1:]):
			if sum(prev) < sum(current):
				times += 1

	print('[2] Sunk {} times'.format(times))
		

if __name__ == '__main__':
	problem_1()
	problem_2()