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
    vector<Player*> players;
    int pointsReq;
    int t1_score;
    int t2_score;
    bool sBool;
    Pack pack;
    void add_player_cards(int count, Player* player);
    Suit trump;
    Card upcard;
    int whoOrderedUp;
    vector <int> whoWon;
public:
    Game(ifstream* cardIn, bool shuffleBool, int pointsNeeded, string p1Name,
        string p1Type, string p2Name, string p2Type, string p3Name,
        string p3Type, string p4Name, string p4Type);
    void play();
    void shuffle();
    void deal();
    bool make_trump(int round);
    void play_hand(int starter);
    void delete_players();
    void reset_partial();
    void update_score();
};

// ./euchre.exe pack.in noshuffle 1 Adi Simple Barbara Simple Chi-Chih Simple Dabbala Simple

void Game::reset_partial(){
    whoWon.clear();
    pack.reset();
}

void Game::update_score(){
    int t1_wins = 0;
    int t2_wins = 0;
    for (int i=0; i < whoWon.size(); ++i){
        if (whoWon[i] == 0 || whoWon[i] == 2){
            ++t1_wins;
        } else{
            ++t2_wins;
        }
    }

    //first case "If the team that ordered up the trump suit takes 3 or 4 tricks, they get 1 point."
    if ((whoOrderedUp == 0 || whoOrderedUp == 2)&&(t1_wins==3 || t1_wins ==4)){
        t1_score++;
    } else if ((whoOrderedUp == 1 || whoOrderedUp == 3)&&(t2_wins==3 || t2_wins ==4)){
        t2_score++;
    }
    //second case "If the team that ordered up the trump suit takes all 5 tricks, they get 2 points. This is called a march."
    if ((whoOrderedUp == 0 || whoOrderedUp == 2)&&(t1_wins==5)){
        t1_score = t1_score+2;
    } else if ((whoOrderedUp == 1 || whoOrderedUp == 3)&&(t2_wins==5)){
        t2_score = t2_score+2;
    }
    //third case "If the team that did not order up takes 3, 4, or 5 tricks, they receive 2 points. This is called euchred."
    if (!(whoOrderedUp == 0 || whoOrderedUp == 2)&&(t1_wins>2)){
        t1_score = t1_score+2;
    } else if (!(whoOrderedUp == 1 || whoOrderedUp == 3)&&(t2_wins>2)){
        t2_score = t2_score+2;
    }
}

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
    add_player_cards(3, players[1]);
    add_player_cards(2, players[2]);
    add_player_cards(3, players[3]);
    add_player_cards(2, players[0]);

    //second round
    add_player_cards(2, players[1]);
    add_player_cards(3, players[2]);
    add_player_cards(2, players[3]);
    add_player_cards(3, players[0]);
}

bool Game::make_trump(int r){
    if(players[0]->make_trump(upcard, true,
                          r, trump)){
        whoOrderedUp = 0;
        return true;
    }
    if(players[1]->make_trump(upcard, false,
                          r, trump)){
        whoOrderedUp = 1;
        return true;
    }
    if(players[2]->make_trump(upcard, false,
                          r, trump)){
        whoOrderedUp = 2;
        return true;
    }
    if(players[3]->make_trump(upcard, false,
                          r, trump)){
        whoOrderedUp = 3;
        return true;
    }
    return false;
}

void Game::play_hand(int starter){
    //five rounds
    for (int i = 0; i < 5; ++i){
        Card lead;
        Card curComp;
        int curInd = starter;
        int endInd = starter;
        lead = players[curInd]->lead_card(trump);
        curComp = players[(curInd+1)%4]->play_card(lead, trump);
        if (lead< curComp){
            lead = curComp;
            endInd = (curInd+1)%4;
        }
        curComp = players[(curInd+2)%4]->play_card(lead, trump);
        if (lead<curComp){
            lead = curComp;
            endInd = (curInd+2)%4;
        }
        curComp = players[(curInd+3)%4]->play_card(lead, trump);
        if (lead< curComp){
            lead = curComp;
            endInd = (curInd+3)%4;
        }
        whoWon.push_back(endInd);
        curInd = endInd;
    }
}

void Game::delete_players(){
    //deletes players after game
    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }
}

Game::Game(ifstream* cardIn, bool shuffleBool, int pointsNeeded, string p1Name,
        string p1Type, string p2Name, string p2Type, string p3Name,
        string p3Type, string p4Name, string p4Type) {
    
    //inport pack
    Pack pack(*cardIn);

    //add points needed to win
    pointsReq = pointsNeeded;

    t1_score = 0;
    t2_score = 0;

    sBool = shuffleBool;

    //add players
    players.push_back(Player_factory(p1Name, p1Type));
    players.push_back(Player_factory(p2Name, p2Type));
    players.push_back(Player_factory(p3Name, p3Type));
    players.push_back(Player_factory(p4Name, p4Type));
}

void Game::play(){
    //resets pack and vectors used
    reset_partial();
    //shuffle if needed
    if (sBool){
        shuffle();
    }
    //deals out the cards
    deal();
    //pulls the upcard
    upcard = pack.deal_one();
    //make the trump and it returns false if everyone passes. Then runs r2
    if(!make_trump(1)){
        make_trump(2);
    }

    play_hand(1);

    update_score();

    if(t1_score > pointsReq || t2_score > pointsReq){
        delete_players();
        return;
    }else {
        play();
    }
    return;
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

//./euchre.exe pack.in noshuffle 1 Adi Simple Barbara Simple Chi-Chih Simple Dabbala Simple

    //check for errors
    if(argc != 12 || pointsIn>100 || pointsIn<1 || (shuffleBool != "shuffle"
            &&shuffleBool != "noshuffle") || (p1_Type != "Simple" && p1_Type != "Human")
            || (p2_Type != "Simple" && p2_Type != "Human") || (p3_Type != "Simple" && p3_Type != "Human")
            || (p4_Type != "Simple" && p4_Type != "Human")){
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

    bool sBool = false;
    if (shuffleBool == "shuffle"){
        sBool = true;
    }

    //play the game
    Game game(&fin, sBool, pointsIn, p1_Name, p1_Type, p2_Name, p2_Type, p3_Name,
        p3_Type, p4_Name, p4_Type);
    
    game.play();

}