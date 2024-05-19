import akshare as ak
# 获取 A 股日线数据
stock_zh_a_hist_df = ak.stock_zh_a_hist(symbol="600519", period="daily", start_date="20230101", end_date="20231231")
print(stock_zh_a_hist_df)