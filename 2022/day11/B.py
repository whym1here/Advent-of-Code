import pprint
from collections import deque
import math

fp = open(r'input.txt', 'r')
lines = fp.readlines()
lines = [line.rstrip('\n').strip(' ').split(' ') for line in lines]

monkey = dict()
order = []
cur = None

p = []

for line in lines:
    # print(line)
    if line[0] == '':
        continue
    elif line[0] == 'Monkey':
        monkey[int(line[1][: -1])] = dict()
        cur = int(line[1][: -1])
        order.append(cur)
    elif line[0] == 'Starting':
        monkey[cur][line[1][: -1]] = deque(list(map(lambda a : int(a.strip(',')), line[2:])))
    elif line[0][: -1] == 'Operation':        
        monkey[cur][line[0][: -1]] = line[3:]
    elif line[0][: - 1] == 'Test':
        monkey[cur][line[0][: -1]] = int(line[3]) 
        p.append(int(line[3]))
    elif line[1][: -1] == 'true':
        monkey[cur][True] = int(line[5])
    elif line[1][: -1] == 'false':
        monkey[cur][False] = int(line[5])

pprint.pprint(monkey)

mod = 0
m = 1
for e in p:
    m *= e
    mod = math.gcd(mod, e)
mod = m // mod
print(p)

print(mod)

def new(x, S):
    if S[0] == 'old' and S[1] == '*':
        if S[2] != 'old':
            return (x * int(S[2])) % mod
        else:
            return (x * x) % mod
    elif S[0] == 'old' and S[1] == '+':
        if S[2] != 'old':
            return (x + int(S[2])) % mod
        else:
            return (x + x) % mod

def test(x, num):
    return x % num == 0

# print(lines, sep='\n')
# pprint.pprint(monkey)
cnt = [0 for i in range(len(order))]


def round(i):
    global monkey, cnt
    while len(monkey[i]['items']) > 0:
        worry = monkey[i]['items'].popleft()
        worry = new(worry, monkey[i]['Operation']) 
        nxt = monkey[i][test(worry, monkey[i]['Test'])]
        monkey[nxt]['items'].append(worry)
        cnt[i] += 1

order.sort()
R = 10000
for r in range(R):
    #print(f"Round: {r}")
    #pprint.pprint(monkey)
    #print(cnt);
    for i in order:
        round(i)

# pprint.pprint(monkey)
print(cnt)
cnt.sort()
print(cnt[-1] * cnt[-2])

