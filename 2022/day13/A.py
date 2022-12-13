L = []
n = 0

fp = open('input.txt', 'r')
lines = fp.readlines()
lines = [line.strip('\n').strip() for line in lines]

N = len(lines) 
for i in range(0, N, 3):
  L1 = eval(lines[i])
  L2 = eval(lines[i + 1])
  dump = lines[i + 2]
  L.append([L1, L2])

# print(*L, sep='\n')

def check(left, right):
  int_left, int_right = isinstance(left, int), isinstance(right, int)
  # print(f'left = {left}, right = {right}')
  if int_left and int_right:
    if left < right:
        return 1
    elif left == right:
        return 0
    else:
        return -1
  if not int_left and not int_right:
    for i in range(min(len(left), len(right))):
      l, r = left[i], right[i]
      v = check(l, r) 
      if v in [1, -1]:
        return v
    return check(len(left), len(right))
  if not int_left and int_right:
    l = left
    r = [right]
    return check(l, r)
  if int_left and not int_right:
    r = right
    l = [left]
    return check(l, r)
  assert False

ans, i = 0, 1
for (L1, L2) in L:
  # print(i)
  if check(L1, L2) == 1:
    ans += i
  i += 1
  
print(ans)
