#include <cassert>
#include <iostream>
#include <array>
#include "Pack.hpp"
#include "Player.hpp"
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
    int dealerInd;
    int whoOrderedUp;
    int handCount;
    vector <int> whoWon;
public:
    Game(ifstream* cardIn, bool shuffleBool, int pointsNeeded,
        vector<string> info);
    void play();
    void shuffle();
    void deal(int start);
    bool make_trump(int round);
    void play_hand(int starter);
    void delete_players();
    void reset_partial();
    void update_score();
};

// ./euchre.exe pack.in noshuffle 1 Adi Simple
// Barbara Simple Chi-Chih Simple Dabbala Simple

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

    //first case "If the team that ordered up the
    //  trump suit takes 3 or 4 tricks, they get 1 point."
    if ((whoOrderedUp == 0 || whoOrderedUp == 2)
    &&(t1_wins==3 || t1_wins ==4)){
        t1_score++;
        cout << players[0]->get_name() << " and "
        << players[2]->get_name() << " win the hand" <<endl;
    } else if ((whoOrderedUp == 1 || whoOrderedUp == 3)
    &&(t2_wins==3 || t2_wins ==4)){
        t2_score++;
        cout << players[1]->get_name() << " and "
        << players[3]->get_name() << " win the hand" <<endl;
    }
    //second case "If the team that ordered up thetrump suit
    // takes all 5 tricks, they get 2 points. This is called a march."
    if ((whoOrderedUp == 0 || whoOrderedUp == 2)&&(t1_wins==5)){
        t1_score = t1_score+2;
        cout << players[0]->get_name() << " and "
        << players[2]->get_name() << " win the hand" <<endl;
        //print march
        cout << "march!" << endl;
    } else if ((whoOrderedUp == 1 || whoOrderedUp == 3)&&(t2_wins==5)){
        t2_score = t2_score+2;
        cout << players[1]->get_name() << " and "
        << players[3]->get_name() << " win the hand" <<endl;
        cout << "march!" << endl;
    }
    //third case "If the team that did not order up takes
    // 3, 4, or 5 tricks, they receive 2 points. This is called euchred."
    if (!(whoOrderedUp == 0 || whoOrderedUp == 2)&&(t1_wins>2)){
        t1_score = t1_score+2;
        cout << players[0]->get_name() << " and "
        << players[2]->get_name() << " win the hand" <<endl;
        cout << "euchred!" << endl;
    } else if (!(whoOrderedUp == 1 || whoOrderedUp == 3)&&(t2_wins>2)){
        t2_score = t2_score+2;
        cout << players[1]->get_name() << " and "
        << players[3]->get_name() << " win the hand" <<endl;
        cout << "euchred!" << endl;
    }

    //print out score
    cout << players[0]->get_name() << " and "
    << players[2]->get_name() << " have " << t1_score << " points" <<endl;
    cout << players[1]->get_name() << " and "
    << players[3]->get_name() << " have " << t2_score << " points" <<endl;  
    cout << endl;
}

void Game::shuffle(){
    pack.shuffle();
}

void Game::add_player_cards(int c, Player* p){
    for (int i = 0; i < c; ++i){
        p->add_card(pack.deal_one());
    }
}

void Game::deal(int start){
    
    //first round
    add_player_cards(3, players[(start+1)%4]);
    add_player_cards(2, players[(start+2)%4]);
    add_player_cards(3, players[(start+3)%4]);
    add_player_cards(2, players[(start+0)%4]);

    //second round
    add_player_cards(2, players[(start+1)%4]);
    add_player_cards(3, players[(start+2)%4]);
    add_player_cards(2, players[(start+3)%4]);
    add_player_cards(3, players[(start+0)%4]);
}

bool Game::make_trump(int r){
    //loop through each player to get their trump
    for (int i = dealerInd+1; i<dealerInd+5; ++i){
        if(players[i%4]->make_trump(upcard, (i%4) == dealerInd,
                            r, trump)){
            whoOrderedUp = i%4;
            cout<< players[i%4]->get_name()
            << " orders up " << trump << endl;
            // //if is second round then extra space
            // if(r==2){
            //     cout << endl;
            // }
            if(r == 1){
                players[dealerInd%4]->add_and_discard(upcard);
            }
            cout << endl;
            return true;
        } else{
            cout << players[i%4]->get_name() << " passes" << endl;
        }
    }
    return false;
}

