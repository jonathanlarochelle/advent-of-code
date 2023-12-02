#include <stdio.h>
#include <string.h>
#include <time.h>

int main(void)
{
	printf("Advent of Code 2023\n");
	printf("Day 1, part 1\n");

	FILE *pInput;
	pInput = fopen("input.txt", "r");
	if (pInput == NULL)
	{
		printf("Input file not found.\n");
		return 1;
	}

	clock_t beginTime = clock();

	unsigned int lineLength = 64;
	char line[64];

	const unsigned int asciiDigitsOffset = 48;

	unsigned int calibrationSum = 0;
	unsigned int charAsInt;
	unsigned int firstDigit;
	unsigned int lastDigit;

	while(fgets(line, lineLength, pInput))
	{
		/* Look from beginning of array for first digit */
		for (int i=0; i<lineLength; ++i)
		{
			charAsInt = (int) line[i];
			if (charAsInt>=asciiDigitsOffset && charAsInt<(asciiDigitsOffset+11))
			{
				firstDigit = charAsInt - asciiDigitsOffset;
				break;
			}
		}

		/* Look from beginning of array for last digit */
		for (int i=lineLength-1; i>=0; --i)
		{
			charAsInt = (int) line[i];
			if (charAsInt>=asciiDigitsOffset && charAsInt<(asciiDigitsOffset+11))
			{
				lastDigit = charAsInt - asciiDigitsOffset;
				break;
			}
		}
		/* Put first and last digit together, sum up */
		calibrationSum += ( (firstDigit*10) + lastDigit);

		//printf("%s", line);
		//printf("%u, %u\n", firstDigit, lastDigit);

		/* Since all lines have different lengths, clear the buffer to avoid
		 * left-overs from previous lines. */
		memset(&line[0], 0, sizeof(line));
	}

	printf("Output: %u\n", calibrationSum);

	clock_t endTime = clock();
	double executionLength = (double)(endTime - beginTime) / CLOCKS_PER_SEC * 1000;
	printf("Execution complete in %f ms.\n", executionLength);

	fclose(pInput);
	printf("Execution complete.\n");
	return 0;
}
