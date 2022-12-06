stack = {
    1: ['Q', 'M', 'G', 'C', 'L'],
    2: ['R', 'D', 'L', 'C', 'T', 'F', 'H', 'G'],
    3: ['V', 'J', 'F', 'N', 'M', 'T', 'W', 'R'],
    4: ['J', 'F', 'D', 'V', 'Q', 'P'],
    5: ['N', 'F', 'M', 'S', 'L', 'B', 'T'],
    6: ['R', 'N', 'V', 'H', 'C', 'D', 'P'],
    7: ['H', 'C', 'T'],
    8: ['G', 'S', 'J', 'V', 'Z', 'N', 'H', 'P'],
    9: ['Z', 'F', 'H', 'G']
}

def mv(n, x, y):
    global stack
    t = []
    for _ in range(n):
        t.append(stack[x][-1])
        stack[x].pop()

    while len(t) > 0:
        stack[y].append(t[-1])
        t.pop()

for _ in range(int(input())):
    S = input().split()
    n, x, y = int(S[1]), int(S[3]), int(S[5])
    print(n, x, y)
    mv(n, x, y)
    print(stack)

print(*[v[-1] for k, v in stack.items()], sep='')
