//
// Created by jacky on 2019-05-17.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "DrawCardSystem.h"

class DrawCardSystemFixture : public ::testing::Test {
public:

    void SetUp() final{

    }
    void TearDown() final{

    }
};

TEST_F(DrawCardSystemFixture, TestCreateCardInfo) {
    DrawCardSystem * cardInfo = nullptr;
    cardInfo = new DrawCardSystem();
}

TEST_F(DrawCardSystemFixture, TestDrawCard) {
    DrawCardSystem * cardInfo = nullptr;
    cardInfo = new DrawCardSystem();
    ASSERT_GE(cardInfo->drawCard(), 0);
}

TEST_F(DrawCardSystemFixture, TestDrawCardRandom) {
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