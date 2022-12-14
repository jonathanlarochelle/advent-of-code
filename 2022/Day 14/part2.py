# Advent of code Year 2022 Day 14 Solution
# Jonathan Larochelle

import time
import numpy as np

def get_input():
    with open("input.txt", 'r') as input_file:
        input = input_file.read()
    return input


def print_array(array):
    print("\n")
    for line in array:
        row = ""
        for el in line:
            row += el.decode("utf-8")
        print(row)


if __name__ == '__main__':
    print(f"Day 14 - Part Two")
    start_time = time.time()
    input = get_input().splitlines()
    nb_units_rested = 0

    # Figure out min and max values for the x axis, y axis
    x_min = 5000
    x_max = 0
    y_max = 0

    rock_paths = []

    for line in input:
        rock_line = []
        for point in line.split(" -> "):
            [x_str, y_str] = point.split(",")
            x = int(x_str)
            y = int(y_str)
            rock_line.append((x, y))
            if x < x_min:
                x_min = x
            if x > x_max:
                x_max = x
            if y > y_max:
                y_max = y
        rock_paths.append(rock_line)
    print(f"x range: {x_min} to {x_max}")
    print(f"y range: 0 to {y_max}")

    # Creating playing field array
    y_length = y_max + 1
    x_length = x_max - x_min + 1
    x_offset = x_min

    infinity = 200  # as long as its high enough ..
    x_length += 2 * infinity
    x_offset -= infinity
    y_length += 2

    cave_wall = np.chararray((y_length, x_length))
    cave_wall[:] = "."

    # Add rock formations
    for path in rock_paths:
        for pair_id in range(len(path) - 1):
            p0 = path[pair_id]
            p1 = path[pair_id + 1]

            if p0[0] <= p1[0] and p0[1] <= p1[1]:
                cave_wall[p0[1]:p1[1] + 1, p0[0] - x_offset:p1[0] - x_offset + 1] = "#"
            else:
                cave_wall[p1[1]:p0[1] + 1, p1[0] - x_offset:p0[0] - x_offset + 1] = "#"
    cave_wall[0, 500 - x_offset] = "+"
    sand_start_col = 500 - x_offset

    # Add floor
    cave_wall[y_max + 2, :] = "#"

    print_array(cave_wall)

    sand_source_blocked = False
    start_position = (sand_start_col, 0)
    while not sand_source_blocked:
        sand_unit_rested = False
        pos = start_position
        while not sand_unit_rested:
            if cave_wall[pos[1] + 1, pos[0]] == b".":
                # Below is free, sand unit falls down
                pos = (pos[0], pos[1] + 1)
            elif cave_wall[pos[1] + 1, pos[0] - 1] == b".":
                # Fall diagonally to bottom left
                pos = (pos[0] - 1, pos[1] + 1)
            elif cave_wall[pos[1] + 1, pos[0] + 1] == b".":
                # Fall diagonally to bottom right
                pos = (pos[0] + 1, pos[1] + 1)
            else:
                # No other position possible, we rest.
                sand_unit_rested = True
                nb_units_rested += 1
                # cave_wall[pos[1], pos[0]] = str(sid)
                cave_wall[pos[1], pos[0]] = b"o"

                if pos == start_position:
                    sand_source_blocked = True
                    break
    print_array(cave_wall)

    end_time = time.time()
    print(f"\t- Solved in {(end_time - start_time) * 10 ** 3}ms.")
    print(f"\t - Output: {nb_units_rested}")