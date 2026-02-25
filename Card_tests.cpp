#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


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

TEST(Rbowler_suitTest) {
    Card c(JACK, HEARTS);
    ASSERT_EQUAL(true, c.is_right_bower(HEARTS));
}

TEST(Rbowler_suitTest2) {
    Card c(TWO, HEARTS);
    ASSERT_EQUAL(false, c.is_right_bower(HEARTS));
}


// TEST(Lbowler_suitTest) {
//     Card c(JACK, DIAMONDS);
//     ASSERT_EQUAL(true, c.is_left_bower(HEARTS));
// }

TEST(Lbowler_suitTest2) {
    Card c(TWO, DIAMONDS);
    ASSERT_EQUAL(false, c.is_left_bower(HEARTS));
}

TEST(Face1){
    Card c(JACK, DIAMONDS);
    ASSERT_EQUAL(true, c.is_face_or_ace());  
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
}
// TEST(Greater2){
//     Card c(THREE, SPADES);
//     Card d(THREE, HEARTS);
//     ASSERT_EQUAL(true, c<d);  
// }

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
