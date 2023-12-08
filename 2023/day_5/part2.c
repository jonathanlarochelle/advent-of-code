#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define LINE_BUFFER_LENGTH	(unsigned int) 211
#define NB_LINES	(unsigned int) 245
#define ASCII_DIGIT_OFFSET	(unsigned int) 48;

int main(void)
{
	printf("Advent of Code 2023\n");
	printf("Day 5, part 2\n");

	FILE *pInput;
	pInput = fopen("input.txt", "r");
	if (pInput == NULL)
	{
		printf("Input file not found.\n");
		return 1;
	}

	clock_t beginTime = clock();

	char line[LINE_BUFFER_LENGTH];

	/* Line numbers start at 1 to facilitate debugging with my text editor whose line numbers start at 1. */

	/* seed-to-soil map */
	int stsFirstLine = 4;
	int stsLastLine = 15;
	int stsNbLines = stsLastLine - stsFirstLine + 1;
	uint64_t* p_stsMap = malloc(3 * stsNbLines * sizeof(uint64_t));

	/* soil-to-fertilizer map */
	int stfFirstLine = 18;
	int stfLastLine = 34;
	int stfNbLines = stfLastLine - stfFirstLine + 1;
	uint64_t* p_stfMap = malloc(3 * stfNbLines * sizeof(uint64_t));

	/* fertilizer-to-water map */
	int ftwFirstLine = 37;
	int ftwLastLine = 75;
	int ftwNbLines = ftwLastLine - ftwFirstLine + 1;
	uint64_t* p_ftwMap = malloc(3 * ftwNbLines * sizeof(uint64_t));

	/* water-to-light map */
	int wtlFirstLine = 78;
	int wtlLastLine = 118;
	int wtlNbLines = wtlLastLine - wtlFirstLine + 1;
	uint64_t* p_wtlMap = malloc(3 * wtlNbLines * sizeof(uint64_t));

	/* light-to-temperature map */
	int lttFirstLine = 121;
	int lttLastLine = 152;
	int lttNbLines = lttLastLine - lttFirstLine + 1;
	uint64_t* p_lttMap = malloc(3 * lttNbLines * sizeof(uint64_t));

	/* temperature-to-humidity map */
	int tthFirstLine = 155;
	int tthLastLine = 196;
	int tthNbLines = tthLastLine - tthFirstLine + 1;
	uint64_t* p_tthMap = malloc(3 * tthNbLines * sizeof(uint64_t));

	/* humidity-to-location map */
	int htlFirstLine = 199;
	int htlLastLine = 244;
	int htlNbLines = htlLastLine - htlFirstLine + 1;
	uint64_t* p_htlMap = malloc(3 * htlNbLines * sizeof(uint64_t));

	/* seeds */
	int nbSeedsRanges = 20/2;
	uint64_t* p_seedRanges = malloc(nbSeedsRanges * 2 * sizeof(uint64_t));

	uint64_t lowestLocation = 1UL << 63;

	/* We cannot directly represent the maps by very long arrays because the numbers are very big.
	 * Instead, I simply convert the chars to numbers and store them in arrays of three terms
	 * such that (destination range start, source range start, length) */

	/* I then loop over each seed, look what mapping it has, and get to the location. */

	/* Using uint64_t to avoid overflows */

	/* Loop over all lines */
	uint64_t currentNumber = 0;
	uint64_t* p_map;
	int mapEntryIdx = 0;
	int idx = 0;



	for (int i=0; i<NB_LINES; ++i)
	{
		fgets(line, LINE_BUFFER_LENGTH, pInput);

		if (i == 0)
		{
			/* Seeds */
			for (int c=7; c<LINE_BUFFER_LENGTH; ++c)
			{
				//printf("char: %c\n", line[c]);
				if (isdigit(line[c]) > 0)
				{
					currentNumber *= 10;
					currentNumber += (uint64_t) line[c] - ASCII_DIGIT_OFFSET;

				}
				else
				{
					//printf("%i : %lu\n", idx, currentNumber);
					p_seedRanges[idx] = currentNumber;
					idx += 1;
					currentNumber = 0;

					if (line[c] == '\n')
					{
						idx = 0;
						break;
					}
				}
			}

			continue;
		}
		else if (i+1 >= stsFirstLine && i+1 <= stsLastLine)
		{
			p_map = p_stsMap;
			mapEntryIdx = (i+1) - stsFirstLine;
		}
		else if (i+1 >= stfFirstLine && i+1 <= stfLastLine)
		{
			p_map = p_stfMap;
			mapEntryIdx = (i+1) - stfFirstLine;
		}
		else if (i+1 >= ftwFirstLine && i+1 <= ftwLastLine)
		{
			p_map = p_ftwMap;
			mapEntryIdx = (i+1) - ftwFirstLine;
		}
		else if (i+1 >= wtlFirstLine && i+1 <= wtlLastLine)
		{
			p_map = p_wtlMap;
			mapEntryIdx = (i+1) - wtlFirstLine;
		}
		else if (i+1 >= lttFirstLine && i+1 <= lttLastLine)
		{
			p_map = p_lttMap;
			mapEntryIdx = (i+1) - lttFirstLine;
		}
		else if (i+1 >= tthFirstLine && i+1 <= tthLastLine)
		{
			p_map = p_tthMap;
			mapEntryIdx = (i+1) - tthFirstLine;
		}
		else if (i+1 >= htlFirstLine && i+1 <= htlLastLine)
		{
			p_map = p_htlMap;
			mapEntryIdx = (i+1) - htlFirstLine;
		}
		else
		{
			/* Empty line */
			continue;
		}


		for (int c=0; c<LINE_BUFFER_LENGTH; ++c)
		{
			if (isdigit(line[c]) > 0)
			{
				currentNumber *= 10;
				currentNumber += (uint64_t) line[c] - ASCII_DIGIT_OFFSET;
			}
			else
			{
				p_map[mapEntryIdx*3 + idx] = currentNumber;
				idx += 1;
				currentNumber = 0;

				if (line[c] == '\n')
				{
					idx = 0;
					break;
				}
			}
		}
	}

	uint64_t number;

	/* We use the maps to find the location for every seed and identify the lowest location number. */
	/* This is brute force, not very elegant, but it works */
	for (int sr=0; sr<nbSeedsRanges; ++sr)
	{
		printf("sr=%i, from %lu to %lu, %lu values\n", sr, p_seedRanges[sr*2], p_seedRanges[sr*2]+p_seedRanges[sr*2+1], p_seedRanges[sr*2+1]);
		for (uint64_t s=p_seedRanges[sr*2]; s<(p_seedRanges[sr*2]+p_seedRanges[sr*2+1]); ++s)
		{
			if (s%1000000 == 0)
			{
				printf("s=%lu\n", s);
			}
			number = s;
			//printf("Seed %i = %lu\n", s, number);

			for (int l=0; l<stsNbLines; ++l)
			{
				//printf("%lu;%lu;%lu\n", p_stsMap[l*3], p_stsMap[l*3+1], p_stsMap[l*3+2]);
				if (number >= p_stsMap[l*3+1] && number < (p_stsMap[l*3+1] + p_stsMap[l*3+2]))
				{
					//printf("!!\n");
					number = (number - p_stsMap[l*3+1]) + p_stsMap[l*3];
					break;
				}
			}
			//printf("\t sts=%lu\n", number);

			for (int l=0; l<stfNbLines; ++l)
			{
				if (number >= p_stfMap[l*3+1] && number < (p_stfMap[l*3+1] + p_stfMap[l*3+2]))
				{
					number = (number - p_stfMap[l*3+1]) + p_stfMap[l*3];
					break;
				}
			}
			//printf("\t stf=%lu\n", number);

			for (int l=0; l<ftwNbLines; ++l)
			{
				if (number >= p_ftwMap[l*3+1] && number < (p_ftwMap[l*3+1] + p_ftwMap[l*3+2]))
				{
					number = (number - p_ftwMap[l*3+1]) + p_ftwMap[l*3];
					break;
				}
			}
			//printf("\t ftw=%lu\n", number);

			for (int l=0; l<wtlNbLines; ++l)
			{
				if (number >= p_wtlMap[l*3+1] && number < (p_wtlMap[l*3+1] + p_wtlMap[l*3+2]))
				{
					number = (number - p_wtlMap[l*3+1]) + p_wtlMap[l*3];
					break;
				}
			}
			//printf("\t wtl=%lu\n", number);

			for (int l=0; l<lttNbLines; ++l)
			{
				if (number >= p_lttMap[l*3+1] && number < (p_lttMap[l*3+1] + p_lttMap[l*3+2]))
				{
					number = (number - p_lttMap[l*3+1]) + p_lttMap[l*3];
					break;
				}
			}
			//printf("\t ltt=%lu\n", number);

			for (int l=0; l<tthNbLines; ++l)
			{
				if (number >= p_tthMap[l*3+1] && number < (p_tthMap[l*3+1] + p_tthMap[l*3+2]))
				{
					number = (number - p_tthMap[l*3+1]) + p_tthMap[l*3];
					break;
				}
			}
			//printf("\t tth=%lu\n", number);

			for (int l=0; l<htlNbLines; ++l)
			{
				if (number >= p_htlMap[l*3+1] && number < (p_htlMap[l*3+1] + p_htlMap[l*3+2]))
				{
					number = (number - p_htlMap[l*3+1]) + p_htlMap[l*3];
					break;
				}
			}
			//printf("\t htl=%lu\n", number);


			if (number < lowestLocation)
			{
				lowestLocation = number;
			}
		}
	}

	printf("Output: %lu\n", lowestLocation);

	free(p_stsMap);
	free(p_stfMap);
	free(p_ftwMap);
	free(p_wtlMap);
	free(p_lttMap);
	free(p_tthMap);
	free(p_htlMap);
	free(p_seedRanges);

	clock_t endTime = clock();
	double executionLength = (double)(endTime - beginTime) / CLOCKS_PER_SEC * 1000;
	printf("Execution complete in %f ms.\n", executionLength);

	fclose(pInput);
	printf("Execution complete.\n");
	return 0;
}
