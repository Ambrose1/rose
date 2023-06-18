use std;

const MOD: i64 = 1_000_000_007;

fn is_prime(n: i32) -> bool {
    if n < 2 {
        return false;
    }
    let mut i = 2;
    while i * i <= n {
        if n % i == 0 {
            return false;
        }
        i += 1;
    }
    true
}

fn factoral(n: i32) -> i64 {
    let mut f = 1;
    for i in 1..=n {
        f = (f * i as i64) % MOD
    }
    f
}

fn num_prime_arrangements(n: i32) -> i32 {
    let mut num = 0;
    for i in 2..=n {
        if is_prime(i) {
            num += 1;
        }
    }

    let num_factorial = factoral(num);
    let num_prime_factorial = factoral(n - num);
    ((num_prime_factorial * num_factorial) % MOD) as i32
}

fn main() {
    let n = 10;
    let result = num_prime_arrangements(n);
    println!(
        "The number of prime arrangements for n = {} is {}",
        n, result
    );
}
