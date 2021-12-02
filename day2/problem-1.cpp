
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

struct Submarine {
public:
	int depth;
	int x;
	int aim;
};


int main() {
	Submarine origin = {0, 0, 0};

	std::fstream stream("course.txt", std::ios_base::in);
	for(std::string command; std::getline(stream, command);) {
		std::stringstream ss; ss.str(command);

		std::string instruction;
		int amount;
		ss >> instruction >> amount;

		switch(instruction[0]) {
			case 'd': origin.aim += amount; break;
			case 'u': origin.aim -= amount; break;
			case 'f': origin.x += amount; origin.depth += amount * origin.aim; break;
		}
	}

	stream.close();

	std::cout << "Final cooridnate is " << origin.depth << "m deep and " << origin.x << "m forward\n";
	std::cout << "Your final aim is " << origin.aim << "\n";
	std::cout << "The multiplication of them is " << origin.depth * origin.x << "\n";

	return 0;
}