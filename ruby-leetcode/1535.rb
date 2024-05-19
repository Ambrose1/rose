# @param {Integer[]} arr
# @param {Integer} k
# @return {Integer}
def get_winner(arr, k)
  n = arr.size();
  currk, currMax = 0, arr[0];
  for i in 1..n-1
      if currk == k
          return currMax
      end
      if currMax > arr[i]
          currk += 1;
      else
          currk = 1;
          currMax = arr[i];
      end
  end
  currMax
end
