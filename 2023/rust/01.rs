use std::fs::File;
use std::io::{BufRead, BufReader};

fn silver(lines: &Vec<String>) -> i64 {
    let digits: Vec<String> = vec![
        "0".to_string(),
        "1".to_string(),
        "2".to_string(),
        "3".to_string(),
        "4".to_string(),
        "5".to_string(),
        "6".to_string(),
        "7".to_string(),
        "8".to_string(),
        "9".to_string(),
    ];

    let mut ans: i64 = 0;

    for line in lines {
        let (mut first, mut f_val, mut last, mut l_val) = (i64::MAX, 0 as i64, i64::MIN, 0 as i64);

        let mut ptr: i64 = 0;
        for digit in &digits {
            if let Some(f_idx) = line.find(digit) {
                if (f_idx as i64) < first {
                    first = f_idx as i64;
                    f_val = ptr;
                }
            }
            if let Some(l_idx) = line.rfind(digit) {
                if (l_idx as i64) > last {
                    last = l_idx as i64;
                    l_val = ptr;
                }
            }
            ptr += 1;
        }

        ans += (f_val * 10) + l_val;
    }
    return ans;
}

fn gold(lines: &Vec<String>) -> i64 {
    let digits: Vec<String> = vec![
        "0".to_string(),
        "1".to_string(),
        "2".to_string(),
        "3".to_string(),
        "4".to_string(),
        "5".to_string(),
        "6".to_string(),
        "7".to_string(),
        "8".to_string(),
        "9".to_string(),
    ];
    let nums: Vec<String> = vec![
        "zero".to_string(),
        "one".to_string(),
        "two".to_string(),
        "three".to_string(),
        "four".to_string(),
        "five".to_string(),
        "six".to_string(),
        "seven".to_string(),
        "eight".to_string(),
        "nine".to_string(),
    ];

    let mut ans: i64 = 0;
    for line in lines {
        let (mut first, mut f_val, mut last, mut l_val) = (i64::MAX, 0 as i64, i64::MIN, 0 as i64);

        let mut ptr: i64 = 0;
        for digit in &digits {
            if let Some(f_idx) = line.find(digit) {
                if (f_idx as i64) < first {
                    first = f_idx as i64;
                    f_val = ptr;
                }
            }
            if let Some(l_idx) = line.rfind(digit) {
                if (l_idx as i64) > last {
                    last = l_idx as i64;
                    l_val = ptr;
                }
            }
            ptr += 1;
        }

        ptr = 0;
        for num in &nums {
            if let Some(f_idx) = line.find(num) {
                if (f_idx as i64) < first {
                    first = f_idx as i64;
                    f_val = ptr;
                }
            }
            if let Some(l_idx) = line.rfind(num) {
                if (l_idx as i64) > last {
                    last = l_idx as i64;
                    l_val = ptr;
                }
            }
            ptr += 1;
        }

        ans += (f_val * 10) + l_val;
    }
    return ans;
}

fn main() {
    let file_path = "input.txt";

    let fp = File::open(file_path).expect(format!("{} file doesn't exist", file_path).as_str());
    let reader = BufReader::new(fp);

    let mut lines: Vec<String> = Vec::new();

    for line in reader.lines() {
        let line_str = line.unwrap();
        lines.push(line_str);
    }

    println!("{}", silver(&lines));
    println!("{}", gold(&lines));
}
