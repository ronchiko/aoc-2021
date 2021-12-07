use std::str::FromStr;
use std::fs::File;
use std::io::{prelude::* ,BufReader};

fn compute_cost(mut n: i32) -> i32 {	
	let mut m = 0;
	while n > 0 { m += n; n -= 1; }

	m
}

fn sum_fuel(origin: i32, crabs: &Vec<i32>) -> i32 {
	let mut fuel = 0i32;

	for &other in crabs.iter() {
		if origin == other { continue; }
		
		fuel += compute_cost(i32::abs(other - origin));
	} 

	fuel
}

fn main() -> std::io::Result<()> {
	let file = File::open("crabs.txt")?;
	let reader = BufReader::new(file);
	
	let mut crabs: Vec<i32> = vec![];

	for line in reader.lines() {
		crabs = line?.split(",").map(|s| i32::from_str(s).unwrap()).collect();
	}
	
	let limit = match crabs.iter().max() {
		Some(&_limit) => _limit,
		None => -1
	};
	println!("{}", limit);

	let position: Vec<i32> = (1..limit+1).collect();
	let fuels: Vec<(i32, usize)> = position.iter().enumerate().map(|x| (sum_fuel(*x.1, &crabs), x.0)).collect();

	let min = fuels.iter().min();
	match min {
		Some((fuel, index)) => println!("The fuel needed is {:?}, will end up in position {:?}", 
			fuel, position[*index]),
		None =>  println!("Empty list")
	}
	
	
	Ok(())
}