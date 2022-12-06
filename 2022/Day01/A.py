N = int(input())
a = []
sm = 0

for _ in range(N):
    s = input()
    if s == '':
        a.append(sm)
        sm = 0
    else:
        sm += int(s)

print(max(a))
