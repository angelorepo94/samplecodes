#include <stdio.h>
#include <stdlib.h>
#include "hand.h"
#include "card.h"
#include "deck.h"

double Score(Hand h){
        double score = 0;

        Card best_combo = NULL;
        int* best_face = NULL;
	Card_sort(h);

        if((best_combo = Straightflush(h)) &&
	   Straightflush(h) != NULL)

                score = 9 + (best_combo->card_face) + best_combo->card_suit;

        else if((best_face = Fourofakind(h)) &&
		Fourofakind(h) != NULL)

                score = 8 + *best_face;

	else if((best_combo = Flush(h)) &&
		Flush(h) != NULL)
                
score = 6 + best_combo->card_face + best_combo->card_suit;
        
	else if((best_combo = Straight(h))&&
		Straight(h) != NULL)
                score = 5 + best_combo->card_face + best_combo->card_suit;
        
	else if((best_face = Threeofakind(h)) &&
		Threeofakind(h) != NULL)
                score = 4 + *best_face;
        
	else if( (best_combo = Twopairs(h)) &&
		 Twopairs(h) != NULL)
                score = 3 + best_combo->card_face + best_combo->card_suit;
        
	else if( (best_combo = Pair(h))&&
		 Pair(h) != NULL)
                score = 2 + best_combo->card_face + best_combo->card_suit;
        
	else{
                best_combo = h->Card_in_hand[4];
                score = 1 + best_combo->card_face + best_combo->card_suit;
        }
        return score;
}

Hand Hand_init(int user){
        Hand h = (Hand)malloc(sizeof(struct hand));
        int x;
        for(x=0; x<HANDSIZE; x++){
                h->Card_in_hand[x]= (Card)malloc(sizeof(struct card));
        }
        h->user = user;
        h->size = 0;
        h->score = 0;
        return h;
}

int Hand_display(Hand h){
        int x;
        for(x=0; x < HANDSIZE; x++)
                Card_display(h->Card_in_hand[x]);
        return 0;
}

int Card_swap(Hand h, int x, int y){
        Card tmp;
        tmp = h->Card_in_hand[x];
        h->Card_in_hand[x] = h->Card_in_hand[y];
        h->Card_in_hand[y] = tmp;
        return 0;
}

int Card_sort(Hand h){
        int x, y;
        for(x=0; x < HANDSIZE-1; x++){
                for(y=x+1; y<HANDSIZE; y++){
                        if(Face_comparator(h->Card_in_hand[x], h->Card_in_hand[y]) == 1){
                                Card_swap(h,x,y);
                        }}}
                     
        return 0;
}

Card Flush(Hand h){
        int i;
        Card c = NULL;
        Card_sort(h);
        for(i=0; i < HANDSIZE-1; i++){
                if(Suit_comparator(h->Card_in_hand[i],h->Card_in_hand[i+1]) != 0)
                        return c;
        }
        c = h->Card_in_hand[0];
        return c;
}


Card Straight(Hand h){
        Card c = NULL;
        Card_sort(h);
        if (h->Card_in_hand[0]->card_face == TWO && h->Card_in_hand[1]->card_face == THREE
                        && h->Card_in_hand[2]->card_face == FOUR && h->Card_in_hand[3]->card_face == FIVE
                        && h->Card_in_hand[4]->card_face == ACE)
                c = h->Card_in_hand[0];
        int i;
        for(i=0; i < HANDSIZE-1; i++){
                if(h->Card_in_hand[i+1]->card_face - h->Card_in_hand[i]->card_face != 1)
                        return NULL;
        }
        c = h->Card_in_hand[0];
        return c;
}

Card Straightflush(Hand h){
        Card c = NULL;
        if(Flush(h) != NULL && Straight(h) != NULL )
                c = h->Card_in_hand[0];
        return c;
}

int* Fourofakind(Hand h){
        int i;
        int* face_counter = (int*)malloc(sizeof(int));
	for(i=0;i<13;i++) 
	  face_counter[i] = 0;
        for(i=0;i<HANDSIZE;i++){
          face_counter[h->Card_in_hand[i]->card_face]++;
        }
        for(i=0;i<13;i++){
                if(face_counter[i] == 4){
                        *face_counter = i;
                        return face_counter;
                }
        }
        return NULL;
}

int* Threeofakind(Hand h){
        int i;
        int* face_counter = (int*) malloc(sizeof(int));
     	for(i=0;i<13;i++) 
	  face_counter[i] = 0;
        for(i=0;i<HANDSIZE;i++){
          face_counter[h->Card_in_hand[i]->card_face]++;
        }
        for (i = 0; i < 13; i++) {
                if (face_counter[i] == 3) {
                        *face_counter = i;
                        return face_counter;
                }
        }
        return NULL;
}



Card Pair(Hand h){
        int i;
        int counter = 0;
        Card c = (Card) malloc(sizeof(Card));
	int* face_counter = (int*) malloc(sizeof(int));
     	for(i=0;i<13;i++) 
	  face_counter[i] = 0;
        for(i=0;i<HANDSIZE;i++){
          face_counter[h->Card_in_hand[i]->card_face]++;
        }
       
        for (i = 0; i < 13; i++) {
                if (face_counter[i] == 2) {
                        counter++;
                        c->card_face = i;
                }
        }
        c->card_suit = DIAMONDS;
        if(counter == 1){
                for(i=0;i < HANDSIZE;i++){
                        if(h->Card_in_hand[i]->card_face == c->card_face && h->Card_in_hand[i]->card_suit > c->card_suit )
                                c->card_suit = h->Card_in_hand[i]->card_suit;
                }
                return c;
        }
        return NULL;
}

Card Twopairs(Hand h){
        int i;
        int counter = 0;
        Card c = (Card) malloc(sizeof(Card));
int* face_counter = (int*) malloc(sizeof(int));
     	for(i=0;i<13;i++) 
	  face_counter[i] = 0;
        for(i=0 ;i < HANDSIZE ;i++){
          face_counter[h->Card_in_hand[i]->card_face]++;
        }
       
        for (i = 0; i < 13; i++) {
                if (face_counter[i] == 2) {
                        counter++;
                        c->card_face = i;
                }
        }
        c->card_suit = HEARTS;
        if(counter == 2){
                for(i=0;i<HANDSIZE;i++){
                        if(h->Card_in_hand[i]->card_face == c->card_face && h->Card_in_hand[i]->card_suit > c->card_suit )
                                c->card_suit = h->Card_in_hand[i]->card_suit;
                }
                return c;
        }
        return NULL;
}
