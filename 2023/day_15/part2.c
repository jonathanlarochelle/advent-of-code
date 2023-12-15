#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define LINE_BUFFER_LENGTH	(unsigned int) 22885
#define ASCII_DIGIT_OFFSET	(unsigned int) 48
#define BOX_SIZE (unsigned int)	20
#define LABEL_LENGTH (unsigned int) 6

struct s_lens {
	char label[LABEL_LENGTH];
	int focalLength;
};

int main(void)
{
	printf("Advent of Code 2023\n");
	printf("Day 15, part 2\n");

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
	struct s_lens *boxes[256][BOX_SIZE] = { 0 };
	char currentLabel[LABEL_LENGTH];
	struct s_lens *p_lens;

	int currentHash = 0;

	fgets(line, LINE_BUFFER_LENGTH, pInput);

	/* All labels point to a unique box.
	 * This means: one label can only ever be in one box.
	 * The presence of the - operation indicates that we will always have only one of each label in a given box.
	 * To this label will be attached a position and a focal length. */

	/* Initialize label */
	for (int c=0; c<LABEL_LENGTH; ++c)
	{
		currentLabel[c] = ' ';
	}

	bool foundLabel;
	bool moveLensToLeft;

	int l = 0;
	for (int i=0; i<LINE_BUFFER_LENGTH; ++i)
	{
		if (line[i]==',' || line[i]=='\n')
		{
			/* End of current step */
			/*
			printf("Step end state:\n");
			for (int b=0; b<256; ++b)
			{
				for (int slot=0; slot<BOX_SIZE; ++slot)
				{
					if (boxes[b][slot]==0)
					{
						break;
					}
					for (int c=0; c<LABEL_LENGTH; ++c)
					{
						printf("%c", boxes[b][slot]->label[c]);
					}
					printf(": box %i, slot %i, focal length %i\n", b, slot, boxes[b][slot]->focalLength);
				}
			}
			*/
			l = 0;
			currentHash = 0;
			for (int c=0; c<LABEL_LENGTH; ++c)
			{
				currentLabel[c] = ' ';
			}
		}
		else if (line[i]=='-')
		{
			/* Remove lens from box (if it is present) */
			moveLensToLeft = false;
			for (int slot=0; slot<BOX_SIZE; ++slot)
			{
				if (boxes[currentHash][slot]==0)
				{
					/* Nothing in the slot */
					break;
				}
				else
				{
					/* First possibility: we are still looking for our lens */
					if (!moveLensToLeft)
					{
						foundLabel = true;
						for (int c=0; c<LABEL_LENGTH; ++c)
						{
							if (boxes[currentHash][slot]->label[c] != currentLabel[c])
							{
								foundLabel = false;
							}
						}

						if (foundLabel)
						{
							/* Found it, now remove it. */
							free(boxes[currentHash][slot]);
							boxes[currentHash][slot] = 0;
							moveLensToLeft = true;
						}
					}
					/* Second possibility: lens was removed, now we move other lens to the left */
					else
					{
						boxes[currentHash][slot-1] = boxes[currentHash][slot];
						boxes[currentHash][slot] = 0;
					}
				}
			}
		}
		else if (line[i]=='=')
		{
			/* Add lens to box */
			p_lens = malloc(sizeof(struct s_lens));
			p_lens->focalLength = (int) line[i+1] - ASCII_DIGIT_OFFSET;
			for (int c=0; c<LABEL_LENGTH; ++c)
			{
				p_lens->label[c] = currentLabel[c];
			}

			for (int slot=0; slot<BOX_SIZE; ++slot)
			{

				if (boxes[currentHash][slot]==0)
				{
					/* Slot is free */
					boxes[currentHash][slot] = p_lens;

					i += 1;
					break;
				}

				foundLabel = true;
				for (int c=0; c<LABEL_LENGTH; ++c)
				{
					if (boxes[currentHash][slot]->label[c] != p_lens->label[c])
					{
						foundLabel = false;
					}
				}

				if (foundLabel)
				{
					/* Found it, replace the focal length. */
					free(boxes[currentHash][slot]);
					boxes[currentHash][slot] = p_lens;
					break;
				}
			}

		}
		else
		{
			/* Process char */
			currentLabel[l] = line[i];
			l += 1;
			currentHash += (int) line[i];
			currentHash *= 17;
			currentHash %= 256;
		}
	}

	/* Go through the boxes and compute the score */
	printf("Final stage:\n");
	for (int b=0; b<256; ++b)
	{
		for (int slot=0; slot<BOX_SIZE; ++slot)
		{
			if (boxes[b][slot]==0)
			{
				break;
			}
			for (int c=0; c<LABEL_LENGTH; ++c)
			{
				printf("%c", boxes[b][slot]->label[c]);
			}
			printf(": box %i, slot %i, focal length %i\n", b, slot, boxes[b][slot]->focalLength);
			output += (b+1) * (slot+1) * boxes[b][slot]->focalLength;
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
