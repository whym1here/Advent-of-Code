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

if sm != 0:
    a.append(sm)

a.sort(reverse=True)
print(sum(a[:3]))
