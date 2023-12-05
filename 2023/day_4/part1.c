#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define LINE_BUFFER_LENGTH	(unsigned int) 118
#define NB_LINES	(unsigned int) 202

int main(void)
{
	printf("Advent of Code 2023\n");
	printf("Day 4, part 1\n");

	FILE *pInput;
	pInput = fopen("input.txt", "r");
	if (pInput == NULL)
	{
		printf("Input file not found.\n");
		return 1;
	}

	clock_t beginTime = clock();

	char line[LINE_BUFFER_LENGTH];

	unsigned int points = 0;

	unsigned int nbWinningNumbers = 10;
	char winningNumbers[10][2];
	unsigned int nbNumbersIHave = 25;
	unsigned int numbersIHave[25] = { 0 };
	char numberString[2] = "00";
	unsigned int number = 0;
	unsigned int nbWinningNumbersForOneTicket = 0;

	/* Loop over all lines */
	for (int i=0; i<NB_LINES; ++i)
	{
		fgets(line, LINE_BUFFER_LENGTH, pInput);

		/* Fortunately, the numbers are always placed at the same positions in a line. */
		/* We actually do not need to convert them to numbers! This saves some time. */

		/* Get winning numbers */
		for (int w=0; w<nbWinningNumbers; ++w)
		{
			strncpy(winningNumbers[w], line+(3*w+10), 2);
		}

		/* Go through ticket numbers, check if they are winning */
		for (int n=0; n<nbNumbersIHave; ++n)
		{
			strncpy(&numberString, line+(3*n+42), 2);
			for (int w=0; w<nbWinningNumbers; ++w)
			{
				if (winningNumbers[w][0] == numberString[0] && winningNumbers[w][1] == numberString[1])
				{
					nbWinningNumbersForOneTicket += 1;
					break;
				}
			}
		}

		/* Tally up the count */
		if (nbWinningNumbersForOneTicket != 0)
		{
			points += 1 << (nbWinningNumbersForOneTicket - 1);
		}

		nbWinningNumbersForOneTicket = 0;
	}



	printf("Output: %u\n", points);

	clock_t endTime = clock();
	double executionLength = (double)(endTime - beginTime) / CLOCKS_PER_SEC * 1000;
	printf("Execution complete in %f ms.\n", executionLength);

	fclose(pInput);
	printf("Execution complete.\n");
	return 0;
}
