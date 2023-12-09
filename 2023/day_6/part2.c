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
	printf("Day 6, part 2\n");

	clock_t beginTime = clock();

	/* Since the input is quite simple, we do not program a parser. */
	int64_t time = 41777096;
	int64_t distance = 249136211271011;
	int64_t distanceTravelled;
	int nbWaysToBeatRecord = 0;

	for (int holdTime=0; holdTime<(time+1); ++holdTime)
	{
		distanceTravelled = holdTime * (time-holdTime);

		if (distanceTravelled > distance)
		{
			nbWaysToBeatRecord += 1;
		}
	}

	printf("Output: %i\n", nbWaysToBeatRecord);

	clock_t endTime = clock();
	double executionLength = (double)(endTime - beginTime) / CLOCKS_PER_SEC * 1000;
	printf("Execution complete in %f ms.\n", executionLength);

	printf("Execution complete.\n");
	return 0;
}
