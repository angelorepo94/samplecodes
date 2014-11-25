#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "card.h"
#include "deck.h"

Deck Deck_init(){

        int x,y;
        Deck d = (Deck)malloc(sizeof(Deck));
        d->cards = (Card*)malloc(52*sizeof(Card));
      

        for( x = 0; x < 4; x++ ){
                for( y = 0; y < 13; y++ ){
                        d->cards[ x * 13 + y] = (Card)malloc(sizeof(struct card));
                        d->cards[ x * 13 + y]->card_face = y;
                        d->cards[x * 13 + y]->card_suit = x;
                }
        }
        d->top = 0;
        d->bottom = 51;
        d->deck_size = 52;

        return d;
}

int Deck_shuffle(Deck d){

        int swaps = 52;
        srand(time(NULL));
        Card tmp;
        while( swaps != 0 ){
                int random_card1 = rand()%52;
                int random_card2 = rand()%52;
                tmp = d->cards[random_card1];
                d->cards[random_card1] = d->cards[random_card2];
                d->cards[random_card2] = tmp;
                swaps = swaps - 1;
        }
        return 0;
}

Card Card_draw(Deck d){
        Card drawCard = (Card)malloc(sizeof(struct card));
        drawCard->card_face = d->cards[d->top]->card_face;
        drawCard->card_suit = d->cards[d->top]->card_suit;
        d->cards[d->top] = NULL;
        d->top = (d->top+1)%52;
        d->deck_size--;
        return drawCard;
}

int Card_replace(Deck d, Card c){
;
        d->bottom++;
        d->bottom = d->bottom%52;
        d->cards[d->bottom] = (Card)malloc(sizeof(struct card));
        d->cards[d->bottom]->card_face = c->card_face;

        d->cards[d->bottom]->card_suit = c->card_suit;
        d->deck_size++;

        return 0;
}

int Deck_display(Deck d){
        
        int i;
        printf("size is %d\n", d->deck_size);

        for( i = d->top; i < d->deck_size + d->top; i++){
                Card_display(d->cards[i%52]);
                printf("%d ",i);
        }
        return 0;
}

int Card_remove(Deck d, Card c){
      
        int x;
        int y = 51;
        Card tmp;
        for(x = 0;x < 52;x++){
                Card_display(d->cards[x]);
                if(Card_match(c, d->cards[x]) == 0){
                        tmp = d->cards[x];
                        d->cards[x] = d->cards[y];
                        d->cards[y] = tmp;
                        d->cards[y] = NULL;
                        y--;
                        d->deck_size--;
                        d->bottom = y;
                }
        }
        return 0;
}
