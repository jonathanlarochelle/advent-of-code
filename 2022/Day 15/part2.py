# Advent of code Year 2022 Day 15 Part 2 Solution
# Jonathan Larochelle

import time
import re


def get_input():
    with open("input.txt", 'r') as input_file:
        input = input_file.read()
    return input


def is_in_range(sensor, manhattan, point_to_check):
    if abs(sensor[0] - point_to_check[0]) + abs(sensor[1] - point_to_check[1]) <= manhattan:
        return True
    else:
        return False


if __name__ == '__main__':
    print(f"Day 15 - Part Two")
    start_time = time.time()
    input = get_input().splitlines()

    tuning_frequency = 0
    sensors_list = []

    for line in input:
        res = re.match(r"Sensor at x=(-?\d*), y=(-?\d*): closest beacon is at x=(-?\d*), y=(-?\d*)", line)
        sens_x = int(res.group(1))
        sens_y = int(res.group(2))
        manhattan = abs(sens_x - int(res.group(3))) + abs(sens_y - int(res.group(4)))

        sensors_list.append([(sens_x, sens_y), manhattan])

    # We have to be bright, else it takes forever.
    # Can't look at 4 000 000 * 4 000 000 points

    end_time = time.time()
    print(f"\t- Solved in {(end_time - start_time) * 10 ** 3}ms.")
    print(f"\t - Output: {tuning_frequency}")