void Game::play_hand(int starter){
    //five rounds
    int curInd = starter+1;
    Card lead;
    for (int i = 0; i < 5; ++i){
        vector <Card> handCards;
        //lead cards for 1
        handCards.push_back(players[curInd%4]->lead_card(trump));
        lead = handCards[0];
        if (lead.is_left_bower(trump)){
            Card next (JACK, Suit_next(lead.get_suit()));
            lead = next;
        }
        cout << handCards[0] << " led by "
        << players[(curInd)%4]->get_name() << endl;

        //play cards for 2,3,4
        for (int j =1; j<4; j++){
            handCards.push_back(players[(curInd+j)%4]
            ->play_card(lead, trump));
            cout << handCards[j] << " played by "
            << players[(curInd+j)%4]->get_name() << endl;
            // if (Card_less(lead, curComp, upcard, trump)){
            //     //play King of Spades played by Chi-Chih
            //     lead = curComp;
            //     endInd = (curInd+j)%4;
            // }
        }

        //analyze led and played cards in hand
        Card a = handCards[0];
        Card b;
        int loopHold=0;
        for(int i = 1; i < handCards.size() ; ++i){
            b = handCards[i];
            if (Card_less(a, b, lead, trump)){
                a = b;
                loopHold = i;
            }
        }

        curInd = (curInd+loopHold)%4;

        //printing who took the trick "Dabbala takes the trick"
        cout << players[curInd]->get_name()
        << " takes the trick" << endl;

        cout << endl;

        whoWon.push_back(curInd);
    }
}

void Game::delete_players(){
    //deletes players after game
    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }
}

Game::Game(ifstream* cardIn, bool shuffleBool,
        int pointsNeeded, vector<string> info) {
    
    //inport pack
    Pack impack(*cardIn);
    pack = impack;

    //add points needed to win
    pointsReq = pointsNeeded;

    string p1Name = info[0];
    string p1Type = info[1];
    string p2Name = info[2];
    string p2Type = info[3];
    string p3Name = info[4];
    string p3Type = info[5];
    string p4Name = info[6];
    string p4Type = info[7];

    handCount = 0;
    t1_score = 0;
    t2_score = 0;
    dealerInd = 0;

    sBool = shuffleBool;

    //add players
    players.push_back(Player_factory(p1Name, p1Type));
    players.push_back(Player_factory(p2Name, p2Type));
    players.push_back(Player_factory(p3Name, p3Type));
    players.push_back(Player_factory(p4Name, p4Type));
}

void Game::play(){    
    //Print out which hand
    cout << "Hand " << handCount << endl;

    //shuffle if needed
    if (sBool){
        shuffle();
    }

    //print out dealer
    cout << players[dealerInd%4]->get_name() << " deals" << endl;

    //deals out the cards
    deal(dealerInd);

    //pulls the upcard
    upcard = pack.deal_one();

    //print out upcard
    cout << upcard << " turned up" << endl;

    //make the trump and it returns false if everyone passes. Then runs r2
    if(!make_trump(1)){
        make_trump(2);
    }

    play_hand(dealerInd);

    update_score();

    if(t1_score > pointsReq || t2_score > pointsReq){
        //print who won
        if (t1_score > pointsReq){
            cout << players[0]->get_name()
            << " and " << players[2]->get_name() << " win!";
        }else {
            cout << players[1]->get_name()
            << " and " << players[3]->get_name() << " win!";
        }
        cout << endl;
        delete_players();
        return;
    }else {
        handCount ++;
        dealerInd ++;
        //resets pack and vectors used
        reset_partial();
        play();
    }
    return;
}

int main(int argc, char *argv[]) {
    string packIn = argv[1];
    string shuffleBool = argv[2];
    int pointsIn = stoi(argv[3]);
    vector<string> info = {};
    info.push_back(argv[4]);
    info.push_back(argv[5]);
    info.push_back(argv[6]);
    info.push_back(argv[7]);
    info.push_back(argv[8]);
    info.push_back(argv[9]);
    info.push_back(argv[10]);
    info.push_back(argv[11]);

// There are exactly 12 arguments, including the executable name.
// Points to win the game is between 1 and 100, inclusive.
// The shuffle argument is either shuffle or noshuffle.
// The types of each of the players are either Simple or Human.

//./euchre.exe pack.in noshuffle 1 Adi
// Simple Barbara Simple Chi-Chih Simple Dabbala Simple

    //check for errors
    if(argc != 12 || pointsIn>100
        || pointsIn<1 || (shuffleBool != "shuffle"
            &&shuffleBool != "noshuffle")
            || (info[1] != "Simple" && info[1] != "Human")
            || (info[3] != "Simple" && info[3] != "Human")
            || (info[5] != "Simple" && info[5] != "Human")
            || (info[7] != "Simple" && info[7] != "Human")){
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

    //print out executable and all arguments on the first line
    for (size_t t = 0; t < argc; t++){
        cout<<argv[t]<<" ";
    }
    cout << endl;

    //play the game
    Game game(&fin, sBool, pointsIn, info);
    
    game.play();

}