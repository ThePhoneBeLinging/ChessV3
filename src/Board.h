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

    Board(const Board& board) = default;

    std::vector<Move> generateAllLegalMoves();

    std::vector<std::pair<int, int>> getAllPieces(Pieces piece, bool isWhite);

    static uint64_t getBitBoardFromLocation(std::pair<int, int> location);

    void removePiece(uint64_t bitboard);

    void executeMove(Move move);

    [[nodiscard]] uint64_t getWhiteBitBoard() const;

    [[nodiscard]] uint64_t getBlackBitBoard() const;

    static bool isPosInsideBoard(std::pair<int, int> location);

    [[nodiscard]] Pieces getPieceFromLocation(uint64_t bitboard) const;

private:
    std::vector<Move> generatePseudoLegalMoves(bool isWhite);

    [[nodiscard]] bool isMoveLegal(const Move& move, bool isWhite);

    [[nodiscard]] bool isTileOccupiedByColor(std::pair<int, int> location, bool isWhite) const;


    std::vector<Move> generateAllPawnMoves(bool isWhite);

    std::vector<Move> generateAllRookMoves(bool isWhite);

    std::vector<Move> generateAllKnightMoves(bool isWhite);

    std::vector<Move> generateAllBishopMoves(bool isWhite);

    std::vector<Move> generateAllQueenMoves(bool isWhite);

    std::vector<Move> generateAllKingMoves(bool isWhite);

    std::vector<Move> generateRookMovesFromLocation(std::pair<int, int> location, bool isWhite);

    std::vector<Move> generateBishopMovesFromLocation(std::pair<int, int> location, bool isWhite);

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
};


#endif //BOARD_H
