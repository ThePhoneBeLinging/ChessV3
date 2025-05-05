//
// Created by eal on 5/6/25.
//

#ifndef PERFTTESTS_H
#define PERFTTESTS_H
#include <gtest/gtest.h>

#include "PerftTestUtil.h"
#include "../src/Board.h"

class PerftTests : public ::testing::Test
{
};

TEST(PerftTests, test1)
{
  PerftTestUtil util;
  Board board;
  int total = 0;
  int depth = 1;
  int threads = 16;
  int expectedResult = 20;
  auto response = util.PerftTest(board, threads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}

TEST(PerftTests, test2)
{
  PerftTestUtil util;
  Board board;
  int total = 0;
  int depth = 2;
  int threads = 16;
  int expectedResult = 400;
  auto response = util.PerftTest(board, threads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}

TEST(PerftTests, test3)
{
  PerftTestUtil util;
  Board board;
  int total = 0;
  int depth = 3;
  int threads = 16;
  int expectedResult = 8902;
  auto response = util.PerftTest(board, threads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}

TEST(PerftTests, test4)
{
  PerftTestUtil util;
  Board board;
  int total = 0;
  int depth = 4;
  int threads = 16;
  int expectedResult = 197281;
  auto response = util.PerftTest(board, threads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}

TEST(PerftTests, test5)
{
  PerftTestUtil util;
  Board board;
  int total = 0;
  int depth = 5;
  int threads = 16;
  int expectedResult = 197281;
  auto response = util.PerftTest(board, threads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}


TEST(PerftTests, test6)
{
  PerftTestUtil util;
  Board board;
  int total = 0;
  int depth = 6;
  int threads = 16;
  int expectedResult = 119060324;
  auto response = util.PerftTest(board, threads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}


#endif //PERFTTESTS_H
