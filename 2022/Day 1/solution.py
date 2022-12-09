# Advent of code Year 2022 Day 1 Solution
# Jonathan Larochelle


with open((__file__.rstrip("solution.py")+"input.txt"), 'r') as input_file:
    input = input_file.read()

calories_per_elf_str = input.split("\n\n")
total_calories_per_elf = []

for calories_str in calories_per_elf_str:
    food = calories_str.split("\n")

    calories = 0
    for item in food:
        if item != '':
            calories += int(item)

    total_calories_per_elf.append(calories)

position_1 = max(total_calories_per_elf)
total_calories_per_elf.remove(position_1)
position_2 = max(total_calories_per_elf)
total_calories_per_elf.remove(position_2)
position_3 = max(total_calories_per_elf)

print(position_1+position_2+position_3)