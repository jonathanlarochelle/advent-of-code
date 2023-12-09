#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define ASCII_DIGIT_OFFSET	(unsigned int) 48;

int main(void)
{
	printf("Advent of Code 2023\n");
	printf("Day 6, part 1\n");

	clock_t beginTime = clock();

	/* Since the input is quite simple, we do not program a parser. */
	int nbRaces = 4;
	int arrTime[4] = {41, 77, 70, 96};
	int arrDistance[4] = {249, 1362, 1127, 1011};
	int distanceTravelled;
	int nbWaysToBeatRecord;
	int output = 1;

	for (int r=0; r<nbRaces; ++r)
	{
		nbWaysToBeatRecord = 0;
		for (int holdTime=0; holdTime<(arrTime[r]+1); ++holdTime)
		{
			distanceTravelled = holdTime * (arrTime[r]-holdTime);

			if (distanceTravelled > arrDistance[r])
			{
				nbWaysToBeatRecord += 1;
			}
		}
		output *= nbWaysToBeatRecord;
	}

	printf("Output: %i\n", output);

	clock_t endTime = clock();
	double executionLength = (double)(endTime - beginTime) / CLOCKS_PER_SEC * 1000;
	printf("Execution complete in %f ms.\n", executionLength);

	printf("Execution complete.\n");
	return 0;
}
