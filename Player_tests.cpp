#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// <<:
TEST(insert_operate){
    Player *p = Player_factory("Alice", "Simple");
    ostringstream os;
    os << *p;
    ASSERT_EQUAL("Alice", os.str());

    delete p;
}


//simpleplayer:
TEST(simple_make_trump_1_yes){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(JACK, SPADES));
    p->add_card(Card(QUEEN, SPADES));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(KING, DIAMONDS));
    p->add_card(Card(NINE, DIAMONDS));
    Card upcard(ACE, SPADES);
    Suit trump;
    ASSERT_TRUE(p->make_trump(upcard, false, 1, trump));
    ASSERT_EQUAL(SPADES, trump);

    delete p;
}

TEST(simple_make_trump_1_2){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(JACK, SPADES));
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(NINE, CLUBS));
    p->add_card(Card(TEN, CLUBS));
    Card upcard(ACE, SPADES);
    Suit trump;
    ASSERT_FALSE(p->make_trump(upcard, false, 1, trump));

    delete p;
}

TEST(simple_make_trump_1_no){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(JACK, HEARTS));
    p->add_card(Card(QUEEN, HEARTS));
    p->add_card(Card(TEN, CLUBS));
    p->add_card(Card(KING, DIAMONDS));
    p->add_card(Card(NINE, CLUBS));
    Card upcard(TEN, SPADES);
    Suit trump;
    ASSERT_FALSE(p->make_trump(upcard, false, 1, trump));

    delete p;
}

TEST(simple_make_trump_1_leftbow){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(JACK, SPADES));
    p->add_card(Card(QUEEN, CLUBS));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(KING, CLUBS));
    p->add_card(Card(NINE, HEARTS));
    Card upcard(ACE, CLUBS);
    Suit trump;
    ASSERT_TRUE(p->make_trump(upcard, false, 1, trump));
    ASSERT_EQUAL(CLUBS, trump);

    delete p;
}

TEST(simple_make_trump_2_yes){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(JACK, DIAMONDS));
    p->add_card(Card(QUEEN, HEARTS));
    p->add_card(Card(TEN, CLUBS));
    p->add_card(Card(KING, SPADES));
    p->add_card(Card(NINE, SPADES));
    Card upcard(TEN, DIAMONDS);
    Suit trump;
    ASSERT_TRUE(p->make_trump(upcard, false, 2, trump));
    ASSERT_EQUAL(HEARTS, trump);

    delete p;
}

TEST(simple_make_trump_2_no){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(NINE, DIAMONDS));
    p->add_card(Card(TEN, DIAMONDS));
    p->add_card(Card(NINE, CLUBS));
    p->add_card(Card(TEN, CLUBS));
    p->add_card(Card(NINE, HEARTS));
    Card upcard(ACE, SPADES);
    Suit trump;
    ASSERT_FALSE(p->make_trump(upcard, false, 2, trump));

    delete p;
}

TEST(simple_make_trump_screwthedealer){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(NINE, DIAMONDS));
    p->add_card(Card(TEN, DIAMONDS));
    p->add_card(Card(NINE, CLUBS));
    p->add_card(Card(TEN, CLUBS));
    p->add_card(Card(NINE, HEARTS));
    Card upcard(ACE, SPADES);
    Suit trump;
    ASSERT_TRUE(p->make_trump(upcard, true, 2, trump));
    ASSERT_EQUAL(CLUBS, trump);

    delete p;
}

TEST(simple_add_and_discard_basic){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(NINE, SPADES));
    p->add_card(Card(TEN, SPADES));
    p->add_card(Card(QUEEN, SPADES));
    p->add_card(Card(KING, SPADES));
    p->add_card(Card(ACE, SPADES));
    p->add_and_discard(Card(JACK, SPADES));
    Card led(NINE, HEARTS);
    Card played = p->play_card(led, SPADES);
    ASSERT_EQUAL(Card(TEN, SPADES), played);

    delete p;
}

TEST(simple_lead_card_1){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(NINE, SPADES));
    p->add_card(Card(TEN, SPADES));
    p->add_card(Card(ACE, HEARTS));
    p->add_card(Card(KING, HEARTS));
    p->add_card(Card(QUEEN, DIAMONDS));
    Card led = p->lead_card(SPADES);
    ASSERT_EQUAL(Card(ACE, HEARTS), led);

    delete p;
}

