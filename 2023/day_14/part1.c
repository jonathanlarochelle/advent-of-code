#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define LINE_BUFFER_LENGTH	(unsigned int) 103
#define NB_LINES	(unsigned int) 100
#define ASCII_DIGIT_OFFSET	(unsigned int) 48

int main(void)
{
	printf("Advent of Code 2023\n");
	printf("Day 14, part 1\n");

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

	/* Read all lines into one big matrix */
	for (int l=0; l<NB_LINES; ++l)
	{
		fgets(platform[l], LINE_BUFFER_LENGTH, pInput);
	}

	/* Go through the matrix column-by-column and make the round boulders O roll up */
	for (int col=0; col<LINE_BUFFER_LENGTH-2; ++col)
	{
		for (int row=1; row<NB_LINES; ++row)
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

	printf("Platform after tilting north:\n");
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
