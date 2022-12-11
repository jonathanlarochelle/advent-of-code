# Advent of code Year 2022 Day 8 Part 2/2 Solution
# Jonathan Larochelle

import time

with open((__file__.rstrip("solution_pt2.py")+"input.txt"), 'r') as input_file:
    input = input_file.read().splitlines()

start_time = time.time()

# Solution starts below


def get_scenic_score(x, y, trees):
    total_score = 1
    height = trees[y][x]

    # Look in row
    from_left = trees[y][:x]
    score = 0
    for t in reversed(from_left):
        score += 1
        if t >= height:
            break
    total_score *= score

    from_right = trees[y][x+1:]
    score = 0
    for t in from_right:
        score += 1
        if t >= height:
            break
    total_score *= score

    # Look in column
    from_above = []
    for yy in range(0, y):
        from_above.append(trees[yy][x])
    score = 0
    for t in reversed(from_above):
        score += 1
        if t >= height:
            break
    total_score *= score

    from_below = []
    for yy in range(y+1, nb_rows):
        from_below.append(trees[yy][x])
    score = 0
    for t in from_below:
        score += 1
        if t >= height:
            break
    total_score *= score

    return total_score


trees = []
for line in input:
    line_as_ints = []
    for t in line:
        line_as_ints.append(int(t))
    trees.append(line_as_ints)

nb_cols = len(trees[0])
nb_rows = len(trees)

top_scenic_score = 0

for y in range(nb_rows):
    for x in range(nb_cols):
        new_score = get_scenic_score(x, y, trees)
        if new_score > top_scenic_score:
            top_scenic_score = new_score


# Solution ends above

end_time = time.time()
print(f"Scenic score: {top_scenic_score}")
print(f"Solved in {(end_time - start_time) * 10**3} ms.")