TEST(simple_lead_card_2){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(NINE, SPADES));
    p->add_card(Card(TEN, SPADES));
    p->add_card(Card(QUEEN, SPADES));
    p->add_card(Card(KING, SPADES));
    p->add_card(Card(ACE, SPADES));
    Card led = p->lead_card(SPADES);
    ASSERT_EQUAL(Card(ACE, SPADES), led);

    delete p;
}

TEST(simple_play_card_abletofollow){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(ACE, HEARTS));
    p->add_card(Card(NINE, CLUBS));
    p->add_card(Card(TEN, CLUBS));
    Card led(KING, HEARTS);
    Card played = p->play_card(led, SPADES);
    ASSERT_EQUAL(Card(ACE, HEARTS), played);

    delete p;
}

TEST(simple_play_card_unabletofollow){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(NINE, SPADES));
    p->add_card(Card(TEN, SPADES));
    p->add_card(Card(QUEEN, SPADES));
    p->add_card(Card(KING, SPADES));
    p->add_card(Card(ACE, SPADES));
    Card led(NINE, HEARTS);
    Card played = p->play_card(led, DIAMONDS);
    ASSERT_EQUAL(Card(NINE, SPADES), played);

    delete p;
}

TEST(simple_make_trump_3){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(JACK, SPADES));
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(NINE, CLUBS));
    p->add_card(Card(TEN, CLUBS));
    Card upcard(ACE, SPADES);
    Suit trump;
    ASSERT_FALSE(p->make_trump(upcard, false, 1, trump));

    delete p;
}

TEST(simple_lead_3){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(JACK, CLUBS));
    p->add_card(Card(JACK, SPADES));
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(NINE, DIAMONDS));
    Card led = p->lead_card(SPADES);
    ASSERT_EQUAL(Card(TEN, HEARTS), led);

    delete p;
}

TEST(simple_play_3){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(JACK, CLUBS));
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(NINE, DIAMONDS));
    p->add_card(Card(TEN, DIAMONDS));
    Card led(ACE, SPADES);
    Card played = p->play_card(led, SPADES);
    ASSERT_EQUAL(Card(JACK, CLUBS), played);

    delete p;
}

TEST(simple_make_trump_4){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(JACK, HEARTS));
    p->add_card(Card(NINE, SPADES));
    p->add_card(Card(TEN, SPADES));
    p->add_card(Card(NINE, CLUBS));
    p->add_card(Card(TEN, CLUBS));
    Card upcard(ACE, DIAMONDS);
    Suit trump;
    ASSERT_TRUE(p->make_trump(upcard, false, 2, trump));
    ASSERT_EQUAL(HEARTS, trump);

    delete p;
}

TEST(simple_add_and_discard_2){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(TEN, SPADES));
    p->add_card(Card(QUEEN, SPADES));
    p->add_card(Card(KING, SPADES));
    p->add_card(Card(ACE, SPADES));
    p->add_card(Card(ACE, HEARTS));
    p->add_and_discard(Card(NINE, SPADES));
    Card led(NINE, HEARTS);
    Card played = p->play_card(led, CLUBS);
    ASSERT_EQUAL(Card(NINE, SPADES), played);

    delete p;
}

TEST(simple_play_card_3){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(NINE, DIAMONDS));
    p->add_card(Card(TEN, DIAMONDS));
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(NINE, CLUBS));
    Card led(ACE, DIAMONDS);
    Card played = p->play_card(led, DIAMONDS);
    ASSERT_EQUAL(Card(TEN, DIAMONDS), played);

    delete p;
}

TEST(simple_add_and_discard_3){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(NINE, SPADES));
    p->add_card(Card(TEN, SPADES));
    p->add_card(Card(QUEEN, SPADES));
    p->add_card(Card(KING, SPADES));
    p->add_card(Card(ACE, SPADES));
    p->add_and_discard(Card(JACK, SPADES));
    Card led = p->lead_card(SPADES);
    ASSERT_EQUAL(Card(JACK, SPADES), led);

    delete p;
}
//Hint 2 for "Simple Player Bug 1" -- check if left bower is considered????
TEST(simple_make_trump_r1_leftbower){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(JACK, CLUBS));
    p->add_card(Card(ACE, SPADES));
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(NINE, DIAMONDS));
    Card upcard(TEN, SPADES);
    Suit trump;
    ASSERT_TRUE(p->make_trump(upcard, false, 1, trump));
    ASSERT_EQUAL(SPADES, trump);

    delete p;
}

