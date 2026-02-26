#include <cassert>
#include <iostream>
#include <array>
#include "Pack.hpp"
#include "Card.hpp"
#include "Player.hpp"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class SimplePlayer: public Player{
public:

  //create SimplePlayer
  SimplePlayer(){
    playerName = "";
  }

  SimplePlayer(string name){
    playerName = name;
  }

  //EFFECTS returns player's name
  virtual const std::string & get_name() const override {
    return playerName;
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  virtual void add_card(const Card &c) override {
    heldCards.push_back(c);
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  virtual bool make_trump(const Card &upcard, bool is_dealer,
                  int round, Suit &order_up_suit) const override{
    //count num cards with current order up suit for round one
    int count1 = 0;
    for (auto car : heldCards){
      if((car.is_face_or_ace() && car.is_trump(upcard.get_suit())) ||
      car.is_left_bower(upcard.get_suit())|| car.is_right_bower(upcard.get_suit())){
        count1 ++;
      }
    }
    //round one decision
    if(round == 1 && count1 >= 2){
      order_up_suit = upcard.get_suit();
      return true;
    }
    int count2 = 0;
    //counting num cards with next suit for round 2
    for (auto car : heldCards){
      if((car.is_face_or_ace() && car.is_trump(Suit_next(upcard.get_suit()))) ||
      car.is_left_bower(Suit_next(upcard.get_suit()))||
      car.is_right_bower(Suit_next(upcard.get_suit()))){
        count2 ++;
      } 
    }
    //round two decision
    if (round == 2 && count2 >=1){
      order_up_suit = Suit_next(upcard.get_suit());
      return true;
    }
    //screw the dealer
    if (round == 2 && is_dealer){
      order_up_suit = Suit_next(upcard.get_suit());
      return true;
    }
    return false;
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  virtual void add_and_discard(const Card &upcard) override {
    heldCards.push_back(upcard);
    sort(heldCards.begin(),heldCards.end());
    heldCards.erase(heldCards.begin());
  };

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  virtual Card lead_card(Suit trump) override {
    vector <int> notTrumps;
    Card finalCard;
    sort(heldCards.begin(),heldCards.end());
    //find locations of not trump card
    for (size_t i = 0; i <heldCards.size(); ++i){
      if(!heldCards[i].is_trump(trump)){
        notTrumps.push_back(i);
      }
    }
    //if only trump cards
    if(notTrumps.size() == 0){
      finalCard = heldCards[heldCards.size()-1];
      heldCards.erase(heldCards.end()-1);
      return finalCard;
    }
    //if not only trump cards
    finalCard = heldCards[notTrumps[notTrumps.size()-1]];
    heldCards.erase(heldCards.begin() + notTrumps[notTrumps.size()-1]);
    return finalCard;
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  virtual Card play_card(const Card &led_card, Suit trump) override {
    vector<int> locations;
    sort(heldCards.begin(),heldCards.end());
    int finalloc = 0;
    Card finalCard = heldCards[0];
    //find all of the ones that follow the suit
    for (int loc = 0; loc < heldCards.size(); ++loc){
      if (heldCards[loc].get_suit() == led_card.get_suit()){
        locations.push_back(loc);
      }
    }
    //if no suits, play lowest
    if(locations.size()== 0){
      finalCard = heldCards[0];
      heldCards.erase(heldCards.begin());
      return finalCard;
    }
    //if has suits, play highest
    finalloc = locations[locations.size()-1];
    finalCard = heldCards[finalloc];
    heldCards.erase(heldCards.begin() + finalloc);
    return finalCard;
  }

  virtual bool get_human() const override{
    return b_human;
  }

  void print_cards() const override{
    for (int i = 0; i < heldCards.size(); ++i){
      cout << "Simple player " << get_name() << "'s hand: [" << i << "] "
      << heldCards[i] << endl;
    }
    cout << "Simple player " <<get_name() << ", please enter a suit, or \"pass\":" << endl;
};


private:
  string playerName;
  vector<Card> heldCards;
  bool b_human = false;
};

class Human: public Player{
  public:
  //create Human
  Human(){
    playerName = "";
  }

  Human(string name){
    playerName = name;
  }

  //EFFECTS returns player's name
  virtual const std::string & get_name() const override{
    return playerName;
  };

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  virtual void add_card(const Card &c) override{
    heldCards.push_back(c);
    sort(heldCards.begin(), heldCards.end());
  };

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  virtual bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const override {
    print_cards();
    cout << "Human player " << playerName << ", please enter a suit, or \"pass\":\n";
    string decision;
    cin >> decision;

    if (decision != "pass") {
      Suit ordered_up = string_to_suit(decision);
      order_up_suit = ordered_up;
      return true;
    }
    else {
      return false;
    }
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  virtual void add_and_discard(const Card &upcard) override {
    sort(heldCards.begin(), heldCards.end());
    print_cards();
    cout << "Discard upcard: [-1]\n";
    cout << "Human player " << playerName << ", please select a card to discard:\n";
    string decision;
    cin >> decision;
    //remove specific card
    if (stoi(decision) != -1) {
      heldCards.erase(heldCards.begin() + stoi(decision));
      add_card(upcard);
    }
    //no change if wanted to remove upcard
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  virtual Card lead_card(Suit trump) override {
    sort(heldCards.begin(), heldCards.end());
    print_cards();
    cout << "Human player " << playerName << ", please select a card:\n";
    string decision;
    cin >> decision;
    Card finalCard = heldCards[stoi(decision)];
    heldCards.erase(heldCards.begin() + stoi(decision));
    return finalCard;
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  virtual Card play_card(const Card &led_card, Suit trump) override {
    sort(heldCards.begin(), heldCards.end());
    print_cards();
    cout << "Human player " << playerName << ", please select a card:\n";
    string decision;
    cin >> decision;
    Card finalCard = heldCards[stoi(decision)];
    heldCards.erase(heldCards.begin() + stoi(decision));
    return finalCard;
  }

  virtual bool get_human() const override{
    return b_human;
  }

  // Human player Judea's hand: [0] Nine of Spades
  // Human player Judea's hand: [1] Ten of Spades
  // Human player Judea's hand: [2] Jack of Spades
  // Human player Judea's hand: [3] King of Hearts
  // Human player Judea's hand: [4] Ace of Hearts
  // Human player Judea, please enter a suit, or "pass":
  void print_cards() const override{
    for (int i = 0; i < heldCards.size(); ++i){
      cout << "Human player " << get_name() << "'s hand: [" << i << "] "
      << heldCards[i].get_rank() << " of " << heldCards[i].get_suit() << endl;
    }
  };

private:
  string playerName;
  vector<Card> heldCards;
  bool b_human = true;
};

Player * Player_factory(const std::string &name, const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  // Repeat for each other type of Player
  if (strategy == "Human") {
    // The "new" keyword dynamically allocates an object.
    return new Human(name);
  }
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  return os<<p.get_name();
}