# Advent of code Year 2022 Day 12 Solution
# Jonathan Larochelle

import time
import os
os.environ["TERM"] = "xterm"

def get_input():
    with open((__file__.rstrip("solution.py")+"input.txt"), 'r') as input_file:
        input = input_file.read()
    return input


def part_one():
    start_time = time.time()
    input = get_input().splitlines()

    nb_rows = len(input)
    nb_cols = len(input[0])

    node_scores = []
    elevation = []
    unvisited_nodes = []

    # Convert letters to elevation values from 1 to 26
    for y in range(nb_rows):
        ns_row = []
        e_row = []
        for x in range(nb_cols):
            if input[y][x] == "S":
                e_row.append(1)
                ns_row.append(0)
            elif input[y][x] == "E":
                end = (x, y)
                e_row.append(26)
                ns_row.append(-1)
            else:
                e_row.append(ord(input[y][x]) - 96)
                ns_row.append(-1)
            unvisited_nodes.append((x, y))
        node_scores.append(ns_row)
        elevation.append(e_row)

    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]

    while len(unvisited_nodes) > 1 and node_scores[end[1]][end[0]] == -1:
        # Focus on unvisited node with lower score
        node = None
        for un in unvisited_nodes:
            if node_scores[un[1]][un[0]] != -1:
                if not node:
                    node = un
                elif node_scores[un[1]][un[0]] < node_scores[node[1]][node[0]]:
                    node = un

        # Look at four directions
        for d in directions:
            next = (node[0] + d[0], node[1] + d[1])
            if next in unvisited_nodes:
                if elevation[next[1]][next[0]] - 1 <= elevation[node[1]][node[0]]:
                    # We can access the next node

                    if node_scores[next[1]][next[0]] == -1:
                        node_scores[next[1]][next[0]] = node_scores[node[1]][node[0]] + 1
                    elif node_scores[node[1]][node[0]] + 1 < node_scores[next[1]][next[0]]:
                        node_scores[next[1]][next[0]] = node_scores[node[1]][node[0]] + 1

        # Node is visited
        unvisited_nodes.remove(node)

        # Progress
        print(len(unvisited_nodes))

    end_time = time.time()
    print(f"Part One")
    print(f"\t- Solved in {(end_time-start_time) * 10**3}ms.")
    print(f"\t - Output: {node_scores[end[1]][end[0]]}")


def part_two():
    # This time, we start from the end, and walk until all values on the left line are stated.
    start_time = time.time()
    input = get_input().splitlines()

    nb_rows = len(input)
    nb_cols = len(input[0])

    node_scores = []
    elevation = []
    unvisited_nodes = []

    # Convert letters to elevation values from 1 to 26
    for y in range(nb_rows):
        ns_row = []
        e_row = []
        for x in range(nb_cols):
            if input[y][x] == "S":
                e_row.append(1)
                ns_row.append(-1)
            elif input[y][x] == "E":
                e_row.append(26)
                ns_row.append(0)
            else:
                e_row.append(ord(input[y][x]) - 96)
                ns_row.append(-1)
            unvisited_nodes.append((x, y))
        node_scores.append(ns_row)
        elevation.append(e_row)

    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]

    while len(unvisited_nodes) > 1 and min([node_scores[row][0] for row in range(nb_rows)]) == -1:
        # Focus on unvisited node with lower score
        node = None
        for un in unvisited_nodes:
            if node_scores[un[1]][un[0]] != -1:
                if not node:
                    node = un
                elif node_scores[un[1]][un[0]] < node_scores[node[1]][node[0]]:
                    node = un

        # Look at four directions
        for d in directions:
            next = (node[0] + d[0], node[1] + d[1])
            if next in unvisited_nodes:
                # Current node can be reached from next if it is one more or lower
                if elevation[next[1]][next[0]] + 1 >= elevation[node[1]][node[0]]:
                    # We can access the next node

                    if node_scores[next[1]][next[0]] == -1:
                        node_scores[next[1]][next[0]] = node_scores[node[1]][node[0]] + 1
                    elif node_scores[node[1]][node[0]] + 1 < node_scores[next[1]][next[0]]:
                        node_scores[next[1]][next[0]] = node_scores[node[1]][node[0]] + 1

        # Node is visited
        unvisited_nodes.remove(node)

        # Progress
        print(len(unvisited_nodes))

    end_time = time.time()
    print(f"Part Two")
    print(f"\t- Solved in {(end_time - start_time) * 10 ** 3}ms.")
    print(f"\t - Output: {min([node_scores[row][0] for row in range(nb_rows)])}")


def main():
    # part_one()
    part_two()


if __name__ == '__main__':
    main()