//
// Created by eal on 5/6/25.
//

#ifndef PERFTTESTS_H
#define PERFTTESTS_H
#include <thread>
#include <gtest/gtest.h>

#include "PerftTestUtil.h"
#include "../src/Board.h"

class PerftTests : public ::testing::Test
{
};

const auto processor_count = std::thread::hardware_concurrency();
const int numThreads = processor_count == 0 ? 8 : processor_count;

TEST(StartPos, Test1)
{
  PerftTestUtil util;
  Board board;
  int total = 0;
  int depth = 1;
  int expectedResult = 20;
  auto response = util.PerftTest(board, numThreads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}

TEST(StartPos, StartPostest2)
{
  PerftTestUtil util;
  Board board;
  int total = 0;
  int depth = 2;
  int expectedResult = 400;
  auto response = util.PerftTest(board, numThreads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}

TEST(StartPos, test3)
{
  PerftTestUtil util;
  Board board;
  int total = 0;
  int depth = 3;
  int expectedResult = 8902;
  auto response = util.PerftTest(board, numThreads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}

TEST(StartPos, test4)
{
  PerftTestUtil util;
  Board board;
  int total = 0;
  int depth = 4;
  int expectedResult = 197281;
  auto response = util.PerftTest(board, numThreads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}

TEST(StartPos, test5)
{
  PerftTestUtil util;
  Board board;
  int total = 0;
  int depth = 1;
  int expectedResult = 4865609;
  auto response = util.PerftTest(board, numThreads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}


TEST(StartPos, test6)
{
  PerftTestUtil util;
  Board board;
  int total = 0;
  int depth = 1;
  int expectedResult = 119060324;
  auto response = util.PerftTest(board, numThreads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}

TEST(r3k2r, test1)
{
  PerftTestUtil util;
  std::string fenString = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ";
  Board board(fenString);
  int total = 0;
  int depth = 1;
  int expectedResult = 48;
  auto response = util.PerftTest(board, numThreads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}

TEST(r3k2r, test2)
{
  PerftTestUtil util;
  std::string fenString = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ";
  Board board(fenString);
  int total = 0;
  int depth = 2;
  int expectedResult = 2039;
  auto response = util.PerftTest(board, numThreads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}


TEST(r3k2r, test3)
{
  PerftTestUtil util;
  std::string fenString = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ";
  Board board(fenString);
  int total = 0;
  int depth = 3;
  int expectedResult = 97862;
  auto response = util.PerftTest(board, numThreads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}

TEST(empty2p5, test1)
{
  PerftTestUtil util;
  std::string fenString = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1";
  Board board(fenString);
  int total = 0;
  int depth = 1;
  int expectedResult = 14;
  auto response = util.PerftTest(board, numThreads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}

TEST(empty2p5, test2)
{
  PerftTestUtil util;
  std::string fenString = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1";
  Board board(fenString);
  int total = 0;
  int depth = 2;
  int expectedResult = 191;
  auto response = util.PerftTest(board, numThreads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}

TEST(empty2p5, test3)
{
  PerftTestUtil util;
  std::string fenString = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1";
  Board board(fenString);
  int total = 0;
  int depth = 3;
  int expectedResult = 2812;
  auto response = util.PerftTest(board, numThreads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}

TEST(empty2p5, test4)
{
  PerftTestUtil util;
  std::string fenString = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1";
  Board board(fenString);
  int total = 0;
  int depth = 4;
  int expectedResult = 43238;
  auto response = util.PerftTest(board, numThreads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}

TEST(empty2p5, test5)
{
  PerftTestUtil util;
  std::string fenString = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1";
  Board board(fenString);
  int total = 0;
  int depth = 5;
  int expectedResult = 674624;
  auto response = util.PerftTest(board, numThreads, depth);
  for (auto result : response)
  {
    total += result.second;
  }
  EXPECT_EQ(total, expectedResult);
}

#endif //PERFTTESTS_H
