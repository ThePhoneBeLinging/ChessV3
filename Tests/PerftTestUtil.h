//
// Created by eal on 5/6/25.
//

#ifndef PERFTTESTUTIL_H
#define PERFTTESTUTIL_H
#include <atomic>

#include "../src/Board.h"

class PerftTestUtil
{
public:
  std::vector<std::pair<Move, int>> PerftTest(Board board, int threads, int depth);

private:
  void threadStart(int depth);
  void recursivePerft(Board board, int depth, int* perftCount);
  std::vector<Board> boards_;
  std::vector<Move> resultPositions_;
  std::vector<int> results_;
  std::atomic_int index_;
};


#endif //PERFTTESTUTIL_H
