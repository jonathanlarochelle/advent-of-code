#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define LINE_BUFFER_LENGTH	(unsigned int) 11+1
#define NB_LINES			(unsigned int)	1000
#define ASCII_DIGIT_OFFSET	(unsigned int) 48
#define NB_CARDS (unsigned int) 5

enum e_handType{
	HIGH_CARD,
	ONE_PAIR,
	TWO_PAIR,
	THREE_OF_A_KIND,
	FULL_HOUSE,
	FOUR_OF_A_KIND,
	FIVE_OF_A_KIND
};

struct s_hand{
	char cards[NB_CARDS];
	int bid;
	enum e_handType handType;
};

enum e_handType getHandType(char cards[NB_CARDS])
{
	enum e_handType ht;

	if (cards[0]==cards[1] && cards[0]==cards[2] && cards[0]==cards[3] && cards[0]==cards[4])
	{
		ht = FIVE_OF_A_KIND;
	}
	else if ((cards[0]==cards[1] && cards[0]==cards[2] && cards[0]==cards[3]) ||
			(cards[0]==cards[1] && cards[0]==cards[2] && cards[0]==cards[4]) ||
			(cards[0]==cards[1] && cards[0]==cards[3] && cards[0]==cards[4]) ||
			(cards[0]==cards[2] && cards[0]==cards[3] && cards[0]==cards[4]) ||
			(cards[1]==cards[2] && cards[1]==cards[3] && cards[1]==cards[4]))
	{
		ht = FOUR_OF_A_KIND;
	}
	else if ((cards[0]==cards[1] && cards[0]==cards[2] && cards[3]==cards[4]) ||
			(cards[0]==cards[1] && cards[0]==cards[3] && cards[2]==cards[4]) ||
			(cards[0]==cards[3] && cards[0]==cards[2] && cards[1]==cards[4]) ||
			(cards[3]==cards[1] && cards[3]==cards[2] && cards[0]==cards[4]) ||
			(cards[0]==cards[1] && cards[0]==cards[4] && cards[2]==cards[3]) ||
			(cards[0]==cards[2] && cards[0]==cards[4] && cards[1]==cards[3]) ||
			(cards[2]==cards[1] && cards[2]==cards[4] && cards[0]==cards[3]) ||
			(cards[0]==cards[3] && cards[0]==cards[4] && cards[1]==cards[2]) ||
			(cards[1]==cards[3] && cards[1]==cards[4] && cards[0]==cards[2]) ||
			(cards[2]==cards[3] && cards[2]==cards[4] && cards[0]==cards[1]))
	{
		ht = FULL_HOUSE;
	}
	else if ((cards[0]==cards[1] && cards[0]==cards[2]) ||
			(cards[0]==cards[1] && cards[0]==cards[3]) ||
			(cards[0]==cards[3] && cards[0]==cards[2]) ||
			(cards[3]==cards[1] && cards[3]==cards[2]) ||
			(cards[0]==cards[1] && cards[0]==cards[4]) ||
			(cards[0]==cards[2] && cards[0]==cards[4]) ||
			(cards[2]==cards[1] && cards[2]==cards[4]) ||
			(cards[0]==cards[3] && cards[0]==cards[4]) ||
			(cards[1]==cards[3] && cards[1]==cards[4]) ||
			(cards[2]==cards[3] && cards[2]==cards[4]))
	{
		ht = THREE_OF_A_KIND;
	}
	else if ((cards[1]==cards[2] && cards[3]==cards[4]) ||
			(cards[1]==cards[3] && cards[2]==cards[4]) ||
			(cards[1]==cards[4] && cards[2]==cards[3]) ||
			(cards[0]==cards[2] && cards[3]==cards[4]) ||
			(cards[0]==cards[3] && cards[2]==cards[4]) ||
			(cards[0]==cards[4] && cards[2]==cards[3]) ||
			(cards[0]==cards[1] && cards[3]==cards[4]) ||
			(cards[0]==cards[3] && cards[1]==cards[4]) ||
			(cards[0]==cards[4] && cards[1]==cards[3]) ||
			(cards[0]==cards[1] && cards[2]==cards[4]) ||
			(cards[0]==cards[2] && cards[1]==cards[4]) ||
			(cards[0]==cards[4] && cards[1]==cards[2]) ||
			(cards[0]==cards[1] && cards[2]==cards[3]) ||
			(cards[0]==cards[2] && cards[1]==cards[3]) ||
			(cards[0]==cards[3] && cards[1]==cards[2]))
	{
		ht = TWO_PAIR;
	}
	else if (cards[0]==cards[1] || cards[0]==cards[2] || cards[0]==cards[3] || cards[0]==cards[4] ||
			cards[1]==cards[2] || cards[1]==cards[3] || cards[1]==cards[4] ||
			cards[2]==cards[3] || cards[2]==cards[4] ||
			cards[3]==cards[4])
	{
		ht = ONE_PAIR;
	}
	else if (cards[0]!=cards[1] && cards[0]!=cards[2] && cards[0]!=cards[3] && cards[0]!=cards[4] &&
			cards[1]!=cards[2] && cards[1]!=cards[3] && cards[1]!=cards[4] &&
			cards[2]!=cards[3] && cards[2]!=cards[4] &&
			cards[3]!=cards[4])
	{
		ht = HIGH_CARD;
	}
	else
	{
		getchar();
		ht = HIGH_CARD;
	}

