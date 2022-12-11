# Advent of code Year 2022 Day 7 Solution
# Jonathan Larochelle

import time

with open((__file__.rstrip("solution.py")+"input.txt"), 'r') as input_file:
    input = input_file.read().splitlines()

start_time = time.time()

# WE WANT: Sum of size of directories with size of at most 100000.
# Solution starts below


class Directory:
    def __init__(self, name):
        self.parent = None
        self.name = name
        self.children = {}

    def add_child(self, new_child):
        self.children[new_child.name] = new_child
        new_child.parent = self

    def get_child(self, name):
        return self.children[name]

    def get_size(self):
        total_size = 0
        for c in self.children.values():
            total_size += c.get_size()
        return total_size


class File:
    def __init__(self, name, size):
        self.name = name
        self.size = size
        self.parent = None

    def get_size(self):
        return self.size


directories = []
root = Directory("/")
directories.append(root)

for line in input:
    if line[0:4] == "$ cd":
        # Move to new directory
        if line[5] == "/":
            current_directory = root
        elif line[5:7] == "..":
            current_directory = current_directory.parent
        else:
            current_directory = current_directory.get_child(line[5:])
    elif line[0:4] != "$ ls":
        if line[0:3] == "dir":
            # Directory
            new_dir = Directory(line[4:])
            directories.append(new_dir)
            current_directory.add_child(new_dir)
        else:
            # File
            [size, name] = line.split(" ")
            current_directory.add_child(File(name, int(size)))

# Part 1 - Sum size of directories with size at most 100000
total_size = 0
for d in directories:
    size = d.get_size()
    if size <= 100000:
        total_size += size

# Part2 - Smallest directory to delete that frees up enough space
total_space = 70000000
free_space_required = 30000000
current_free_space = total_space - root.get_size()
current_space_required = free_space_required - current_free_space

dir_to_delete = root
dir_to_delete_space_saved = root.get_size()
print(f"Need {current_space_required}")
for d in directories:
    size = d.get_size()

    if current_space_required <= size < dir_to_delete_space_saved:
        dir_to_delete = d
        dir_to_delete_space_saved = size

# Solution ends above

end_time = time.time()
print(f"Directory to delete: {dir_to_delete.name} with {dir_to_delete.get_size()}")
print(f"Solved in {(end_time - start_time) * 10**3} ms.")
