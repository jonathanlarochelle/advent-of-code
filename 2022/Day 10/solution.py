# Advent of code Year 2022 Day 10 Solution
# Jonathan Larochelle

import time


def get_input():
    with open((__file__.rstrip("solution.py")+"input.txt"), 'r') as input_file:
        input = input_file.read().splitlines()
    return input


def part_one():
    start_time = time.time()
    input = get_input()
    cycle_counter = 0
    register_x = 1
    signal_strength = 0

    line_count = 0
    for line in input:
        line_count += 1
        if line[0:4] == "noop":
            cycle_counter += 1
            if (cycle_counter + 20) % 40 == 0:
                new_ss = cycle_counter * register_x
                signal_strength += cycle_counter * register_x
        elif line[0:4] == "addx":
            cycle_counter += 1
            if (cycle_counter + 20) % 40 == 0:
                new_ss = cycle_counter * register_x
                signal_strength += cycle_counter * register_x
            cycle_counter += 1
            if (cycle_counter + 20) % 40 == 0:
                new_ss = cycle_counter * register_x
                signal_strength += cycle_counter * register_x
            register_x += int(line[5:])

        # print(f"{cycle_counter} : {register_x}")

    end_time = time.time()
    return signal_strength, (end_time-start_time)


def part_two():
    def get_pixel(regx, cycle):
        x_pos_crt = (cycle % 40) - 1
        if regx - 1 <= x_pos_crt <= regx + 1:
            ret = "#"
        else:
            ret = "."

        if cycle % 40 == 0:
            ret += "\n"

        return ret

    start_time = time.time()
    input = get_input()
    cycle_counter = 0
    register_x = 1
    signal_strength = 0

    line_count = 0

    pixels = ""
    for line in input:
        line_count += 1
        if line[0:4] == "noop":
            cycle_counter += 1
            pixels += get_pixel(register_x, cycle_counter)
        elif line[0:4] == "addx":
            cycle_counter += 1
            pixels += get_pixel(register_x, cycle_counter)
            cycle_counter += 1
            pixels += get_pixel(register_x, cycle_counter)
            register_x += int(line[5:])

    # Add line breaks

    end_time = time.time()
    return pixels, (end_time - start_time)


def main():
    print(f"Part One: {part_one()}")
    print(part_two()[0])
    #print(f"Part Two: {part_two()}")


if __name__ == '__main__':
    main()