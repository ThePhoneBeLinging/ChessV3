//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//

#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <vector>
#include <memory>
#include "Move.h"
#include "Pieces.h"


class Board
{
public:
  Board();

  explicit Board(const std::string& fenString);

  Board(const Board& board) = default;

  std::vector<Move> generateAllLegalMoves();

  std::vector<std::pair<int, int>> getAllPieces(Pieces piece, bool isWhite);

  static uint64_t getBitBoardFromLocation(const std::pair<int, int>& location);

  void removePiece(uint64_t bitboard);

  void executeMove(const Move& move);

  [[nodiscard]] uint64_t getWhiteBitBoard() const;

  [[nodiscard]] uint64_t getBlackBitBoard() const;

  static bool isPosInsideBoard(const std::pair<int, int>& location);

  [[nodiscard]] Pieces getPieceFromLocation(uint64_t bitboard) const;

private:
  std::vector<Move> generatePseudoLegalMoves(bool isWhite);

  [[nodiscard]] bool isMoveLegal(const Move& move, bool isWhite);

  [[nodiscard]] bool canCastleKingSide();

  [[nodiscard]] bool canCastleQueenSide();

  [[nodiscard]] bool isTileOccupiedByColor(const std::pair<int, int>& location, bool isWhite) const;


  std::vector<Move> generateAllPawnMoves(bool isWhite);

  std::vector<Move> generateAllRookMoves(bool isWhite);

  std::vector<Move> generateAllKnightMoves(bool isWhite);

  std::vector<Move> generateAllBishopMoves(bool isWhite);

  std::vector<Move> generateAllQueenMoves(bool isWhite);

  std::vector<Move> generateAllKingMoves(bool isWhite);

  [[nodiscard]] std::vector<Move> generateRookMovesFromLocation(const std::pair<int, int>& location,
                                                                bool isWhite) const;

  [[nodiscard]] std::vector<Move> generateBishopMovesFromLocation(const std::pair<int, int>& location,
                                                                  bool isWhite) const;

  Move lastWhiteMove_;
  Move lastBlackMove_;

  uint64_t whitePawnsBitBoard_;
  uint64_t whiteRooksBitBoard_;
  uint64_t whiteKnightsBitBoard_;
  uint64_t whiteBishopsBitBoard_;
  uint64_t whiteQueensBitBoard_;
  uint64_t whiteKingBitBoard_;
  uint64_t blackPawnsBitBoard_;
  uint64_t blackRooksBitBoard_;
  uint64_t blackKnightsBitBoard_;
  uint64_t blackBishopsBitBoard_;
  uint64_t blackQueensBitBoard_;
  uint64_t blackKingBitBoard_;

  bool isWhite_;

  bool whiteCanCastleKingSide_;
  bool whiteCanCastleQueenSide_;

  bool blackCanCastleKingSide_;
  bool blackCanCastleQueenSide_;
};


#endif //BOARD_H
