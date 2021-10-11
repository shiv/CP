mod = 1000000007

b, c = map(int, input().split())
mat = [[0 for _ in range(b + 1)] for _ in range(c)]
for i in range(0, c):
    temp = list(map(int, input().split()))
    for j in range(1, b + 1):
        mat[i][j] = temp[j - 1]
        mat[i][j] += mat[i][j - 1]

res = mod
dp = [[mod for _ in range(b + 1)] for _ in range(1 << c)]

def  countSetBits(n):
    count = 0
    while (n):
        count += n & 1
        n >>= 1
    return count

for i in range (1, 1 << c):

    if (countSetBits(i) == 1):
        l = (i & -i).bit_length() - 1
        for k in range(b + 1):
            dp[i][k] = mat[l][k]

    for j in range(c):
        if ((i & (1 << j)) == 0):
            for k in range(1, b + 1):
                for l in range(k, b + 1):
                    temp = dp[i][k - 1] - mat[j][k - 1] + mat[j][l]
                    idx = i | 1 << j
                    dp[idx][l] = min(dp[idx][l], temp)

    res = min(res, dp[i][b])

print(res)