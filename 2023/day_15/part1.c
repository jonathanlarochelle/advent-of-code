#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define LINE_BUFFER_LENGTH	(unsigned int) 22885
#define ASCII_DIGIT_OFFSET	(unsigned int) 48

int main(void)
{
	printf("Advent of Code 2023\n");
	printf("Day 15, part 1\n");

	FILE *pInput;
	pInput = fopen("input.txt", "r");
	if (pInput == NULL)
	{
		printf("Input file not found.\n");
		return 1;
	}

	clock_t beginTime = clock();

	int output = 0;
	char line[LINE_BUFFER_LENGTH];

	int currentHash = 0;

	fgets(line, LINE_BUFFER_LENGTH, pInput);

	for (int i=0; i<LINE_BUFFER_LENGTH; ++i)
	{
		if (line[i]==',' || line[i]=='\n')
		{
			/* End of current step */
			printf("Step hash: %i\n", currentHash);
			output += currentHash;
			currentHash = 0;
		}
		else
		{
			/* Process char */
			currentHash += (int) line[i];
			currentHash *= 17;
			currentHash %= 256;
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
