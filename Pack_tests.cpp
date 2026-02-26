#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

TEST(pack_istream){
    istringstream i("Ten of Spades");
    Pack pack(i);
    Card first = pack.deal_one();
    ASSERT_EQUAL(TEN, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

TEST(resetNext) {
    Pack pack;
    Card first = pack.deal_one();
    pack.reset();
    first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

TEST(test_shuffle) {
    Pack pack;
    pack.shuffle();
    Card first = pack.deal_one();
    Card second = pack.deal_one();
    ASSERT_EQUAL(JACK, second.get_rank());
    ASSERT_EQUAL(SPADES, second.get_suit());
    ASSERT_EQUAL(KING, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

TEST(pack_istream1){
    Pack pack;
    for(int i =0 ; i < 24; ++i){
        pack.deal_one();
    }
    ASSERT_TRUE(pack.empty());
}

TEST(pack_istream2){
    Pack pack;
    ASSERT_FALSE(pack.empty());
}

// Add more tests here

TEST_MAIN()
