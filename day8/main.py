N2A = {2: 1, 4: 4, 3: 7, 7: 8}

with open("in.txt", mode='r') as file:
	results = []
	for line in file.readlines():
		elements = line.strip().split(' ')
		
		options = [None for _ in range(10)]

		for digit in filter(lambda x: len(x) in [2, 3, 4, 7], elements[:10]):
			options[N2A[len(digit)]] = set(digit)

		for digit in (set(x) for x in elements if len(x) == 6):
			if len(digit.difference(options[1])) == 5:
				options[6] = digit
			elif digit.issuperset(options[4]):
				options[9] = digit
			else:
				options[0] = digit

		for digit in (set(x) for x in elements if len(x) == 5):
			if len(digit.difference(options[4])) == 3:
				options[2] = digit
			elif digit.issuperset(options[1]):
				options[3] = digit 
			else:
				options[5] = digit

		d2n, number = dict(map(lambda u: (str(sorted(u[1])), u[0]), enumerate(options))), 0
		[number := number * 10 + d2n[elem] for elem in map(lambda e: str(sorted(e)), elements[11:])]
		results.append(number)

print("The final result is {}".format(sum(results)))