# Advent of code Year 2022 Day 13 Solution
# Jonathan Larochelle

import time


def get_input():
    with open((__file__.rstrip("solution.py")+"input.txt"), 'r') as input_file:
        input = input_file.read()
    return input


def compare_lists(l, r):
    for (el, er) in zip(l, r):
        if isinstance(el, int) and isinstance(er, int):
            # Both are ints
            if el > er:
                #print(f"\n\t\t{el} and {er} FALSE because left > right")
                return False
            elif el < er:
                #print(f"\n\t\t{el} and {er} TRUE because left < right")
                return True
            else:
                # Undecided - check next part of input
                continue
        elif isinstance(el, list) and isinstance(er, list):
            # Both are lists
            ret = compare_lists(el, er)
            if ret is not None:
                return ret
            else:
                # Undecided - check next part of input
                continue
        elif isinstance(el, int) and isinstance(er, list):
            # left is int, right is list
            ret = compare_lists([el], er)
            if ret is not None:
                return ret
            else:
                # Undecided - check next part of input
                continue
        elif isinstance(el, list) and isinstance(er, int):
            # left is list, right is int
            ret = compare_lists(el, [er])
            if ret is not None:
                return ret
            else:
                # Undecided - check next part of input
                continue

    # We made it to the end of a list without a decision, we now compare lengths
    if len(l) < len(r):
        #print(f"\n\t\t{l} and {r} TRUE because left ran out of items first")
        return True
    elif len(l) > len(r):
        #print(f"\n\t\t{l} and {r} FALSE because right ran out of items first")
        return False
    else:
        return None


def part_one():
    start_time = time.time()
    pairs = get_input().split("\n\n")

    sum_pair_indices = 0
    pair_index = 0

    for p in pairs:
        pair_index += 1

        splitted = p.split("\n")
        left = eval(splitted[0])
        right = eval(splitted[1])

        # print(f"Pair {pair_index}")
        # print(f"\t{left}")
        # print(f"\t{right}")

        right_order = compare_lists(left, right)

        if right_order:
            sum_pair_indices += pair_index

    end_time = time.time()
    print(f"Part One")
    print(f"\t- Solved in {(end_time-start_time) * 10**3}ms.")
    print(f"\t - Output: {sum_pair_indices}")


def part_two():
    start_time = time.time()
    input = get_input()
    packets = [eval(x) for x in input.replace("\n\n", "\n").splitlines()]

    decoder_key = 1
    pair_index = 0

    sorted_packets = [packets[0]]
    packets.pop(0)

    for p in packets:
        len_sorted_packets = len(sorted_packets)
        for s in range(len_sorted_packets+1):
            # s is a tentative position for the new packet
            if 0 <= s - 1:
                if not compare_lists(sorted_packets[s - 1], p):
                    continue
            if s < len_sorted_packets:
                if not compare_lists(p, sorted_packets[s]):
                    continue
            # Packet can fit here.
            sorted_packets.insert(s, p)

    for s in range(len(sorted_packets)):
        if sorted_packets[s] in [[[2]], [[6]]]:
            decoder_key *= s + 1

    end_time = time.time()
    print(f"Part Two")
    print(f"\t- Solved in {(end_time - start_time) * 10 ** 3}ms.")
    print(f"\t - Output: {decoder_key}")


def main():
    part_one()
    part_two()


if __name__ == '__main__':
    main()