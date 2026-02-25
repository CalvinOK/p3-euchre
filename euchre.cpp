#include <cassert>
#include <iostream>
#include <array>
#include "Pack.hpp"
#include "Player.hpp"
#include "Card.hpp"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Game {
private:
    Player player();
    vector<Player> players;
    int pointsReq;
    Pack pack;
    void add_player_cards(int count, Player* player);
public:
    Game(fstream cardIn, bool shuffleBool, int pointsNeeded, string p1Name,
        string p1Type, string p2Name, string p2Type, string p3Name,
        string p3Type, string p4Name, string p4Type);
    void play();
    void shuffle();
    void deal();
    void make_trump(/* ... */);
    void play_hand(/* ... */);
    void delete_players();
};

// ./euchre.exe pack.in noshuffle 1 Adi Simple Barbara Simple Chi-Chih Simple Dabbala Simple

void Game::shuffle(){
    pack.shuffle();
}

void Game::add_player_cards(int c, Player* p){
    for (int i = 0; i < c; ++i){
        p->add_card(pack.deal_one());
    }
}

void Game::deal(){
    //first round
    add_player_cards(3, &players[1]);
    add_player_cards(2, &players[2]);
    add_player_cards(3, &players[3]);
    add_player_cards(2, &players[0]);

    //second round
    add_player_cards(2, &players[1]);
    add_player_cards(3, &players[2]);
    add_player_cards(2, &players[3]);
    add_player_cards(3, &players[0]);
}

void Game::delete_players(){
    //deletes players after game
    for (size_t i = 0; i < players.size(); ++i) {
        delete &players[i];
    }
}

int main(int argc, char *argv[]) {
    string packIn = argv[1];
    string shuffleBool = argv[2];
    int pointsIn = stoi(argv[3]);
    string p1_Name = argv[4];
    string p1_Type = argv[5];
    string p2_Name = argv[6];
    string p2_Type = argv[7];
    string p3_Name = argv[8];
    string p3_Type = argv[9];
    string p4_Name = argv[10];
    string p4_Type = argv[11];

// There are exactly 12 arguments, including the executable name.
// Points to win the game is between 1 and 100, inclusive.
// The shuffle argument is either shuffle or noshuffle.
// The types of each of the players are either Simple or Human.

    //check for errors
    if(argc != 12 || pointsIn>100 || pointsIn<1 || (shuffleBool != "shuffle"
            ||shuffleBool != "noshuffle") || (p1_Type != "Simple"|| p1_Type != "Human")
            || (p2_Type != "Simple"|| p2_Type != "Human") || (p3_Type != "Simple"|| p3_Type != "Human")
            || (p4_Type != "Simple"|| p4_Type != "Human")){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }

    //verify opens pack correctly
    ifstream fin;
    fin.open(packIn);
    if (!fin.is_open()){
        // Assume pack_filename is a variable containing
        // the specified pack filename from argv
        cout << "Error opening " << packIn << endl;
        return 1;
    }
}

// class League {
// private:
//   // TODO: Add member variables here
//   Trainer trainer;
//   vector<Trainer> gym_leaders;
//   size_t matches_won;
//   vector<string> defeated;
  
// public:
//   // TODO: Add constructor here to initialize members
//   League(ifstream* a_in, ifstream* i_in) : trainer (Trainer("ash")){
//     string ash_word;
//     string indigo_word;
//     Trainer ash(*a_in);
//     this->trainer = ash;
//     int gymNumber;
//     string junk;
//     *i_in >> gymNumber >> junk;
//     this->matches_won = 0;
//     for (int i=0 ; i << gymNumber; i++ ){
//       Trainer t (*i_in);
//       this->gym_leaders.push_back(t);
//     }
//   }

//   // TODO: Add member functions here
//   void battle(Trainer* t1, Trainer* t2){
//     cout << "-----" << t1->get_name() << " vs. " << t2->get_name() << "-----" << endl;
//     size_t t1_score{0};
//     size_t t2_score{0};
//     for (size_t i{0}; i < 5; ++i) {
//       Pokemon t2_chosen= t2->choose_pokemon();
//       Pokemon t1_chosen = t1->choose_pokemon(t2_chosen.get_type());
      
//       cout << t2->get_name() << " chooses " << t2_chosen << endl;
//       cout << t1->get_name() << " chooses " << t1_chosen << endl;
      
//       if (Pokemon_battle(t1_chosen, t2_chosen)){
//         cout << t1_chosen << " defeats " << t2_chosen << endl << endl;
//         ++t1_score;
//       }
//       else {
//         cout << t2_chosen << " defeats " << t1_chosen << endl << endl;
//         ++t2_score;
//       }
//     }
    
//     cout << "Result: " << t1->get_name() << "=" << t1_score << ", " << t2->get_name() << "=" << t2_score << endl;
    
//     if (t1_score == 5 || t2_score == 5){
//       cout << "It's a clean sweep!" << endl << endl;
//     }
//     else
//       cout << endl;
    
//     if (t1_score > t2_score) {
//       set_matches_won();
//       add_defeated(t2->get_name());
//     }
//   }

// //   Brock chooses Vulpix 85 Fire
// // Ash chooses Blastoise 73 Water
// // Vulpix 85 Fire defeats Blastoise 73 Water

//   size_t num_trainers (){
//     return gym_leaders.size();
//   }

//   Trainer* get_trainer(int i){
//     return &gym_leaders[i];
//   }
  
//   Trainer* get_trainer(){
//     return &trainer;
//   }

//   void set_matches_won(){this->matches_won = this->matches_won + 1;}

//   size_t get_matches_won(){return this->matches_won;}

//   void add_defeated(string name){this->defeated.push_back(name);}

//   ~League() {
//     // TODO: put code here to clean up by deleting all Trainer objects
//   }
// };

// int main(int argc, char *argv[]) {

//   // TODO: Add code to read command line args and open file streams here
  
//   string ash_file = argv[1];
//   string indigo_file = argv[2];
//   ifstream ash_in(ash_file);
//   ifstream indigo_in(indigo_file);

//   if (!ash_in.is_open() || !indigo_in.is_open()) {
//     cout << "file didn't read" << endl;
//     return 0;
//   }
  
//   League Indigo (&ash_in, &indigo_in);

//   for (size_t i = 0; i < Indigo.num_trainers(); i++){
//     Indigo.battle(Indigo.get_trainer(),Indigo.get_trainer(i));
//   }
//   // Ash won 6 matches by defeating:
//   // Brock
//   // Misty
//   // Surge
//   // Erika
//   // Koga
//   // Giovanni

//   cout << "Ash won" ;

//   // TODO: Create a League object, call function to run the simulation
  

  
// }