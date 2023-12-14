#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define LINE_BUFFER_LENGTH	(unsigned int) 102
#define NB_LINES	(unsigned int) 100
#define ASCII_DIGIT_OFFSET	(unsigned int) 48

#define CYCLES_HISTORY_LENGTH (unsigned int) 200

void tilt_north(char platform[NB_LINES][LINE_BUFFER_LENGTH], int nbRows, int nbCols)
{
	for (int col=0; col<nbCols; ++col)
	{
		for (int row=1; row<nbRows; ++row)
		{
			/* Check if O can roll up. If yes, make it roll! */
			if (platform[row][col]=='O')
			{
				/* Look up */
				for (int revRow=row-1; revRow>=0; --revRow)
				{
					if (platform[revRow][col]=='O' || platform[revRow][col]=='#')
					{
						/* Already a boulder at the row, can't roll up more. */
						break;
					}
					else
					{
						/* roll up */
						platform[revRow+1][col] = '.';
						platform[revRow][col] = 'O';
					}
				}
			}
		}
	}
}

void tilt_south(char platform[NB_LINES][LINE_BUFFER_LENGTH], int nbRows, int nbCols)
{
	for (int col=0; col<nbCols; ++col)
	{
		for (int row=nbRows-2; row>=0; --row)
		{
			/* Check if O can roll down. If yes, make it roll! */
			if (platform[row][col]=='O')
			{
				/* Look down */
				for (int revRow=row+1; revRow<nbRows; ++revRow)
				{
					if (platform[revRow][col]=='O' || platform[revRow][col]=='#')
					{
						/* Already a boulder at the row, can't roll down more. */
						break;
					}
					else
					{
						/* roll down */
						platform[revRow-1][col] = '.';
						platform[revRow][col] = 'O';
					}
				}
			}
		}
	}
}

void tilt_west(char platform[NB_LINES][LINE_BUFFER_LENGTH], int nbRows, int nbCols)
{
	for (int row=0; row<nbRows; ++row)
	{
		for (int col=1; col<nbCols; ++col)
		{
			/* Check if O can roll left. If yes, make it roll! */
			if (platform[row][col]=='O')
			{
				/* Look left */
				for (int revCol=col-1; revCol>=0; --revCol)
				{
					if (platform[row][revCol]=='O' || platform[row][revCol]=='#')
					{
						/* Already a boulder at the col, can't roll left more. */
						break;
					}
					else
					{
						/* roll left */
						platform[row][revCol+1] = '.';
						platform[row][revCol] = 'O';
					}
				}
			}
		}
	}
}

void tilt_east(char platform[NB_LINES][LINE_BUFFER_LENGTH], int nbRows, int nbCols)
{
	for (int row=0; row<nbRows; ++row)
	{
		for (int col=nbCols-1; col>=0; --col)
		{
			/* Check if O can roll right. If yes, make it roll! */
			if (platform[row][col]=='O')
			{
				/* Look right */
				for (int revCol=col+1; revCol<nbCols; ++revCol)
				{
					if (platform[row][revCol]=='O' || platform[row][revCol]=='#')
					{
						/* Already a boulder at the col, can't roll right more. */
						break;
					}
					else
					{
						/* roll right */
						platform[row][revCol-1] = '.';
						platform[row][revCol] = 'O';
					}
				}
			}
		}
	}
}

int main(void)
{
	printf("Advent of Code 2023\n");
	printf("Day 14, part 2\n");

	FILE *pInput;
	pInput = fopen("input.txt", "r");
	if (pInput == NULL)
	{
		printf("Input file not found.\n");
		return 1;
	}

	clock_t beginTime = clock();

	int output = 0;
	char platform[NB_LINES][LINE_BUFFER_LENGTH];
	char platformHistory[CYCLES_HISTORY_LENGTH][NB_LINES][LINE_BUFFER_LENGTH];

	/* Read all lines into one big matrix */
	for (int l=0; l<NB_LINES; ++l)
	{
		fgets(platform[l], LINE_BUFFER_LENGTH, pInput);
	}

	/* Execute all cycles ..... */
	/* It would take forever ... */
	/* Idea: check after each cycle if we have reached the same position as the first cycle */
	/* Surely there is a repetition at some point ... */
	/* Idea was correct on the basis, but I falsely assumed that the cycle would always come back to the
	 * first state, which is not necessarily the case. I thus need to keep in memory all previous states,
	 * and verify after each cycle.
	 */
	printf("what\n");
	int nbCycles = 1000000000;
	bool differenceFound = false;
	int cycleLoopLength;
	int nbFullLoopsAhead;
	bool cycleLoopFound = false;

	for (int cycle=0; cycle<nbCycles; ++cycle)
	{
		printf("Cycle %i/%i\n", cycle+1, nbCycles);

		tilt_north(platform, NB_LINES, LINE_BUFFER_LENGTH-2);
		tilt_west(platform, NB_LINES, LINE_BUFFER_LENGTH-2);
		tilt_south(platform, NB_LINES, LINE_BUFFER_LENGTH-2);
		tilt_east(platform, NB_LINES, LINE_BUFFER_LENGTH-2);

		/* Store cycle in history */
		if (!cycleLoopFound)
		{
			for (int row=0; row<NB_LINES; ++row)
			{
				for (int col=0; col<LINE_BUFFER_LENGTH; ++col)
				{
					platformHistory[cycle][row][col] = platform[row][col];
				}
			}


			/* Look at past cycles */
			for (int pastCycle=0; pastCycle<cycle; ++pastCycle)
			{
				differenceFound = false;
				for (int row=0; row<NB_LINES; ++row)
				{
					for (int col=0; col<LINE_BUFFER_LENGTH; ++col)
					{
						if (platformHistory[pastCycle][row][col] != platform[row][col])
						{
							differenceFound = true;
							break;
						}
					}

					if (differenceFound)
					{
						break;
					}
				}

				if (!differenceFound)
				{
					printf("Cycle %i is equivalent to past cycle %i!\n", cycle, pastCycle);
					cycleLoopLength = cycle - pastCycle;
					nbFullLoopsAhead = (int) (nbCycles-pastCycle)/cycleLoopLength - 1;
					cycle += cycleLoopLength*nbFullLoopsAhead;
					cycleLoopFound = true;
					break;
				}
				differenceFound = true;
			}
		}

	}

	printf("Platform after %i cycles:\n", nbCycles);
	for (int row=0; row<NB_LINES; ++row)
	{
		printf("%s", platform[row]);

		for (int col=0; col<LINE_BUFFER_LENGTH; ++col)
		{
			if (platform[row][col]=='O')
			{
				output += NB_LINES - row;
			}
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
