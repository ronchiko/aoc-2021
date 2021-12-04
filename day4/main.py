
def parse_input():
	with open('bingo.txt', 'r') as file:
		pulling = file.readline()
		boards = []

		while line := file.readline():
			board = []
			for _ in range(5):
				line = file.readline()
				board.extend([int(num) for num in line.split(' ') if num])

			boards.append(board)

		return boards, [int(num) for num in pulling.split(',')]


def is_bingo(board: list, insert):
	if insert not in board:
		return False, 0
	
	while insert in board:
		board[board.index(insert)] = (insert,)

	outs = [num for (num, mrk) in filter(lambda a: isinstance(a[1], tuple), enumerate(board))]
	unmarked_sum = sum(filter(lambda a: not isinstance(a, tuple), board))

	# Vertical
	for k in range(5):
		if len(list(filter(lambda i: i % 5 == k, outs))) == 5:
			return True, unmarked_sum * insert
	
	# Horizontal
	for i in map(lambda i: outs.index(i), filter(lambda i: i % 5 == 0, outs)):
		if i + 5 <= len(outs) and sum(outs[i: i + 5]) - outs[i] * 5 == 10:
			return True, unmarked_sum * insert

	return False, 0


def problem_1():
	boards, pulling = parse_input()

	final = None
	for num in pulling:
		for i, board in enumerate(boards):
			bingo, _sum = is_bingo(board, num)
			if bingo:
				if not final:
					print("First winner is #{} with sum of {}".format(i, _sum))
				final = (i, _sum)
				boards[i] = []

	print("Final board to win is #{} with score of {}".format(final[0], final[1]))

if __name__ == '__main__':
	problem_1()