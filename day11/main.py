
def inbound(x, y):
	return 0 <= x < 10 and 0 <= y < 10

def flash(ng, fm, x, y):
	count = 0
	if ng[y][x] > 9 and not fm[y][x]:
		count += 1 
		fm[y][x] = True	
		for (x1, y1) in [(x - 1, y - 1), (x, y), (x + 1, y + 1),
						 (x + 1, y - 1), (x + 1, y), (x - 1, y + 1),
						 (x - 1, y), (x, y + 1), (x, y - 1)]:
			if inbound(x1, y1):
				ng[y1][x1] += 1
				count += flash(ng, fm, x1, y1)

	return count

def sim_step(grid):
	ng = grid = [[x + 1 for x in l] for l in grid]
	flashmap = [[False for _ in range(10)] for  _ in range(10)]

	flashes = sum([flash(ng, flashmap, k % 10, k // 10) for k in range(100)])	

	return [[x if x <= 9 else 0 for x in l] for l in ng], flashes


def sim(f: str, steps: int) -> int:
	with open(f) as file:
		grid = [[c for c in map(lambda x: ord(x) - ord('0'), line) if 0 <= c <= 9] for line in file.readlines()]
		
		count = 0
		for _ in range(steps):
			grid, step_flashes = sim_step(grid)
			count += step_flashes

	return count


def find_sync(f: str) -> int:
	with open(f) as file:
		grid = [[c for c in map(lambda x: ord(x) - ord('0'), line) if 0 <= c <= 9] for line in file.readlines()]
		
		count, step = 0, 0
		while count < 100:
			grid, count = sim_step(grid)
			step += 1

	return step


print(sim("in.txt", 100))
print(find_sync("in.txt"))