	return ht;
}

int getCardStrength(char card)
{
	int str;
	switch (card)
	{
	case '2':
		str=2;
		break;
	case '3':
		str=3;
		break;
	case '4':
		str=4;
		break;
	case '5':
		str=5;
		break;
	case '6':
		str=6;
		break;
	case '7':
		str=7;
		break;
	case '8':
		str=8;
		break;
	case '9':
		str=9;
		break;
	case 'T':
		str=10;
		break;
	case 'J':
		str=11;
		break;
	case 'Q':
		str=12;
		break;
	case 'K':
		str=13;
		break;
	case 'A':
		str=14;
		break;
	default:
		getchar();
	}
	return str;
}

int main(void)
{
	printf("Advent of Code 2023\n");
	printf("Day 7, part 1\n");

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
	struct s_hand *hands[NB_LINES] = { 0 };
	struct s_hand *p_newHand;
	bool newHandIsBetter;

	for (int l=0; l<NB_LINES; ++l)
	{
		for (int i=0; i<LINE_BUFFER_LENGTH; ++i)
		{
			line[i] = ' ';
		}
		fgets(line, LINE_BUFFER_LENGTH, pInput);

		/* Parse new hand */
		p_newHand = malloc(sizeof(struct s_hand));
		for (int c=0; c<NB_CARDS; ++c)
		{
			p_newHand->cards[c] = line[c];
		}
		p_newHand->bid = atoi(&line[6]);
		p_newHand->handType = getHandType(p_newHand->cards);

		/* Compare with previous hands */
		newHandIsBetter = false;
		for (int h=0; h<l+1; ++h)
		{
			if (hands[h]==0)
			{
				hands[h] = p_newHand;
			}
			else if (p_newHand->handType > hands[h]->handType)
			{
				newHandIsBetter = true;
			}
			else if (p_newHand->handType == hands[h]->handType)
			{
				for (int c=0; c<NB_CARDS; ++c)
				{
					if (getCardStrength(p_newHand->cards[c])>getCardStrength(hands[h]->cards[c]))
					{
						newHandIsBetter = true;
						break;
					}
					else if (getCardStrength(p_newHand->cards[c])<getCardStrength(hands[h]->cards[c]))
					{
						break;
					}
				}
			}

			if (newHandIsBetter)
			{
				/* New hand is better, place it here and bump the next ones */
				for (int hh=l; hh>h; --hh)
				{
					hands[hh] = hands[hh-1];
				}
				hands[h] = p_newHand;
				break;
			}
		}

		/* Show hands */
		/*
		printf("Hand in progress: \n");
		for (int h=0; h<l+1; ++h)
		{
			for (int c=0; c<NB_CARDS; ++c)
			{
				printf("%c", hands[h]->cards[c]);
			}
			printf(" %i %i\n", hands[h]->bid, hands[h]->handType);
		}
		*/
	}

	/* Compute scores */
	for (int h=0; h<NB_LINES; ++h)
	{
		printf("%i: ", h+1);
		for (int c=0; c<NB_CARDS; ++c)
		{
			printf("%c", hands[h]->cards[c]);
		}
		output += (NB_LINES-h) * hands[h]->bid;
		printf("; type=%i; bid=%i; winnings=%i; new output=%i\n",
				hands[h]->handType, hands[h]->bid, (NB_LINES-h) * hands[h]->bid, output);
		//printf("%i\n", hands[h]->bid);
		//getchar();
	}

	printf("Output: %i\n", output);

	clock_t endTime = clock();
	double executionLength = (double)(endTime - beginTime) / CLOCKS_PER_SEC * 1000;
	printf("Execution complete in %f ms.\n", executionLength);

	fclose(pInput);
	printf("Execution complete.\n");
	return 0;
}
