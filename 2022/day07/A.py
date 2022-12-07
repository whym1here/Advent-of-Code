fp = open(r'input.txt', 'r')
lines = fp.readlines()
lines = [line.rstrip('\n').split() for line in lines]

print(*lines, sep = '\n')

file_cnt = 0
size_limit = 100000
ans = 0

class Dir:
    def __init__(self, name, prev):
        self.name = name
        self.prev = prev
        self.next = []
        self.map_dir = dict()
        self.map_file = dict()

    def get_size(self):
        global file_cnt, size_limit, ans
        size = 0
        for obj in self.next:
            size += obj.get_size()
        if size <= size_limit: 
            file_cnt += 1
            ans += size
        return size
    
    def add_dir(self, Dir_obj):
        self.map_dir[Dir_obj.name] = len(self.next)
        self.next.append(Dir_obj)
    
    def add_file(self, File_obj):
        self.map_file[File_obj.name] = len(self.next)
        self.next.append(File_obj)
    
    def move_to(self, name):
        return self.next[self.map_dir[name]]

    def move_back(self):
        return self.prev

    def print(self):
        if self.prev == None:
            print("name: {self.name}\nnext: {self.next}")
        else:
            print("name: {self.name}\nprev: {self.prev.name}\nnext: {self.next}")

class File:
    def __init__(self, name, size):
        self.name = name
        self.size = size

    def get_size(self):
        return self.size


base_dir = None
cur_dir = None

for line in lines:
    if line[0] == '$':
        command = line[1] # command type
        if command == 'cd':
            to_dir = line[2] # to dirctory
            if to_dir == '..':
                cur_dir = cur_dir.prev
            else:
                if to_dir == '/':
                    if base_dir == None:
                        base_dir = Dir('/', None)
                    cur_dir = base_dir
                elif to_dir in cur_dir.next:
                    cur_dir = cur_dir.move_to(to_dir)
                else:
                    cur_dir.add_dir(Dir(to_dir, cur_dir))
                    cur_dir = cur_dir.move_to(to_dir)

        if command == 'ls':
            continue

    elif line[0] == 'dir':
        dir_name = line[1]
        if dir_name not in cur_dir.next:
            cur_dir.add_dir(Dir(dir_name, cur_dir))
    else:
        size, file_name = line
        size = int(size)
        if file_name not in cur_dir.map_file:
            cur_dir.add_file(File(file_name, size))


total_size = base_dir.get_size()

print(f"\nno. dir with total size of at most {size_limit},")

print(f"Count: {file_cnt}")
        
print(f"Total size: {ans}")