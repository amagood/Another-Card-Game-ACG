//
// Created by jacky on 2019/5/21.
//


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CardInfoSystem.h"

class CardInfoSystemFixture : public ::testing::Test {
public:

    void SetUp() final{

    }
    void TearDown() final{

    }
};

TEST_F(CardInfoSystemFixture, TestCreateCardInfo) {
    CardInfoSystem * cardInfo = new CardInfoSystem();
    cardInfo->load();
}