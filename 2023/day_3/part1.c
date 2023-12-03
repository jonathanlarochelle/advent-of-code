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
	printf("Day 3, part 1\n");

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

	unsigned int partNumbersSum = 0;

	/* Load the schematic into the schematic matrix */
	for (int i=0; i<nbLines; ++i)
	{
		fgets(schematic[i], lineLength, pInput);
		//printf("Line %d = %s", i, schematic[i]);
	}

	/* Go through each line, detect the numbers,
	 * and look if any of the digit touches a symbol.
	 */

	unsigned int currentNumber = 0;
	bool symbolFound = false;
	int ii;
	int jj;

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
							if (!isCharADigit(schematic[ii][jj]) &&
									schematic[ii][jj]!='.' && schematic[ii][jj]!='\n')
							{
								//printf("\t(%i,%i) symbol found!\n", ii, jj);
								symbolFound = true;
							}
						}

					}
				}
			}
			else
			{
				if (symbolFound)
				{
					partNumbersSum += currentNumber;
				}

				//printf("(%i,%i) = %i (%d)\n", i+1, j+1, currentNumber, symbolFound);

				currentNumber = 0;
				symbolFound = false;
			}
		}
	}

	printf("Output: %u\n", partNumbersSum);

	clock_t endTime = clock();
	double executionLength = (double)(endTime - beginTime) / CLOCKS_PER_SEC * 1000;
	printf("Execution complete in %f ms.\n", executionLength);

	fclose(pInput);
	printf("Execution complete.\n");
	return 0;
}
