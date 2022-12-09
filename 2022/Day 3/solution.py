# Advent of code Year 2022 Day 3 Solution
# Jonathan Larochelle

import time

with open((__file__.rstrip("solution.py")+"input.txt"), 'r') as input_file:
    input = input_file.read()

start_time = time.time()

rucksacks = input.splitlines()
priorities_sum = 0

# Instead of mapping each letter to a score, we obtain the decimal ASCII code for the letter with ord('a') and then we
# apply an offset based on the obtained value.
letter_offset = 96
capital_letter_offset = 38
threshold = 91

nb_rucksacks = len(rucksacks)

for i in range(int(nb_rucksacks/3)):
    rucksack1 = rucksacks[i*3]
    rucksack2 = rucksacks[i*3+1]
    rucksack3 = rucksacks[i*3+2]

    common_item = "wrong"
    for item in rucksack1:
        if (item in rucksack2) and (item in rucksack3):
            common_item = item
            break

    letter_code = ord(common_item)
    item_priority = 0
    if letter_code < threshold:
        item_priority = letter_code - capital_letter_offset
    else:
        item_priority = letter_code - letter_offset
    print(f"{common_item}")
    priorities_sum += item_priority

end_time = time.time()
print(f"Total score: {priorities_sum}")
print(f"Solved in {(end_time - start_time) * 10**3} ms.")
