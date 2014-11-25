#ifndef PLAYER_H_
#define PLAYER_H_
#include <stdio.h>
#include <stdlib.h>
#include "hand.h"
#include "deck.h"
#include "card.h"


double Score_expectation(Deck d, Hand h, int* discard);
int* Discard_card(int x);
int* Optimal_play(Hand h);
int* Discard_cards_automated(int x);

#endif
