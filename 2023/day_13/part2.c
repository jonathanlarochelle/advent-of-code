#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define LINE_BUFFER_LENGTH	(unsigned int) 20
#define NB_LINES	(unsigned int) 1351
#define ASCII_DIGIT_OFFSET	(unsigned int) 48

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
	printf("Day 13, part 1\n");

	FILE *pInput;
	pInput = fopen("input.txt", "r");
	if (pInput == NULL)
	{
		printf("Input file not found.\n");
		return 1;
	}

	clock_t beginTime = clock();

	int output = 0;
	char line[NB_LINES][LINE_BUFFER_LENGTH];
	int firstLine = 0;
	int lastLine = 0;
	int maxDeltaCol = 0;
	int col1, col2, row1, row2;
	bool reflectionFound;

	int nbDifferentChars = 0;
	int smudgeRow;
	int smudgeCol;

	/* Read input line by line and stop when an empty line is detected. */
	/* At every empty line, go through the previously-scanned patterned to detect reflections. */
	/* First go through each row and column, identify the row or column with only one difference. */
	/* Calculate the new reflection line based on this knowledge. */

	for (int l=0; l<NB_LINES; ++l)
	{
		fgets(line[l], LINE_BUFFER_LENGTH, pInput);

		if (line[l][0]=='\n')
		{

			lastLine = l-1;

			/* Look at each column */
			/* vLine is the column to the left of the vertical line. */
			reflectionFound = false;
			for (int vLine=0; vLine<LINE_BUFFER_LENGTH; ++vLine)
			{
				nbDifferentChars = 0;
				if (line[firstLine][vLine]=='\n')
				{
					/* end of pattern, no vertical reflection found */
					break;
				}

				for (int deltaCol=0; deltaCol<LINE_BUFFER_LENGTH; ++deltaCol)
				{

					col1 = vLine-deltaCol;
					col2 = vLine+1+deltaCol;

					if (col1<0 || line[firstLine][col2]=='\n')
					{
						/* delta is bigger than the pattern, stop looking. */
						break;
					}

					/* Compare both columns */
					for (int row=firstLine; row<lastLine+1; ++row)
					{
						if (line[row][col1] != line[row][col2])
						{
							nbDifferentChars += 1;
							smudgeRow = row;
							smudgeCol = col1;
						}
					}
				}

				/* If there is exactly one different char, it is the one to change! */
				if (nbDifferentChars == 1)
				{
					/* This is the new vertical reflection! */
					/* Careful: columns numbering starts at 1 in this problem. */
					printf("Pattern at lines %i-%i; Smudge at (%i,%i); New vertical reflection between columns %i and %i\n",
							firstLine+1, lastLine+1, smudgeRow+1, smudgeCol+1, vLine+1, vLine+2);

					reflectionFound = true;
					output += vLine+1;
					printf("\tAdding %i, output is now %i\n", vLine+1, output);
					break;
				}
			}

			/* vLine was found, skip search for horizontal reflection. */
			if (reflectionFound)
			{
				firstLine = l+1;
				continue;
			}

			for (int hLine=firstLine; hLine<lastLine+1; ++hLine)
			{
				nbDifferentChars = 0;
				if (line[hLine][0]=='\n')
				{
					/* end of pattern, no horizontal reflection found */
					break;
				}

				for (int deltaRow=0; deltaRow<(lastLine-firstLine); ++deltaRow)
				{
					row1 = hLine-deltaRow;
					row2 = hLine+1+deltaRow;

					if (row1<firstLine || line[row2][0]=='\n')
					{
						/* delta is bigger than the pattern, stop looking. */
						break;
					}

					/* Compare both rows */
					for (int col=0; col+1<LINE_BUFFER_LENGTH; ++col)
					{
						if (line[row1][col]=='\n')
						{
							break;
						}

						if (line[row1][col] != line[row2][col])
						{
							nbDifferentChars += 1;
							smudgeRow = row1;
							smudgeCol = col;
						}
					}
				}

				if (nbDifferentChars==1)
				{
					/* This is the new horizontal reflection! */
					/* Careful: rows numbering starts at 1 in this problem. */
					printf("Pattern at lines %i-%i; Smudge at (%i,%i); New horizontal reflection between rows %i and %i (%i and %i)\n",
							firstLine+1, lastLine+1, smudgeRow+1, smudgeCol+1, hLine-firstLine+1, hLine-firstLine+2, hLine+1, hLine+2);

					reflectionFound = true;
					output += 100*(hLine-firstLine+1);
					printf("\tAdding %i, output is now %i\n", 100*(hLine-firstLine+1), output);
					break;
				}
			}

			if(!reflectionFound)
			{
				printf("No reflection found for lines %i-%i ...\n", firstLine, lastLine);
			}

			firstLine = l+1;
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
