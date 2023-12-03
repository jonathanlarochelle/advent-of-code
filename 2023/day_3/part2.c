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
	printf("Day 3, part 2\n");

	FILE *pInput;
	pInput = fopen("input.txt", "r");
	if (pInput == NULL)
	{
		printf("Input file not found.\n");
		return 1;
	}

	clock_t beginTime = clock();

	unsigned int lineLength = 142;
	unsigned int nbLines = 140;
	char schematic[140][142];

	/* Load the schematic into the schematic matrix */
	for (int i=0; i<nbLines; ++i)
	{
		fgets(schematic[i], lineLength, pInput);
	}

	/* Go through each char, identify how many part numbers exist for each * symbols. */

	int ii;
	int jj;
	bool gears[140][142] = {{false}};
	unsigned int gearRatios[140][142] = {{0}};
	unsigned int nbParts = 0;

	for (int i=0; i<nbLines; ++i)
	{
		for (int j=0; j<lineLength; ++j)
		{
			nbParts = 0;

			if (schematic[i][j]=='*')
			{
				/* Look around for numbers */

				/* Left */
				ii = i;
				jj = j-1;
				if (ii>=0 && jj>=0 && ii<nbLines && jj<lineLength)
				{
					if (isCharADigit(schematic[ii][jj]))
					{
						nbParts += 1;
					}
				}

				/* Right */
				ii = i;
				jj = j+1;
				if (ii>=0 && jj>=0 && ii<nbLines && jj<lineLength)
				{
					if (isCharADigit(schematic[ii][jj]))
					{
						nbParts += 1;
					}
				}

				/* Top: if middle is a digit, other digits on the line would be part of the same number. */
				ii = i-1;
				jj = j;
				if (ii>=0 && jj>=0 && ii<nbLines && jj<lineLength)
				{
					if (isCharADigit(schematic[ii][jj]))
					{
						nbParts += 1;
					}
					else
					{
						/* Top left */
						ii = i-1;
						jj = j-1;
						if (ii>=0 && jj>=0 && ii<nbLines && jj<lineLength)
						{
							if (isCharADigit(schematic[ii][jj]))
							{
								nbParts += 1;
							}
						}
						/* Top right */
						ii = i-1;
						jj = j+1;
						if (ii>=0 && jj>=0 && ii<nbLines && jj<lineLength)
						{
							if (isCharADigit(schematic[ii][jj]))
							{
								nbParts += 1;
							}
						}
					}
				}

				/* Bottom: if middle is a digit, other digits on the line would be part of the same number. */
				ii = i+1;
				jj = j;
				if (ii>=0 && jj>=0 && ii<nbLines && jj<lineLength)
				{
					if (isCharADigit(schematic[ii][jj]))
					{
						nbParts += 1;
					}
					else
					{
						/* Top left */
						ii = i+1;
						jj = j-1;
						if (ii>=0 && jj>=0 && ii<nbLines && jj<lineLength)
						{
							if (isCharADigit(schematic[ii][jj]))
							{
								nbParts += 1;
							}
						}
						/* Top right */
						ii = i+1;
						jj = j+1;
						if (ii>=0 && jj>=0 && ii<nbLines && jj<lineLength)
						{
							if (isCharADigit(schematic[ii][jj]))
							{
								nbParts += 1;
							}
						}
					}
				}

				if (nbParts==2)
				{
					gears[i][j] = true;
				}
			}

		}
	}

	/* Go through each char, compute numbers (like in part 1), if gears is True, put the number in gearsRatio.
	 * If there is already a nb in gears ratio, do the multiplication and sum. */
	unsigned int gearRatiosSum = 0;
	unsigned int currentNumber = 0;
	bool symbolFound = false;
	int iGear;
	int jGear;

	for (int i=0; i<nbLines; ++i)
	{

		for (int j=0; j<lineLength; ++j)
		{
			if (isCharADigit(schematic[i][j]))
			{
				currentNumber = currentNumber*10 + getDigitFromChar(schematic[i][j]);

				/* Look around for symbol */
				for (int deltaI=-1; deltaI<2; ++deltaI)
				{
					for (int deltaJ=-1; deltaJ<2; ++deltaJ)
					{
						ii = i+deltaI;
						jj = j+deltaJ;
						/* is the new i and j valid */
						if (ii>=0 && jj>=0 && ii<nbLines && jj<lineLength)
						{
							if (gears[ii][jj])
							{
								symbolFound = true;
								iGear = ii;
								jGear = jj;
							}
						}

					}
				}
			}
			else
			{
				if (symbolFound)
				{
					if (gearRatios[iGear][jGear]==0)
					{
						gearRatios[iGear][jGear] = currentNumber;
					}
					else
					{
						gearRatiosSum += (gearRatios[iGear][jGear]*currentNumber);
					}
				}

				//printf("(%i,%i) = %i (%d)\n", i+1, j+1, currentNumber, symbolFound);

				currentNumber = 0;
				symbolFound = false;
			}
		}
	}

	printf("Output: %u\n", gearRatiosSum);

	clock_t endTime = clock();
	double executionLength = (double)(endTime - beginTime) / CLOCKS_PER_SEC * 1000;
	printf("Execution complete in %f ms.\n", executionLength);

	fclose(pInput);
	printf("Execution complete.\n");
	return 0;
}
