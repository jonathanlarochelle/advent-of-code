# Advent of code Year 2022 Day 8 Part 1/2 Solution
# Jonathan Larochelle

import time

with open((__file__.rstrip("solution_pt1.py")+"input.txt"), 'r') as input_file:
    input = input_file.read().splitlines()

start_time = time.time()

# Solution starts below


def is_tree_visible(x, y, trees):
    height = trees[y][x]
    if (x == 0) or (x == nb_cols-1) or (y == 0) or (y == nb_rows-1):
        return True

    # Look in row
    from_left = trees[y][:x]
    if max(from_left) < height:
        return True
    from_right = trees[y][x+1:]
    if max(from_right) < height:
        return True

    # Look in column
    from_above = []
    for yy in range(0, y):
        from_above.append(trees[yy][x])
    if max(from_above) < height:
        return True

    from_below = []
    for yy in range(y+1, nb_rows):
        from_below.append(trees[yy][x])
    if max(from_below) < height:
        return True

    return False


trees = []
for line in input:
    line_as_ints = []
    for t in line:
        line_as_ints.append(int(t))
    trees.append(line_as_ints)

nb_cols = len(trees[0])
nb_rows = len(trees)

visibility_matrix = []
visible_count = 0

for y in range(nb_rows):
    visibility_matrix.append([])
    for x in range(nb_cols):
        visibility_matrix[y].append(is_tree_visible(x, y, trees))
        if visibility_matrix[y][-1]:
            visible_count += 1


# Solution ends above

end_time = time.time()
print(f"Number of visible trees: {visible_count}")
print(f"Solved in {(end_time - start_time) * 10**3} ms.")
