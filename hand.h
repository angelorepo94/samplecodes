#ifndef HAND_H_
#define HAND_H_
#include "card.h"
#include "deck.h"
#define HANDSIZE 5

struct hand{
        Card Card_in_hand[HANDSIZE];
        int size;
        int user;
        double score;
};

typedef struct hand* Hand;

Hand Hand_init(int user);
int Hand_display(Hand h);
int Card_swap(Hand h, int i, int j);
int Card_sort(Hand h);
double Score(Hand h);
Card Flush(Hand h);
Card Straight(Hand h);
Card Straightflush(Hand h);
int* Fourofakind(Hand h);
int* Threeofakind(Hand h);
Card Pair(Hand h);
Card Twopairs(Hand h);

#endif
