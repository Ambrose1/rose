class Solution:
    def distributeCandies(self, candies: int, num_people: int) -> List[int]:
        p = int((2 * candies + 0.25) ** 0.5 - 0.5)
        rem = int(candies - p *(p+1)*0.5)
        row,col = p // num_people, p % num_people

        d = [0] * num_people
        for i in range(num_people):
            d[i] = (i+1) * row + int(row * (row - 1) * 0.5 * num_people)
            if i < col:
                d[i] += i + 1 + row *num_people
        d[col] += rem
        return d
