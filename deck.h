#ifndef DECK_H_
#define DECK_H_
#include <stdio.h>
#include <stdlib.h>
#include "card.h"

struct deck{
        Card *cards;
        int top;
        int bottom;
        int deck_size;
};
typedef struct deck* Deck;

Deck Deck_init();
int Deck_shuffle( Deck d );
Card Card_draw( Deck d );
int Card_replace( Deck d, Card c );
int Deck_display( Deck d );
int Card_remove( Deck d, Card c );

#endif
