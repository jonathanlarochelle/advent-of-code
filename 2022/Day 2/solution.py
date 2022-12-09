# Advent of code Year 2022 Day 2 Solution
# Jonathan Larochelle

import time

with open((__file__.rstrip("solution.py")+"input.txt"), 'r') as input_file:
    input = input_file.read()

start_time = time.time()

outcome_map = {"A X": "C",
               "A Y": "A",
               "A Z": "B",
               "B X": "A",
               "B Y": "B",
               "B Z": "C",
               "C X": "B",
               "C Y": "C",
               "C Z": "A"}

shape_selected_score = {"A": 1,
                        "B": 2,
                        "C": 3}

outcome_score = {"X": 0,
                 "Y": 3,
                 "Z": 6}

rounds = input.splitlines()

score = 0
for r in rounds:
    score += shape_selected_score[outcome_map[r]]
    score += outcome_score[r[2]]

end_time = time.time()
print(f"Total score: {score}")
print(f"Solved in {(end_time - start_time) * 10**3} ms.")
