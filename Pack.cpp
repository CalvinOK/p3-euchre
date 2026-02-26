#include <cassert>
#include <iostream>
#include <array>
#include "Pack.hpp"
#include "Card.hpp"
#include <string>
#include <vector>

using namespace std;

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on. 
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
// NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(): next(0) {
    for (int r = NINE; r<=ACE; r++){
        for (int s = SPADES; s <= DIAMONDS; ++s) {
            cards.at((4 * (r - 7)) + s) = Card(Rank(r), Suit(s));
        }
    }
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
// NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(istream& pack_input): next(0){
    string rank;
    string junk;
    string suit;
    int i = 0;
    while(pack_input >> rank >> junk >> suit){
        cards.at(i) = Card(string_to_rank(rank), string_to_suit(suit));
        ++i;
    }

    next = 0;
};

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one(){
    int currCard = next;
    ++next;
    return(cards[currCard]);
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset(){
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle(){
    std::array <Card, PACK_SIZE/2> first;
    std::array <Card, PACK_SIZE/2> second;
    for(int j=0; j<7; ++j){
        for (int i = 0; i < cards.size()/2; i++){
            first.at(i) = cards.at(i);
        }
        for (int k=cards.size()/2; k < cards.size(); k++){
            second.at(k-cards.size()/2) = cards.at(k);
        }
        for (int f=0; f< cards.size()/2 ; f++){
            cards.at(2*f) = second.at(f);
            cards.at(2*f+1) = first.at(f);
        }
    }
    reset();
}

// void Pack::sort(const Card &led_card, Suit trump){

// }

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const{
    return next >= (PACK_SIZE);
}