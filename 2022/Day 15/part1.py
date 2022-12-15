# Advent of code Year 2022 Day 15 Part 1 Solution
# Jonathan Larochelle

import time
import re


def get_input():
    with open("input.txt", 'r') as input_file:
        input = input_file.read()
    return input


if __name__ == '__main__':
    print(f"Day 15 - Part One")
    start_time = time.time()
    input = get_input().splitlines()

    target_row_id = 2000000
    nb_positions_without_sensor = 0

    sensors_list = []
    beacons_list = []

    min_x = None
    max_x = None

    for line in input:
        res = re.match(r"Sensor at x=(-?\d*), y=(-?\d*): closest beacon is at x=(-?\d*), y=(-?\d*)", line)
        sens_x = int(res.group(1))
        sens_y = int(res.group(2))
        manhattan = abs(sens_x - int(res.group(3))) + abs(sens_y - int(res.group(4)))

        if int(res.group(4)) == target_row_id:
            beacons_list.append(int(res.group(3)))

        if sens_y - manhattan <= target_row_id <= sens_y + manhattan:
            if (max_x is None) and (min_x is None):
                max_x = sens_x + manhattan
                min_x = sens_x - manhattan
            else:
                if sens_x - manhattan < min_x:
                    min_x = sens_x - manhattan
                if sens_x + manhattan > max_x:
                    max_x = sens_x + manhattan
            sensors_list.append([(sens_x, sens_y), manhattan])

    target_row_profile = []
    for x in range(max_x - min_x):
        target_row_profile.append(".")

    for b in beacons_list:
        target_row_profile[b - min_x] = "B"

    for s in sensors_list:
        diff_y = abs(s[0][1] - target_row_id)
        center_pos = s[0][0]
        start = center_pos - (s[1] - diff_y)
        stop = center_pos + (s[1] - diff_y)
        for i in range(start, stop + 1):
            if target_row_profile[i - min_x] == ".":
                nb_positions_without_sensor += 1
                target_row_profile[i - min_x] = "#"

    end_time = time.time()
    print(f"\t- Solved in {(end_time - start_time) * 10 ** 3}ms.")
    print(f"\t - Output: {nb_positions_without_sensor}")