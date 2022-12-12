# Advent of code Year 2022 Day 12 Solution
# Jonathan Larochelle

import time
import copy


def get_input():
    with open((__file__.rstrip("solution.py")+"input.txt"), 'r') as input_file:
        input = input_file.read()
    return input

nb_step_good_paths = []


def part_one():
    start_time = time.time()
    input = get_input().splitlines()

    nb_rows = len(input)
    nb_cols = len(input[0])


    elevation = []

    for y in range(nb_rows):
        row = []
        for x in range(nb_cols):
            if input[y][x] == "S":
                start_x = x
                start_y = y
                row.append(ord("a"))
            elif input[y][x] == "E":
                end_x = x
                end_y = y
                row.append(ord("z"))
            else:
                row.append(ord(input[y][x]))
        elevation.append(row)

    minimum_nb_steps = None

    class Step:
        def __init__(self, parent, x0, y0):
            self.x0 = x0
            self.y0 = y0
            if parent:
                self.step_nb = parent.step_nb + 1
            else:
                self.step_nb = 0
            self.children = []
            self.parent = parent

            print(f"{self.x0}, {self.y0}, {elevation[self.y0][self.x0]}")

            if self.step_nb < 200:
                if (x0 == end_x) and (y0 == end_y):
                    print(f"Success in {self.step_nb} steps!")
                    nb_step_good_paths.append(self.step_nb)
                else:
                    self.move(x0 + 1, y0)
                    self.move(x0, y0 - 1)
                    self.move(x0, y0 + 1)
                    self.move(x0 - 1, y0)


        def move(self, x1, y1):
            if elevation[y1][x1] != 97:
                if not self.is_in_history(x1, y1):
                    if 0 <= x1 < nb_cols and 0 <= y1 < nb_rows:
                        if 0 <= elevation[y1][x1] - elevation[self.y0][self.x0] <= 1:
                            self.children.append(Step(self, x1, y1))

        def is_in_history(self, x, y):
            if (x == self.x0) and (y == self.y0):
                return True
            else:
                if self.parent:
                    return self.parent.is_in_history(x, y)
                else:
                    return False

    first_step = Step(None, start_x, start_y)

    end_time = time.time()
    print(f"Part One")
    print(f"\t- Solved in {(end_time-start_time) * 10**3}ms.")
    print(f"\t - Output: {min(nb_step_good_paths)}")


def part_two():
    start_time = time.time()
    input = get_input().split("\n\n")


    end_time = time.time()
    print(f"Part Two")
    print(f"\t- Solved in {(end_time-start_time) * 10**3}ms.")
    print(f"\t - Output: {monkey_business}")

    #96577
def main():
    part_one()
    #part_two()


if __name__ == '__main__':
    main()