TEST(simple_make_trump_r2_leftbower){
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(JACK, CLUBS));
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(NINE, DIAMONDS));
    p->add_card(Card(TEN, DIAMONDS));
    Card upcard(ACE, SPADES);
    Suit trump;
    ASSERT_TRUE(p->make_trump(upcard, false, 2, trump));
    ASSERT_EQUAL(CLUBS, trump);

    delete p;
}

TEST_MAIN()


// #include "Player.hpp"
// #include "unit_test_framework.hpp"

// #include <iostream>

// using namespace std;

// TEST(test_player_get_name) {
//     Player * alice = Player_factory("Alice", "Simple");
//     ASSERT_EQUAL("Alice", alice->get_name());

//     delete alice;
// };

// TEST(test_add_card){
//     Player * alice = Player_factory("Alice", "Simple");
//     ASSERT_EQUAL("Alice", alice->get_name());
//     Card c (NINE, SPADES);
//     Card b (TEN, SPADES);
//     alice->add_card(c);
//     alice->add_card(b);

//     ASSERT_EQUAL(alice->play_card(c, c.get_suit()), b);

//     delete alice;
// }

// TEST(test_play_card){
//     Player * alice = Player_factory("Alice", "Simple");
//     ASSERT_EQUAL("Alice", alice->get_name());
//     Card a (NINE, SPADES);
//     Card b (TEN, SPADES);
//     Card c (JACK, SPADES);
//     Card d (QUEEN, HEARTS);
//     alice->add_card(a);
//     alice->add_card(b);
//     alice->add_card(c);
//     alice->add_card(d);

//     ASSERT_EQUAL(alice->play_card(a, HEARTS), c);

//     delete alice;
// }

// TEST(test_make_trump){
//     Player * alice = Player_factory("Alice", "Simple");
//     ASSERT_EQUAL("Alice", alice->get_name());
//     Card a (NINE, SPADES);
//     Card b (TEN, SPADES);
//     Card c (JACK, HEARTS);
//     Card d (QUEEN, HEARTS);
//     Suit s = SPADES;
//     alice->add_card(a);
//     alice->add_card(b);
//     alice->add_card(c);
//     alice->add_card(d);

//     ASSERT_FALSE(alice->make_trump(a, false, 1, s));

//     delete alice;
// }

// TEST(test_make_trump2){
//     Player * alice = Player_factory("Alice", "Simple");
//     ASSERT_EQUAL("Alice", alice->get_name());
//     Card a (JACK, SPADES);
//     Card b (QUEEN, SPADES);
//     Card c (JACK, HEARTS);
//     Card d (QUEEN, HEARTS);
//     Suit s = SPADES;
//     alice->add_card(a);
//     alice->add_card(b);
//     alice->add_card(c);
//     alice->add_card(d);

//     ASSERT_TRUE(alice->make_trump(a, false, 1, s));

//     delete alice;
// }

// TEST(test_make_trump_r2){
//     Player * alice = Player_factory("Alice", "Simple");
//     ASSERT_EQUAL("Alice", alice->get_name());
//     Card a (JACK, SPADES);
//     Card b (TEN, HEARTS);
//     Card c (JACK, HEARTS);
//     Card d (QUEEN, HEARTS);
//     Suit s = SPADES;
//     alice->add_card(a);
//     alice->add_card(b);
//     alice->add_card(c);
//     alice->add_card(d);

//     ASSERT_TRUE(alice->make_trump(a, false, 2, s));

//     delete alice;
// }

// TEST(test_add_discard){
//     Player * alice = Player_factory("Alice", "Simple");
//     ASSERT_EQUAL("Alice", alice->get_name());
//     Card a (JACK, SPADES);
//     Card b (QUEEN, SPADES);
//     alice->add_card(a);
//     alice->add_and_discard(b, SPADES);
//     ASSERT_EQUAL(alice->play_card(a, SPADES), b);

//     delete alice;
// }

// TEST(test_lead_card){
//     Player * alice = Player_factory("Alice", "Simple");
//     ASSERT_EQUAL("Alice", alice->get_name());
//     Card a (JACK, SPADES);
//     Card b (QUEEN, SPADES);
//     alice->add_card(a);
//     alice->add_card(b);
//     ASSERT_EQUAL(alice->lead_card(HEARTS), b);

//     delete alice;
// }

// // Add more tests here

// TEST_MAIN()
