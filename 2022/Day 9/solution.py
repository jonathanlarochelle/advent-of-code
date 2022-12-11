# Advent of code Year 2022 Day 9 Solution
# Jonathan Larochelle

import time


def get_input():
    with open((__file__.rstrip("solution.py")+"input.txt"), 'r') as input_file:
        input = input_file.read().splitlines()
    return input





def part_one():
    def move_head(head_coords, direction):
        if direction == "U":
            new_coords = (head_coords[0], head_coords[1] + 1)
        elif direction == "D":
            new_coords = (head_coords[0], head_coords[1] - 1)
        elif direction == "L":
            new_coords = (head_coords[0] - 1, head_coords[1])
        else:
            new_coords = (head_coords[0] + 1, head_coords[1])
        return new_coords

    def move_tail(tail_coords, head_coords):
        x_diff = head_coords[0] - tail_coords[0]
        y_diff = head_coords[1] - tail_coords[1]

        if (abs(x_diff) <= 1) and (abs(y_diff) <= 1):
            # Tail and head are touching, we don't move.
            return tail_coords

        if abs(x_diff) == 2 and y_diff == 0:
            # Move 1 in x direction
            return tail_coords[0] + int(x_diff/2), tail_coords[1]

        if abs(y_diff) == 2 and x_diff == 0:
            # Move 1 in y direction
            return (tail_coords[0], tail_coords[1] + int(y_diff/2))

        # Diagonal move - Move 1 in both directions
        if x_diff > 0:
            new_x = tail_coords[0] + 1
        else:
            new_x = tail_coords[0] - 1
        if y_diff > 0:
            new_y = tail_coords[1] + 1
        else:
            new_y = tail_coords[1] - 1
        return new_x, new_y

    start_time = time.time()
    input = get_input()
    head_coords = (0, 0)
    tail_coords = head_coords

    positions_visited = []
    nb_positions_visited_once = 0

    for instruction in input:
        direction = instruction[0]
        nb_moves = int(instruction[2:])

        for _ in range(nb_moves):
            head_coords = move_head(head_coords, direction)
            tail_coords = move_tail(tail_coords, head_coords)
            if tail_coords not in positions_visited:
                positions_visited.append(tail_coords)
                nb_positions_visited_once += 1

    end_time = time.time()
    return nb_positions_visited_once, (end_time-start_time)


def part_two():
    def move_head(head_coords, direction):
        if direction == "U":
            new_coords = (head_coords[0], head_coords[1] + 1)
        elif direction == "D":
            new_coords = (head_coords[0], head_coords[1] - 1)
        elif direction == "L":
            new_coords = (head_coords[0] - 1, head_coords[1])
        else:
            new_coords = (head_coords[0] + 1, head_coords[1])
        return new_coords

    def move_knot(tail_coords, head_coords):
        x_diff = head_coords[0] - tail_coords[0]
        y_diff = head_coords[1] - tail_coords[1]

        if (abs(x_diff) <= 1) and (abs(y_diff) <= 1):
            # Tail and head are touching, we don't move.
            return tail_coords

        if abs(x_diff) == 2 and y_diff == 0:
            # Move 1 in x direction
            return tail_coords[0] + int(x_diff / 2), tail_coords[1]

        if abs(y_diff) == 2 and x_diff == 0:
            # Move 1 in y direction
            return (tail_coords[0], tail_coords[1] + int(y_diff / 2))

        # Diagonal move - Move 1 in both directions
        if x_diff > 0:
            new_x = tail_coords[0] + 1
        else:
            new_x = tail_coords[0] - 1
        if y_diff > 0:
            new_y = tail_coords[1] + 1
        else:
            new_y = tail_coords[1] - 1
        return new_x, new_y

    start_time = time.time()
    input = get_input()
    nb_knots = 9
    knots = [(0, 0) for _ in range(nb_knots+1)]

    positions_visited = []
    nb_positions_visited_once = 0

    for instruction in input:
        direction = instruction[0]
        nb_moves = int(instruction[2:])

        for _ in range(nb_moves):
            knots[0] = move_head(knots[0], direction)
            for k in range(1, nb_knots+1):
                knots[k] = move_knot(knots[k], knots[k-1])
            if knots[-1] not in positions_visited:
                positions_visited.append(knots[-1])
                nb_positions_visited_once += 1

    end_time = time.time()
    return nb_positions_visited_once, (end_time - start_time)


def main():
    print(f"Part One: {part_one()}")
    print(f"Part Two: {part_two()}")


if __name__ == '__main__':
    main()