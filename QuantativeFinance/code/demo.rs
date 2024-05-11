use std::fs::File;
use std::io::{BufRead, BufReader};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    // 读取历史数据
    let file = File::open("historical_data.csv")?;
    let reader = BufReader::new(file);
    let mut prices: Vec<f64> = Vec::new();

    for line in reader.lines().skip(1) {
        let line = line?;
        let price: f64 = line.trim().parse()?;
        prices.push(price);
    }

    // 计算均值
    let mean_price: f64 = prices.iter().sum::<f64>() / prices.len() as f64;

    // 计算标准差
    let variance: f64 = prices.iter().map(|&x| (x - mean_price).powi(2)).sum::<f64>() / prices.len() as f64;
    let std_dev: f64 = variance.sqrt();

    // 计算当前价格与均值的偏差
    let current_price: f64 = prices.last().cloned().unwrap_or(0.0);
    let deviation = current_price - mean_price;

    // 判断是否交易
    let threshold = 1.0; // 设定阈值
    if deviation > threshold * std_dev {
        println!("Buy signal");
    } else if deviation < -threshold * std_dev {
        println!("Sell signal");
    } else {
        println!("Hold");
    }

    Ok(())
}
