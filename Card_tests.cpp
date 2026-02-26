#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

TEST(str1){
    Card c (JACK, DIAMONDS);
    ASSERT_EQUAL(JACK, c.get_rank());
    ASSERT_EQUAL(DIAMONDS, c.get_suit());
}

TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_card_ctor2) {
    Card c(FOUR, HEARTS);
    ASSERT_EQUAL(FOUR, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(getSuitLB){
    Card c(JACK, DIAMONDS);
    ASSERT_EQUAL(HEARTS, c.get_suit(HEARTS));
}

TEST(Rbowler_suitTest) {
    Card c(JACK, HEARTS);
    ASSERT_EQUAL(true, c.is_right_bower(HEARTS));
}

TEST(Rbowler_suitTest2) {
    Card c(TWO, HEARTS);
    ASSERT_EQUAL(false, c.is_right_bower(HEARTS));
}

TEST(Lbowler_suitTest) {
    Card c(TWO, DIAMONDS);
    ASSERT_EQUAL(false, c.is_left_bower(HEARTS));
}

TEST(Lbowler_suitTest2) {
    Card c(JACK, DIAMONDS);
    ASSERT_EQUAL(true, c.is_left_bower(HEARTS));
}

TEST(Face1){
    Card c(JACK, DIAMONDS);
    ASSERT_EQUAL(true, c.is_face_or_ace());  
}

TEST(Face3){
    Card c(ACE, DIAMONDS);
    ASSERT_EQUAL(true, c.is_face_or_ace());  
}

TEST(Face4){
    Card c(TEN, DIAMONDS);
    ASSERT_EQUAL(false, c.is_face_or_ace());  
}

TEST(Face2){
    Card c(THREE, DIAMONDS);
    ASSERT_EQUAL(false, c.is_face_or_ace());  
}

TEST(Trump1){
    Card c(THREE, DIAMONDS);
    ASSERT_EQUAL(true, c.is_trump(DIAMONDS));  
}

TEST(Greater){
    Card c(THREE, DIAMONDS);
    Card d(FOUR, HEARTS);
    ASSERT_EQUAL(true, c<d);
    ASSERT_FALSE(c>d);  
}

TEST(Greater1){
    Card d(ACE, DIAMONDS);
    Card h(ACE, HEARTS);
    ASSERT_EQUAL(true, d>h);
    ASSERT_FALSE(d<h);
}

TEST(Equal){
    Card a(ACE, HEARTS);
    Card b(ACE, HEARTS);
    Card c(NINE, DIAMONDS);
    ASSERT_TRUE(a<=b);
    ASSERT_TRUE(a>=b);
    ASSERT_TRUE(c<=b);
    ASSERT_TRUE(a>=c);
    ASSERT_TRUE(a==b);
    ASSERT_TRUE(a!=c);
}

TEST(Suit_next1){
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
    ASSERT_EQUAL(HEARTS, Suit_next(DIAMONDS));
}

TEST(Suit_next2){
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES));
    ASSERT_EQUAL(SPADES, Suit_next(CLUBS));
}

TEST(Card_less1){
    Card a(ACE, HEARTS);
    Card b(ACE, DIAMONDS);
    Card c(JACK, DIAMONDS);
    Card d(JACK, HEARTS);
    ASSERT_FALSE(Card_less(a,b, HEARTS));
    ASSERT_TRUE(Card_less(a,c,HEARTS));
    ASSERT_TRUE(Card_less(c,d,HEARTS));
}

TEST(Card_less2){
    Card led(EIGHT, DIAMONDS);
    Card a(NINE, HEARTS);
    Card b(TEN, DIAMONDS);
    Card e(ACE, CLUBS);
    Card c(JACK, DIAMONDS);
    Card d(JACK, HEARTS);
    ASSERT_TRUE(Card_less(b,a, led, HEARTS));
    ASSERT_TRUE(Card_less(e,a, led, HEARTS));
    ASSERT_TRUE(Card_less(e,b, led, HEARTS));
    ASSERT_TRUE(Card_less(a,c, led, HEARTS));
    ASSERT_TRUE(Card_less(c,d, led, HEARTS));
}

// //EFFECTS Returns true if lhs is lower value than rhs.
// //  Does not consider trump.
// bool operator<(const Card &lhs, const Card &rhs);

// //EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
// //  Does not consider trump.
// bool operator<=(const Card &lhs, const Card &rhs);

// //EFFECTS Returns true if lhs is higher value than rhs.
// //  Does not consider trump.
// bool operator>(const Card &lhs, const Card &rhs);

// //EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
// //  Does not consider trump.
// bool operator>=(const Card &lhs, const Card &rhs);

// //EFFECTS Returns true if lhs is same card as rhs.
// //  Does not consider trump.
// bool operator==(const Card &lhs, const Card &rhs);

// //EFFECTS Returns true if lhs is not the same card as rhs.
// //  Does not consider trump.
// bool operator!=(const Card &lhs, const Card &rhs);

// //EFFECTS returns the next suit, which is the suit of the same color
// Suit Suit_next(Suit suit);

// //EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// // order, as described in the spec.
// bool Card_less(const Card &a, const Card &b, Suit trump);

// //EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
// //  and the suit led to determine order, as described in the spec.
// bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump);

// #endif // CARD_HPP


// Add more test cases here

TEST_MAIN()
