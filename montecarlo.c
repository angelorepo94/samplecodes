#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "montecarlo.h"
#include "deck.h"
#include "hand.h"
#include "card.h"

/* Monte Carlo & Scoring */

double Score_expectation(Deck d, Hand h, int* discard){

   int i,j;
        Card* possCard = (Card*) malloc(HANDSIZE*sizeof(Card));
        Hand h2 = (Hand) malloc(HANDSIZE*sizeof(Hand));

        srand(time(NULL));
        int score = 0;

  for(i=0; i < 20; i++) {
           for (i = 0; i < HANDSIZE; i++) {
                        possCard[i] = d->cards[rand() % 52 - HANDSIZE];
                        memcpy(h,h2, sizeof(Hand));
                }
                for (j = 0; j < HANDSIZE; j++){
                        if(discard[j] == 1)

                                h2->Card_in_hand[j] = NULL;
                                h2->Card_in_hand[j] = possCard[j];
                }

                score = score + Score(h2);
                printf("Your current score is %d", score);
        }
        return score;
}

int* Discard_card(int x){
        int i;
        int* discard = (int*)malloc(HANDSIZE*sizeof(int));
        for(i = 0;i < HANDSIZE; i++)
          discard[i] = 0;
        while(x != 0){
                discard[x++] = x%2;
                x/=2;

        }
        return discard;
}

int* Optimal_play(Hand h){

        Deck d = Deck_init();

        int i, j, k;
        for (i = 0; i < HANDSIZE; i++)
               Card_remove(d, h->Card_in_hand[i]);

        int score[20];
        int maxscore = 0;
        int maxscorei = 0;
        int* discard;

        for(i=0;i<20;i++){
                discard = Discard_card(i);
                score[i] = Score_expectation(d, h, discard);
        }
        for(j=0;i<20;j++){
                if(score[j] > maxscore){
                        maxscore = score[j];
                        maxscorei = j;
                }
        }
        discard = Discard_card(maxscorei);
        return discard;
}

double Discard_card_automated(Deck d, Hand h){
        int* discard = Optimal_play(h);
        int x;
        for(x = 0;x < HANDSIZE; x++){
                if(discard[x] == 1){
                        Card_replace(d, h->Card_in_hand[x]);
                        h->Card_in_hand[x] = NULL;
                        h->Card_in_hand[x] = Card_draw(d);
                }
        }
        double score = Score(h);
        return score;
}
