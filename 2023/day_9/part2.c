#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define LINE_BUFFER_LENGTH	(unsigned int) 125
#define NB_LINES	(unsigned int) 200
#define ASCII_DIGIT_OFFSET	(unsigned int) 48;

int main(void)
{
	printf("Advent of Code 2023\n");
	printf("Day 9, part 2\n");

	FILE *pInput;
	pInput = fopen("input.txt", "r");
	if (pInput == NULL)
	{
		printf("Input file not found.\n");
		return 1;
	}

	clock_t beginTime = clock();

	char line[LINE_BUFFER_LENGTH];

	int64_t predictionsSum = 0;

	/* In each line, we first detect all the numbers.
	 * From the number of spaces in a given line, we determine how many numbers we have.
	 * This is then used to create a dynamically sized array and then fill it up.
	 * We then recursively create arrays of the difference until we have a zero-filled array. */

	int currentNumber = 0;
#define MAX_NB_VALUES	40
#define MAX_DEPTH		MAX_NB_VALUES
	int valuesArray[MAX_DEPTH][MAX_NB_VALUES];	// [depth][value]
	int idx = 0;
	bool allZeroes = true;
	int prediction;
	int sign = 1;
	int nbValues = 0;

	for (int i=0; i<NB_LINES; ++i)
	{
		fgets(line, LINE_BUFFER_LENGTH, pInput);

		/* Get the history for the given line */
		printf("Line %i = ", i);
		nbValues = 0;
		sign = 1;
		for (int c=0; c<LINE_BUFFER_LENGTH; ++c)
		{
			if (isdigit(line[c]) > 0)
			{
				currentNumber *= 10;
				currentNumber += (uint64_t) line[c] - ASCII_DIGIT_OFFSET;

			}
			else if (line[c] == '-')
			{
				sign = -1;
			}
			else
			{
				currentNumber *= sign;
				printf("%i ", currentNumber);
				valuesArray[0][idx] = currentNumber;
				idx += 1;
				currentNumber = 0;
				sign = 1;
				nbValues += 1;

				if (line[c] == '\n')
				{
					idx = 0;
					break;
				}
			}
		}
		printf("\n");


		/* Go down in depth */
		prediction = valuesArray[0][0];
		sign = 1;
		for (int d=1; d<MAX_DEPTH; ++d)
		{
			allZeroes = true;

			/* For each depth, compute the difference of previous depth */
			printf("\t d=%i;", d);
			for (int n=0; n<(nbValues-d); ++n)
			{

				valuesArray[d][n] = valuesArray[d-1][n+1] - valuesArray[d-1][n];
				printf("%i ", valuesArray[d][n]);
				if (valuesArray[d][n] != 0)
				{
					allZeroes = false;
				}

				if (n+1==nbValues-d)
				{
					if (d%2==0)
					{
						sign = 1;
					}
					else
					{
						sign = -1;
					}
					prediction += sign*valuesArray[d][0];
				}
			}
			printf("\n");

			if (allZeroes)
			{
				break;
			}
		}
		printf("\tprediction: %i\n", prediction);
		predictionsSum += prediction;

	}

	printf("Output: %li\n", predictionsSum);

	clock_t endTime = clock();
	double executionLength = (double)(endTime - beginTime) / CLOCKS_PER_SEC * 1000;
	printf("Execution complete in %f ms.\n", executionLength);

	fclose(pInput);
	printf("Execution complete.\n");
	return 0;
}
