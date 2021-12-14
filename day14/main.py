import re
import copy


def divide_and_build(string, rules, history):
	length = len(string)
	
	if length <= 2:
		return r if (r := rules.get(string)) else string

	if m := history.get(string):
		return m

	left  = divide_and_build(string[:length >> 1], rules, history)
	right = divide_and_build(string[length >> 1:], rules, history)
	result = left + rules.get(f'{left.last}{right.first}', '')[1] + right

	history[string] = result
	return result

with open("main.txt", "r") as file:
	template = file.readline().strip()

	patterns = {}
	for line in file.readlines():
		if match := re.match(r'(\w{2}) -> (\w)', line):
			patterns[match.group(1)] = match.group(2)

	pairs = {}
	for key in patterns:
		pairs[key] = 0

	for a, b in zip(template, template[1:]):
		pairs[f'{a}{b}'] += 1 

	for _ in range(40):
		inserts = copy.deepcopy(pairs)
		for pair, count in inserts.items():
			pairs[pair[0] + patterns[pair]] += count
			pairs[patterns[pair] + pair[1]] += count
			pairs[pair] -= count

	result = {}
	for key in pairs.keys():
		if key[0] not in result.keys():
			result[key[0]] = 0
		if key[1] not in result.keys():
			result[key[1]] = 0
		
		result[key[0]] += pairs[key]/2
		result[key[1]] += pairs[key]/2

	print(.5 + (max(result.values()) - min(result.values())) )
