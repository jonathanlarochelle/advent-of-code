# Advent of code Year 2022 Day 5 Solution
# Jonathan Larochelle

import time
import re

with open((__file__.rstrip("solution.py")+"input.txt"), 'r') as input_file:
    input = input_file.read()

start_time = time.time()

# Solution starts below
[starting_stacks, rearrangement_procedure] = input.split("\n\n")
starting_stacks = starting_stacks.split("\n")
starting_stacks.pop()

# Convert each stack to a list of crates
nb_stacks = int(len(starting_stacks[-1]) / 3)
stacks = []
for i in range(nb_stacks):
    col = i*4+1
    stack = []
    for line in reversed(starting_stacks):
        try:
            if line[col] == " ":
                break
        except IndexError:
            break
        stack.append(line[col])
    stacks.append(stack)

# Execute rearrangement procedures
for step in rearrangement_procedure.split("\n"):
    [[nb_to_move, from_stack, to_stack]] = re.findall(r"move (\d+) from (\d+) to (\d+)", step)

    crates = stacks[int(from_stack)-1][(-int(nb_to_move)):]
    stacks[int(to_stack)-1] += crates

    for c in range(int(nb_to_move)):
        stacks[int(from_stack)-1].pop(-1)

# Get top of each stack
top_crates = ""
for s in stacks:
    try:
        top_crates += s[-1]
    except IndexError:
        pass


# Solution ends above

end_time = time.time()
print(f"Total score: {top_crates}")
print(f"Solved in {(end_time - start_time) * 10**3} ms.")
