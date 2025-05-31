//
// Created by eal on 5/6/25.
//

#include "PerftTestUtil.h"

#include <future>
#include <strings.h>
#include <thread>

std::vector<std::pair<Move, int>> PerftTestUtil::PerftTest(Board board, int threadsToStart, int depth)
{
  index_ = 0;
  auto legalMoves = board.generateAllLegalMoves();

  results_.resize(legalMoves.size());

  for (auto move : legalMoves)
  {
    Board newBoard(board);
    newBoard.executeMove(move);
    boards_.push_back(newBoard);
    resultPositions_.push_back(move);
  }

  std::vector<std::thread> threads;

  for (int i = 0; i < threadsToStart; i++)
  {
    threads.emplace_back([this,depth]()-> void { this->threadStart(depth - 1); });
  }

  for (int i = 0; i < threadsToStart; i++)
  {
    threads[i].join();
  }

  std::vector<std::pair<Move, int>> resultVector;
  for (int i = 0; i < results_.size(); i++)
  {
    resultVector.emplace_back(resultPositions_[i], results_[i]);
  }

  return resultVector;
}

void PerftTestUtil::threadStart(const int depth)
{
  while (index_ < boards_.size())
  {
    int localIndex = index_++;
    recursivePerft(boards_[localIndex], depth, &results_[localIndex]);
  }
}

void PerftTestUtil::recursivePerft(Board board, int depth, int* perftCount)
{
  if (depth == 0)
  {
    (*perftCount)++;
    return;
  }
  auto legalMoves = board.generateAllLegalMoves();
  for (const auto& move : legalMoves)
  {
    Board newBoard(board);
    newBoard.executeMove(move);
    recursivePerft(newBoard, depth - 1, perftCount);
  }
}
