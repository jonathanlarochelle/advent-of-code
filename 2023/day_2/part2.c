#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

bool isCharADigit(char c)
{
	const unsigned int asciiDigitsOffset = 48;
	unsigned int charAsInt = c;
	return (charAsInt>=asciiDigitsOffset && charAsInt<(asciiDigitsOffset+11));
}

unsigned int getDigitFromChar(char c)
{
	return (unsigned int) c - 48;
}

int main(void)
{
	printf("Advent of Code 2023\n");
	printf("Day 2, part 2\n");

	FILE *pInput;
	pInput = fopen("input.txt", "r");
	if (pInput == NULL)
	{
		printf("Input file not found.\n");
		return 1;
	}

	clock_t beginTime = clock();

	unsigned int lineLength = 200;
	char line[200];

	unsigned int powersSum = 0;
	unsigned int charAsInt;

	unsigned int gameId;
	bool gameIdDone;
	bool nbOfCubesSection;
	unsigned int nbCubes;

	unsigned int nbRed = 0;
	unsigned int nbGreen = 0;
	unsigned int nbBlue = 0;

	while(fgets(line, lineLength, pInput))
	{
		/* Loop through each char */
		/* Game id: first digit(s) before finding a : char. */
		/* Revealed cubes: digit(s) followed by a space and one of {r, g, b} */
		gameId = 0;
		gameIdDone = false;
		nbOfCubesSection = false;
		nbCubes = 0;

		nbRed = 0;
		nbGreen = 0;
		nbBlue = 0;

		for (int i=0; i<lineLength; ++i)
		{
			charAsInt = (int) line[i];

			/* Break on end of line */
			if (line[i] == '\n')
			{
				break;
			}

			/* Game ID section */
			if (!gameIdDone)
			{
				if (line[i] == ':')
				{
					gameIdDone = true;
					nbOfCubesSection = true;
				}
				else if (isCharADigit(line[i]))
				{
					//printf("%c is a digit\n", line[i]);
					gameId = (gameId*10) + getDigitFromChar(line[i]);
				}
			}

			/* Nb of cubes sections */
			if (nbOfCubesSection)
			{
				if (isCharADigit(line[i]))
				{
					//printf("%c is a digit\n", line[i]);
					nbCubes = (nbCubes*10) + getDigitFromChar(line[i]);
				}
				else if (line[i] == ' ')
				{
					/* Check next char for red, green or blue */
					if (line[i+1] == 'r')
					{
						if (nbCubes > nbRed)
						{
							nbRed = nbCubes;
						}
					}
					else if (line[i+1] == 'g')
					{
						if (nbCubes > nbGreen)
						{
							nbGreen = nbCubes;
						}
					}
					else if (line[i+1] == 'b')
					{
						if (nbCubes > nbBlue)
						{
							nbBlue = nbCubes;
						}
					}
					nbCubes = 0;
				}
			}
		}

		powersSum += (nbRed * nbGreen * nbBlue);


		//printf("Game id: %i\n", gameId);

		/* Since all lines have different lengths, clear the buffer to avoid
		 * left-overs from previous lines. */
		memset(&line[0], 0, sizeof(line));
	}

	printf("Output: %u\n", powersSum);

	clock_t endTime = clock();
	double executionLength = (double)(endTime - beginTime) / CLOCKS_PER_SEC * 1000;
	printf("Execution complete in %f ms.\n", executionLength);

	fclose(pInput);
	printf("Execution complete.\n");
	return 0;
}
