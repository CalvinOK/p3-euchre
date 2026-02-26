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

TEST(make_trump_r1_case2){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (NINE, CLUBS);
    Card b (TEN, DIAMONDS);
    Card c (QUEEN, DIAMONDS);
    Card d (TEN, DIAMONDS);
    Suit s = SPADES;
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);

    ASSERT_TRUE(alice->make_trump(a, true, 2, s));

    delete alice;
}

TEST(make_trump_r1_case3){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (NINE, SPADES);
    Card b (TEN, SPADES);
    Card c (QUEEN, SPADES);
    Card d (TEN, SPADES);
    Suit s = HEARTS;
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);

    ASSERT_FALSE(alice->make_trump(a, false, 1, s));

    delete alice;
}

TEST(make_trump_r1_case4){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (NINE, SPADES);
    Card b (TEN, SPADES);
    Card c (QUEEN, HEARTS);
    Card d (TEN, HEARTS);
    Suit s = HEARTS;
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);

    ASSERT_FALSE(alice->make_trump(a, false, 1, s));

    delete alice;
}

TEST(make_trump_r1_case5){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (NINE, SPADES);
    Card b (TEN, SPADES);
    Card c (QUEEN, SPADES);
    Card d (TEN, HEARTS);
    Suit s = HEARTS;
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);

    ASSERT_FALSE(alice->make_trump(a, false, 1, s));

    delete alice;
}

TEST(make_trump_r1_case6){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (QUEEN, SPADES);
    Card b (KING, SPADES);
    Card c (QUEEN, HEARTS);
    Card d (TEN, HEARTS);
    Suit s = HEARTS;
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);

    ASSERT_TRUE(alice->make_trump(a, false, 1, s));

    delete alice;
}

TEST(make_trump_r1_case7){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (NINE, SPADES);
    Card b (KING, SPADES);
    Card c (QUEEN, HEARTS);
    Card d (TEN, HEARTS);
    Suit s = HEARTS;
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);

    ASSERT_FALSE(alice->make_trump(a, false, 2, s));

    delete alice;
}

TEST(make_trump_r1_case8){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (NINE, SPADES);
    Card b (JACK, CLUBS);
    Card c (QUEEN, SPADES);
    Card d (TEN, HEARTS);
    Suit s = HEARTS;
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);

    ASSERT_TRUE(alice->make_trump(a, false, 1, s));

    delete alice;
}

TEST(make_trump_r1_case9){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (JACK, SPADES);
    Card b (JACK, CLUBS);
    Suit s = SPADES;
    alice->add_card(a);
    alice->add_card(b);

    ASSERT_TRUE(alice->make_trump(a, false, 1, s));

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

TEST(test_name_human){
    Player * alice = Player_factory("Alice", "Human");
    ASSERT_EQUAL("Alice", alice->get_name());
    delete alice;
}


TEST(test_add_discard2){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (NINE, SPADES);
    Card b (JACK, HEARTS);
    Card c (QUEEN, SPADES);
    Card d (TEN, HEARTS);
    Card e (TEN, CLUBS);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_and_discard(a);

    ASSERT_EQUAL(alice->play_card(e, CLUBS), a);

    delete alice;
}

TEST(test_add_discard3){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (NINE, SPADES);
    Card b (JACK, HEARTS);
    Card c (QUEEN, SPADES);
    Card d (TEN, HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);

    ASSERT_EQUAL(alice->play_card(a, SPADES), c);

    delete alice;
}

TEST(test_lead_card){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (NINE, SPADES);
    Card b (JACK, DIAMONDS);
    Card c (QUEEN, SPADES);
    Card d (TEN, HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);

    ASSERT_EQUAL(alice->lead_card(SPADES), b);

    delete alice;
}

TEST(test_lead_card_2){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (JACK, SPADES);
    Card b (JACK, DIAMONDS);
    Card c (JACK, CLUBS);
    Card d (JACK, HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);

    ASSERT_EQUAL(alice->lead_card(DIAMONDS), c);

    delete alice;
}

TEST(test_lead_card_3){
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Card a (NINE, SPADES);
    Card b (TEN, SPADES);
    Card c (KING, SPADES);
    Card d (QUEEN, SPADES);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);

    ASSERT_EQUAL(alice->lead_card(SPADES), c);

    delete alice;
}

// Add more tests here

TEST_MAIN()
