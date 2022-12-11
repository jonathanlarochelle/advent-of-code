# Advent of code Year 2022 Day 11 Solution
# Jonathan Larochelle

import time

class Monkey:
    def __init__(self, monkey_strings):
        self.items = [int(i) for i in monkey_strings[1][18:].split(", ")]

        if "* old" in monkey_strings[2]:
            self.operation = lambda old: old ** 2
        elif "*" in monkey_strings[2]:
            self.operation = lambda old: old * int(monkey_strings[2][25:])
        else:
            self.operation = lambda old: old + int(monkey_strings[2][25:])

        self.throw_to_monkey_map = {True: int(monkey_strings[4][29:]),
                                    False: int(monkey_strings[5][30:])}
        self.throw_to_monkey = lambda worry: self.throw_to_monkey_map[(worry % int(monkey_strings[3][21:])) == 0]

        self.nb_inspections = 0


def get_input():
    with open((__file__.rstrip("solution.py")+"input.txt"), 'r') as input_file:
        input = input_file.read()
    return input


def part_one():
    start_time = time.time()
    input = get_input().split("\n\n")
    nb_monkeys = len(input)
    monkeys_list = [None] * nb_monkeys
    for mid in range(nb_monkeys):
        monkeys_list[mid] = Monkey(input[mid].splitlines())

    for round in range(20):
        for mid in range(nb_monkeys):
            m = monkeys_list[mid]
            for i in range(len(m.items)):
                m.nb_inspections += 1

                worry = m.items[0]
                new_worry = int(m.operation(worry) / 3)
                m.items.pop(0)
                monkeys_list[m.throw_to_monkey(new_worry)].items.append(new_worry)

    # Calculation of nb of inspections per monkey
    nb_inspections_per_monkey = [m.nb_inspections for m in monkeys_list]
    max_nb_inspection = max(nb_inspections_per_monkey)
    nb_inspections_per_monkey.remove(max_nb_inspection)
    monkey_business = max_nb_inspection * max(nb_inspections_per_monkey)

    end_time = time.time()
    print(f"Part One")
    print(f"\t- Solved in {(end_time-start_time) * 10**3}ms.")
    print(f"\t - Output: {monkey_business}")


def part_two():
    start_time = time.time()
    input = get_input().split("\n\n")
    nb_monkeys = len(input)
    monkeys_list = [None] * nb_monkeys
    common_divider = 1
    for mid in range(nb_monkeys):
        monkey_strings = input[mid].splitlines()
        monkeys_list[mid] = Monkey(monkey_strings)
        common_divider *= int(input[mid].splitlines()[3][21:])

    nb_inspections_per_monkey = [0] * nb_monkeys

    for round in range(10000):
        for mid in range(nb_monkeys):
            m = monkeys_list[mid]
            for i in range(len(m.items)):
                nb_inspections_per_monkey[mid] += 1
                worry = m.items[0]
                new_worry = int(m.operation(worry))
                new_worry %= common_divider
                m.items.pop(0)
                monkeys_list[m.throw_to_monkey(new_worry)].items.append(new_worry)
        #print(round)

    # Calculation of nb of inspections per monkey
    max_nb_inspection = max(nb_inspections_per_monkey)
    nb_inspections_per_monkey.remove(max_nb_inspection)
    monkey_business = max_nb_inspection * max(nb_inspections_per_monkey)

    end_time = time.time()
    print(f"Part Two")
    print(f"\t- Solved in {(end_time-start_time) * 10**3}ms.")
    print(f"\t - Output: {monkey_business}")

    #96577
def main():
    part_one()
    part_two()


if __name__ == '__main__':
    main()