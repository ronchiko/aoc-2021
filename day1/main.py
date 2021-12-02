

from os import curdir
from typing import Generator, Optional


def load_data(path: str) -> Generator[str, None, None]:
	prev: Optional[int] = None
	with open(path, 'r') as input:	
		while current := input.readline():
			current = int(current)
			if prev:
				yield prev, current
			prev = current


def main_1():
	times  = 0
	for prev, current in load_data('input.txt'):
		if prev < current:
			times += 1

	print('Sunk {} times'.format(times))


def main_2():
	times = 0
	with open('input.txt', 'r') as input:
		lines = [int(depth) for depth in input.readlines()]
		groups = [(lines[i], lines[i + 1], lines[i + 2]) for i in range(0, len(lines) - 2)]
		
		for group_1, group_2 in zip(groups, groups.copy()[1:]):
			if sum(group_1) < sum(group_2):
				times += 1 

	print('Average sinking times = {}'.format(times))
		

if __name__ == '__main__':
	main_1()
	main_2()