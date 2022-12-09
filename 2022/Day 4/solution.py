# Advent of code Year 2022 Day 4 Solution
# Jonathan Larochelle

import time

with open((__file__.rstrip("solution.py")+"input.txt"), 'r') as input_file:
    input = input_file.read()

start_time = time.time()

pairs = input.splitlines()

nb_fully_overlaping = 0

for pair in pairs:
    [elf1_sections, elf2_sections] = pair.split(",")
    [elf1_first_section, elf1_last_section] = elf1_sections.split("-")
    [elf2_first_section, elf2_last_section] = elf2_sections.split("-")

    elf1_first_section = int(elf1_first_section)
    elf1_last_section = int(elf1_last_section)
    elf2_first_section = int(elf2_first_section)
    elf2_last_section = int(elf2_last_section)

    if elf1_first_section <= elf2_last_section <= elf1_last_section:
        nb_fully_overlaping += 1
    elif elf2_first_section <= elf1_last_section <= elf2_last_section:
        nb_fully_overlaping += 1

end_time = time.time()
print(f"Total score: {nb_fully_overlaping}")
print(f"Solved in {(end_time - start_time) * 10**3} ms.")
