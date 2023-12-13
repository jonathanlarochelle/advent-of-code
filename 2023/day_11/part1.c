#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define LINE_BUFFER_LENGTH	(unsigned int) 142
#define NB_LINES	(unsigned int) 140
#define ASCII_DIGIT_OFFSET	(unsigned int) 48
#define NB_GALAXIES (unsigned int) 439

int max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int min(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int main(void)
{
	printf("Advent of Code 2023\n");
	printf("Day 11, part 1\n");

	FILE *pInput;
	pInput = fopen("input.txt", "r");
	if (pInput == NULL)
	{
		printf("Input file not found.\n");
		return 1;
	}

	clock_t beginTime = clock();
	int output;

	char image[NB_LINES][LINE_BUFFER_LENGTH];
	int galaxyInRow[NB_LINES] = { 0 };
	int galaxyInCol[LINE_BUFFER_LENGTH] = { 0 };
	int galaxies[NB_GALAXIES][2] = { 0 };
	int galaxyIdx = 0;


	/* Read the input into an image matrix and take note of the rows
	 * and cols where a galaxy is present.
	 *
	 * We also store the coordinates of every galaxy in a matrix:
	 * 		mat[galaxyIdx] = {row, col}
	 */

	for (int r=0; r<NB_LINES; ++r)
	{
		fgets(image[r], LINE_BUFFER_LENGTH, pInput);

		for (int c=0; c<LINE_BUFFER_LENGTH; ++c)
		{
			if (image[r][c]=='#')
			{
				galaxyInRow[r] = 1;
				galaxyInCol[c] = 1;

				galaxies[galaxyIdx][0] = r;
				galaxies[galaxyIdx][1] = c;

				galaxyIdx += 1;
			}
		}
	}

	printf("Nb of galaxies: %i\n", galaxyIdx);

	/* We then loop through the galaxies to find each pair. For each pair,
	 * we calculate the shortest path, which consists in the difference in the rows
	 * and cols, taking into account the columns and rows that must be doubled
	 * due to expansion.
	 */

	int shortestPath = 0;
	int row1 = 0;
	int row2 = 0;
	int col1 = 0;
	int col2 = 0;

	for (int g1=0; g1<galaxyIdx; ++g1)
	{
		for (int g2=g1+1; g2<galaxyIdx; ++g2)
		{
			row1 = min(galaxies[g1][0], galaxies[g2][0]);
			row2 = max(galaxies[g1][0], galaxies[g2][0]);
			col1 = min(galaxies[g1][1], galaxies[g2][1]);
			col2 = max(galaxies[g1][1], galaxies[g2][1]);

			shortestPath = (row2 - row1) + (col2 - col1);

			for (int r=row1; r<row2; ++r)
			{
				if (galaxyInRow[r] == 0)
				{
					shortestPath += 1;
				}
			}

			for (int c=col1; c<col2; ++c)
			{
				if (galaxyInCol[c] == 0)
				{
					shortestPath += 1;
				}
			}

			//printf("(%i, %i) -> %i\n", g1, g2, shortestPath);
			output += shortestPath;
		}
	}


	printf("Output: %i\n", output);

	clock_t endTime = clock();
	double executionLength = (double)(endTime - beginTime) / CLOCKS_PER_SEC * 1000;
	printf("Execution complete in %f ms.\n", executionLength);

	fclose(pInput);
	printf("Execution complete.\n");
	return 0;
}
