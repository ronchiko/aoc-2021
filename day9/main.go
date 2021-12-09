package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

type Point struct {
	x int
	y int
}

const ARRAY_OOB = 10

func GetPointOrMax(array [][]int, x int, y int) int {
	if y < 0 || y >= len(array) {
		return ARRAY_OOB
	}

	if x < 0 || x >= len(array[y]) {
		return ARRAY_OOB
	}

	return array[y][x]
}

func IsLowPoint(array [][]int, x int, y int) bool {
	top, bottom := GetPointOrMax(array, x, y-1), GetPointOrMax(array, x, y+1)
	left, right := GetPointOrMax(array, x-1, y), GetPointOrMax(array, x+1, y)

	current := GetPointOrMax(array, x, y)

	return current < top && current < bottom && current < left && current < right
}

func FloodFillBasin(array [][]int, marker []bool, point Point, prev int, w int) int {
	current := GetPointOrMax(array, point.x, point.y)

	if current < 9 && current > prev && !marker[point.y*w+point.x] {
		marker[point.y*w+point.x] = true
		return 1 + FloodFillBasin(array, marker, Point{point.x + 1, point.y}, current, w) +
			FloodFillBasin(array, marker, Point{point.x - 1, point.y}, current, w) +
			FloodFillBasin(array, marker, Point{point.x, point.y + 1}, current, w) +
			FloodFillBasin(array, marker, Point{point.x, point.y - 1}, current, w)
	}

	return 0
}

func main() {

	file, err := os.Open("main.txt")
	if err != nil {
		fmt.Print("Failed to open file\n")
		os.Exit(-1)
	}

	scanner := bufio.NewScanner(file)
	width, height := 0, 0

	var data [][]int

	for scanner.Scan() {
		height++
		line := scanner.Text()
		width = len(line)

		tmp := make([][]int, height)
		copy(tmp, data)
		data = tmp

		data[height-1] = make([]int, width)
		for i, char := range line {
			data[height-1][i] = int(rune(char) - '0')
		}
	}

	sum := 0
	var lowpoints []Point = nil

	// Part 1
	for i := 0; i < height; i++ {
		for j := 0; j < width; j++ {
			if IsLowPoint(data, j, i) {
				sum += int(data[i][j]) + 1
				lowpoints = append(lowpoints, Point{j, i})
			}
		}
	}

	fmt.Printf("The total risk is %d\n", sum)

	// Part 2
	var marker []bool = make([]bool, width*height)
	var basins []int = nil

	for _, point := range lowpoints {
		basins = append(basins, FloodFillBasin(data, marker, point, data[point.y][point.x]-1, width))
	}

	sort.Ints(basins)
	length := len(basins)

	final := basins[length-1] * basins[length-2] * basins[length-3]
	fmt.Printf("The total basin multiplier is %d\n", final)

	file.Close()
}
