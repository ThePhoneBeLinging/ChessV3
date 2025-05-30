//
// Created by Elias Aggergaard Larsen on 30/05/2025.
//
#include "../src/Board.h"
#include "gtest/gtest.h"

class FenTests : public ::testing::Test
{
};


TEST_F(FenTests, StartPos)
{
  std::string fenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  auto fenBoard = Board(fenString);
  auto board = Board();
  EXPECT_EQ(fenBoard.generateAllLegalMoves().size(),board.generateAllLegalMoves().size());

  for (auto fenMove : fenBoard.generateAllLegalMoves())
  {
    bool equivelantFound = false;
    for (auto move : board.generateAllLegalMoves())
    {
      if (fenMove.capturedPiece == move.capturedPiece && fenMove.from == move.from && fenMove.to == move.to && fenMove.promotion == move.promotion)
      {
        equivelantFound = true;
        break;
      }
    }
    EXPECT_TRUE(equivelantFound);
  }
}