# Advent of code Year 2022 Day 6 Solution
# Jonathan Larochelle

import time

with open((__file__.rstrip("solution.py")+"input.txt"), 'r') as input_file:
    input = input_file.read()

start_time = time.time()

# Solution starts below
for pos in range(13, len(input)):
    letter_found = False
    for letter in input[pos-13:pos+1]:
        if input[pos-13:pos+1].count(letter) > 1:
            letter_found = True
            break
    if not letter_found:
        break
# Solution ends above

end_time = time.time()
print(f"Position: {pos+1}")
print(f"Solved in {(end_time - start_time) * 10**3} ms.")
