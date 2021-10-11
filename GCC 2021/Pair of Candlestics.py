n = int(input())
p = list(map(int, input().split()))

res = 0
stack = []
for i in p:
    while stack and stack[-1] <= i:
        stack.pop()
        res += 1
    if stack:
        res += 1
    stack.append(i)

print(res)