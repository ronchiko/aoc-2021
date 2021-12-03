use std::fs::File;
use std::io::{prelude::*, BufReader};

const LENGTH: usize = 12;

fn bit_spreads(path: String) -> std::io::Result<(Vec<u32>, Vec<u32>)> {
    let file = File::open(path)?; 
    let reader = BufReader::new(file);
    
    let mut count = [0u32; LENGTH];
    let mut total = 0u32;
    
    for line in  reader.lines() {
        let mut num = u32::from_str_radix(&line?, 2).unwrap();

        for i in (0..LENGTH).rev() {
            if num & 0x1 == 0 {
                count[i] += 1;
            }
            num >>= 1;
        }

        total += 1;
    }

    let ones:  Vec<u32> = count.iter().copied().collect();
    let zeros: Vec<u32> = count.iter().map(|x| total - x).collect();

    Ok((ones, zeros))
}

fn count_bits_at_position(v: &Vec<u32>, pos: usize) -> (Vec<u32>, Vec<u32>) {
    let (mut ones, mut zeros) = (Vec::new(), Vec::new());

    for item in v {
        match (item >> pos) & 0x1 {
            1 => ones.push(*item),
            _ => zeros.push(*item)
        }
    }

    (ones, zeros)
}

fn main() -> std::io::Result<()> { 
    // First   
    let (ones, zeros) = bit_spreads(String::from("data.txt"))?;
    let mut gamma = 0u16;

    for (one, zero) in ones.iter().zip(zeros.iter()) {
        gamma <<= 1;
        gamma |= if one < zero { 0 } else { 1 };
    }
    let epsilon = !gamma & 0xFFF;

    println!("Gamma: {}, Epsilon: {}", gamma, epsilon);
    println!("Result: {}", (gamma as u32) * (epsilon as u32));

    // Second
    let file = File::open("data.txt")?; 
    let reader = BufReader::new(file);

    let lines = reader.lines().map(|x| u32::from_str_radix(&x.unwrap(), 2).unwrap());
    
    let mut oxygen: Vec<u32> = lines.collect();
    let mut co2:    Vec<u32> = oxygen.clone();

    for i in (0..LENGTH).rev() {
        if oxygen.len() > 1 {
            let (ones, zeros) = count_bits_at_position(&oxygen, i);
            oxygen = if ones.len() >= zeros.len() { ones } else { zeros };
        }

        if co2.len() > 1 {
            let (ones, zeros) = count_bits_at_position(&co2, i);
            co2 = if ones.len() < zeros.len() { ones } else { zeros };        
        }
    }

    println!("{:0>12b} {:0>12b} = {:?}", oxygen[0], co2[0], oxygen[0] * co2[0]);
    Ok(())
}
