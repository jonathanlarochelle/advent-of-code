#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define LINE_BUFFER_LENGTH	(unsigned int) 143
#define NB_LINES	(unsigned int) 140
#define ASCII_DIGIT_OFFSET	(unsigned int) 48;

int main(void)
{
	printf("Advent of Code 2023\n");
	printf("Day 10, part 2\n");

	FILE *pInput;
	pInput = fopen("input.txt", "r");
	if (pInput == NULL)
	{
		printf("Input file not found.\n");
		return 1;
	}

	clock_t beginTime = clock();
	char line[LINE_BUFFER_LENGTH];
	int output = 0;

	/* First load the whole map into a matrix of values which indicate potential directions for each position.
	 * S can go everywhere, . nowhere, etc.
	 *
	 * Each value is int8, with the first bits representing one direction each. */
#define NORTH	(int8_t) 0b0001
#define EAST	(int8_t) 0b0010
#define SOUTH	(int8_t) 0b0100
#define WEST	(int8_t) 0b1000
	int8_t map[NB_LINES][LINE_BUFFER_LENGTH] = { 0 };
	char loopMap[NB_LINES][LINE_BUFFER_LENGTH];

	int sRow;
	int sCol;

	for (int i=0; i<NB_LINES; ++i)
	{
		fgets(line, LINE_BUFFER_LENGTH, pInput);

		for (int c=0; c<LINE_BUFFER_LENGTH; ++c)
		{
			loopMap[i][c] = ' ';
			switch (line[c])
			{
			case '|':
				map[i][c] = NORTH + SOUTH;
				break;
			case '-':
				map[i][c] = WEST + EAST;
				break;
			case 'L':
				map[i][c] = NORTH + EAST;
				break;
			case 'J':
				map[i][c] = NORTH + WEST;
				break;
			case '7':
				map[i][c] = SOUTH + WEST;
				break;
			case 'F':
				map[i][c] = SOUTH + EAST;
				break;
			case 'S':
				map[i][c] = NORTH + EAST + WEST + SOUTH;
				sRow = i;
				sCol = c;
				printf("Found S at (%i,%i)\n", sRow, sCol);
				loopMap[i][c] = 'L';
				break;
			}

		}
	}

	/* Then we trace out the loop in a new matrix */
	int lastCol = sCol;
	int lastRow = sRow;
	int newCol = lastCol;
	int newRow = lastRow;
	int8_t lastCameFrom = SOUTH;
	int8_t newCameFrom = lastCameFrom;

	while (true)
	{
		/* Looking north */
		if (lastRow>0 && (lastCameFrom&NORTH)==0)
		{
			if ((map[lastRow][lastCol]&NORTH)>0 && (map[lastRow-1][lastCol]&SOUTH)>0)
			{
				newRow = lastRow - 1;
				newCol = lastCol;
				newCameFrom = SOUTH;
			}
		}

		/* Looking east */
		if (lastCol+1<LINE_BUFFER_LENGTH && (lastCameFrom&EAST)==0)
		{
			if ((map[lastRow][lastCol]&EAST)>0 && (map[lastRow][lastCol+1]&WEST)>0)
			{
				newCol = lastCol + 1;
				newRow = lastRow;
				newCameFrom = WEST;
			}
		}

		/* Looking south */
		if (lastRow+1<NB_LINES && (lastCameFrom&SOUTH)==0)
		{
			if ((map[lastRow][lastCol]&SOUTH)>0 && (map[lastRow+1][lastCol]&NORTH)>0)
			{
				newRow = lastRow + 1;
				newCol = lastCol;
				newCameFrom = NORTH;
			}
		}

		/* Looking west */
		if (lastCol>0 && (lastCameFrom&WEST)==0)
		{
			if ((map[lastRow][lastCol]&WEST)>0 && (map[lastRow][lastCol-1]&EAST)>0)
			{
				newCol = lastCol - 1;
				newRow = lastRow;
				newCameFrom = EAST;
			}
		}

		//printf("%i: (%i,%i) -> (%i,%i)\n", totalSteps, lastRow,
		//		lastCol, newRow, newCol);

		if (newCol==sCol && newRow==sRow)
		{
			/* Came back to the start. */
			printf("Came back to the start.\n");
			break;
		}
		else if (newCol==lastCol && newRow==lastRow)
		{
			/* Stuck in a loop */
			printf("Stuck.\n");
			break;
		}

		loopMap[newRow][newCol] = 'L';
		lastRow = newRow;
		lastCol = newCol;
		lastCameFrom = newCameFrom;
	}

	int score = 0;
	int8_t lastIndividual = 0;

	for (int r=0; r<NB_LINES; ++r)
	{
		score=0;
		lastIndividual=0;

		for (int c=0; c<LINE_BUFFER_LENGTH; ++c)
		{
			if (map[r][c]==NORTH+SOUTH+EAST+WEST)
			{
				/* Start */
				/* TODO: this is hardcoded, assuming that S acts like an L */
				if (lastIndividual == 0)
				{
					score += 0;
				}
			}
			else if (loopMap[r][c]=='L')
			{
				if (map[r][c]==NORTH+SOUTH)
				{
					score += 1;
				}
				else if ((map[r][c]&NORTH)>0)
				{
					if (lastIndividual==0)
					{
						lastIndividual = NORTH;
					}
					else if (lastIndividual==NORTH)
					{
						score += 0;
						lastIndividual = 0;
					}
					else if (lastIndividual==SOUTH)
					{
						score += 1;
						lastIndividual = 0;
					}
				}
				else if ((map[r][c]&SOUTH)>0)
				{
					if (lastIndividual==0)
					{
						lastIndividual = SOUTH;
					}
					else if (lastIndividual==NORTH)
					{
						score += 1;
						lastIndividual = 0;
					}
					else if (lastIndividual==SOUTH)
					{
						score += 0;
						lastIndividual = 0;
					}
				}
			}
			else if (loopMap[r][c] == ' ')
			{
				if (score%2==0)
				{
					loopMap[r][c] = 'O';
				}
				else
				{
					loopMap[r][c] = 'I';
					output += 1;
				}
			}
		}
	}

	/* Print out the loop for debugging*/
	for (int r=0; r<NB_LINES; ++r)
	{
		for (int c=0; c<LINE_BUFFER_LENGTH; ++c)
		{
			printf("%c", loopMap[r][c]);
		}
		printf("\n");
	}

	printf("Output: %i\n", output);

	clock_t endTime = clock();
	double executionLength = (double)(endTime - beginTime) / CLOCKS_PER_SEC * 1000;
	printf("Execution complete in %f ms.\n", executionLength);

	fclose(pInput);
	printf("Execution complete.\n");
	return 0;
}
