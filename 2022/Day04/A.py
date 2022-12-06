N = int(input())

def inside(x, y):
    return y[0] <= x[0] and x[1] <= y[1]

ans = 0
for i in range(N):
    s = input().split(',')
    s = [list(map(int, i.split('-'))) for i in s]
    if inside(s[0], s[1]) or inside(s[1], s[0]):
        ans += 1
print(ans)
