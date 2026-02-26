#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
};

TEST(test_add_card){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card c (NINE, SPADES);
    Card b (TEN, SPADES);
    alice->add_card(c);
    alice->add_card(b);

    ASSERT_EQUAL(alice->play_card(c, c.get_suit()), b);

    delete alice;
}

TEST(test_play_card){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (NINE, SPADES);
    Card b (TEN, SPADES);
    Card c (JACK, SPADES);
    Card d (QUEEN, HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);

    ASSERT_EQUAL(alice->play_card(a, HEARTS), c);

    delete alice;
}

TEST(test_make_trump){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (NINE, SPADES);
    Card b (TEN, SPADES);
    Card c (JACK, HEARTS);
    Card d (QUEEN, HEARTS);
    Suit s = SPADES;
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);

    ASSERT_FALSE(alice->make_trump(a, false, 1, s));

    delete alice;
}

TEST(test_make_trump2){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (JACK, SPADES);
    Card b (QUEEN, SPADES);
    Card c (JACK, HEARTS);
    Card d (QUEEN, HEARTS);
    Suit s = SPADES;
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);

    ASSERT_TRUE(alice->make_trump(a, false, 1, s));

    delete alice;
}

TEST(test_make_trump_r2){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (JACK, SPADES);
    Card b (TEN, HEARTS);
    Card c (JACK, HEARTS);
    Card d (QUEEN, HEARTS);
    Suit s = SPADES;
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);

    ASSERT_TRUE(alice->make_trump(a, false, 2, s));

    delete alice;
}

TEST(make_trump_r1_case1){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (NINE, SPADES);
    Card b (TEN, SPADES);
    Card c (NINE, CLUBS);
    Card d (TEN, CLUBS);
    Suit s = SPADES;
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);

    ASSERT_FALSE(alice->make_trump(a, false, 1, s));

    delete alice;
}

TEST(test_add_discard){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (JACK, SPADES);
    Card b (QUEEN, SPADES);
    alice->add_card(a);
    alice->add_and_discard(b);
    ASSERT_EQUAL(alice->play_card(a, SPADES), a);

    delete alice;
}

TEST(test_lead_card){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (JACK, SPADES);
    Card b (QUEEN, SPADES);
    alice->add_card(a);
    alice->add_card(b);
    ASSERT_EQUAL(alice->lead_card(HEARTS), b);

    delete alice;
}

// Add more tests here

TEST_MAIN()
