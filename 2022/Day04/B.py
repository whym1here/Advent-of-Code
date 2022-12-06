N = int(input())

def overlap(x, y):
    return not (x[1] < y[0] or y[1] < x[0])

ans = 0
for i in range(N):
    s = input().split(',')
    s = [list(map(int, i.split('-'))) for i in s]
    if overlap(s[0], s[1]):
        ans += 1
print(ans)
