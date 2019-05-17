//
// Created by jacky on 2019-05-17.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "DrawCardSystem.h"

class CardInfoFixture : public ::testing::Test {
public:

    void SetUp() final{

    }
    void TearDown() final{

    }
};

TEST_F(CardInfoFixture, TestCreateCardInfo) {
    DrawCardSystem * cardInfo = nullptr;
    cardInfo = new DrawCardSystem();
}

TEST_F(CardInfoFixture, TestDrawCard) {
    DrawCardSystem * cardInfo = nullptr;
    cardInfo = new DrawCardSystem();
    ASSERT_GE(cardInfo->drawCard(), 0);
}

TEST_F(CardInfoFixture, TestDrawCardRandom) {
    DrawCardSystem * cardInfo = nullptr;
    cardInfo = new DrawCardSystem();
    bool allSame = true;
    int last_card = cardInfo->drawCard();
    for (int i=0; i < 100; i ++) {
        if (last_card != cardInfo->drawCard()) {
            allSame = false;
        }
    }
    ASSERT_FALSE(allSame);
}