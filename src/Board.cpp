//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//

#include "Board.h"
#include <iostream>

Board::Board() : lastWhiteMove_(0, 0), lastBlackMove_(0, 0),whiteCanCastleKingSide_(true),
                 whiteCanCastleQueenSide_(true), blackCanCastleKingSide_(true), blackCanCastleQueenSide_(true)
{
    isWhite_ = true;
    // Initialize white pieces
    whitePawnsBitBoard_ = 0x000000000000FF00;
    whiteRooksBitBoard_ = 0x0000000000000081;
    whiteKnightsBitBoard_ = 0x0000000000000042;
    whiteBishopsBitBoard_ = 0x0000000000000024;
    whiteQueensBitBoard_ = 0x0000000000000008;
    whiteKingBitBoard_ = 0x0000000000000010;

    // Initialize black pieces
    blackPawnsBitBoard_ = 0x00FF000000000000;
    blackRooksBitBoard_ = 0x8100000000000000;
    blackKnightsBitBoard_ = 0x4200000000000000;
    blackBishopsBitBoard_ = 0x2400000000000000;
    blackQueensBitBoard_ = 0x0800000000000000;
    blackKingBitBoard_ = 0x1000000000000000;
}

Board::Board(const std::string& fenString)
    : lastWhiteMove_(0, 0), lastBlackMove_(0, 0), whitePawnsBitBoard_(0), whiteRooksBitBoard_(0),
whiteBishopsBitBoard_(0), whiteKingBitBoard_(0),whiteCanCastleKingSide_(false),whiteCanCastleQueenSide_(false),whiteKnightsBitBoard_(0)
, whiteQueensBitBoard_(0), blackBishopsBitBoard_(0), blackCanCastleKingSide_(false), blackCanCastleQueenSide_(false),
blackKingBitBoard_(0), blackKnightsBitBoard_(0),blackPawnsBitBoard_(0),blackQueensBitBoard_(0),blackRooksBitBoard_(0),isWhite_(true)
{
    uint64_t currentPosition = 0x8000000000000000;
    int index = 0;
    for (const auto& character : fenString)
    {
        if (character == ' ')
        {
            index++;
        }
        if (index == 0)
        {
            switch (character)
            {
                case 'P': {whitePawnsBitBoard_ |= currentPosition; break;}
                case 'R': {whiteRooksBitBoard_ |= currentPosition; break;}
                case 'B': {whiteBishopsBitBoard_ |= currentPosition; break;}
                case 'Q': {whiteQueensBitBoard_ |= currentPosition; break;}
                case 'K': {whiteKingBitBoard_ |= currentPosition; break;}
                case 'N': {whiteKnightsBitBoard_ |= currentPosition; break;}

                case 'p': {blackPawnsBitBoard_ |= currentPosition; break;}
                case 'r': {blackRooksBitBoard_ |= currentPosition; break;}
                case 'b': {blackBishopsBitBoard_ |= currentPosition; break;}
                case 'q': {blackQueensBitBoard_ |= currentPosition; break;}
                case 'k': {blackKingBitBoard_ |= currentPosition; break;}
                case 'n': {blackKnightsBitBoard_|= currentPosition; break;}

                case '1': {currentPosition = currentPosition >> 1; continue;}
                case '2': {currentPosition = currentPosition >> 2; continue;}
                case '3': {currentPosition = currentPosition >> 3; continue;}
                case '4': {currentPosition = currentPosition >> 4; continue;}
                case '5': {currentPosition = currentPosition >> 5; continue;}
                case '6': {currentPosition = currentPosition >> 6; continue;}
                case '7': {currentPosition = currentPosition >> 7; continue;}
                case '8': {currentPosition = currentPosition >> 8; continue;}
                case ' ': {break;}
                case '/':
                default: continue;
            }
            currentPosition = currentPosition >> 1;
        }
        if (index == 1)
        {
            switch (character)
            {
                case 'w': {isWhite_=true; break;}
                case 'b': {isWhite_=false; break;}
                default: {break;}
            }
        }
        if (index == 2)
        {
            switch (character)
            {
                case 'K': {whiteCanCastleKingSide_ = true;break;}
                case 'Q': {whiteCanCastleQueenSide_ = true;break;}
                case 'k': {blackCanCastleKingSide_ = true; break;}
                case 'q': {blackCanCastleQueenSide_ = true; break;}
                default: {break;}
                }
        }
        if (index == 3)
        {
            if (character == '-')
            {
                lastWhiteMove_ = Move(-1,-1);
                lastBlackMove_ = Move(-1,-1);
            }
        }
    }
}


std::vector<Move> Board::generateAllLegalMoves()
{
    // Filter out illegal moves
    std::vector<Move> allMoves = generatePseudoLegalMoves(isWhite_);
    std::vector<Move> legalMoves;
    for (const Move& move : allMoves)
    {
        if (isMoveLegal(move, isWhite_))
        {
            legalMoves.push_back(move);
        }
    }

    return legalMoves;
}

std::vector<std::pair<int, int>> Board::getAllPieces(Pieces piece, bool isWhite)
{
    uint64_t bitBoard = 0;
    switch (piece)
    {
        case Pieces::Pawn:
            bitBoard = isWhite ? whitePawnsBitBoard_ : blackPawnsBitBoard_;
            break;
        case Pieces::Rook:
            bitBoard = isWhite ? whiteRooksBitBoard_ : blackRooksBitBoard_;
            break;
        case Pieces::Knight:
            bitBoard = isWhite ? whiteKnightsBitBoard_ : blackKnightsBitBoard_;
            break;
        case Pieces::Bishop:
            bitBoard = isWhite ? whiteBishopsBitBoard_ : blackBishopsBitBoard_;
            break;
        case Pieces::Queen:
            bitBoard = isWhite ? whiteQueensBitBoard_ : blackQueensBitBoard_;
            break;
        case Pieces::King:
            bitBoard = isWhite ? whiteKingBitBoard_ : blackKingBitBoard_;
            break;
        default:
            throw std::invalid_argument("Invalid piece type or color");
    }

    std::vector<std::pair<int, int>> locations;

    for (int i = 0; i < 64; ++i)
    {
        if (bitBoard & (1ULL << i))
        {
            int x = i % 8;
            int y = i / 8;
            locations.emplace_back(x, y);
        }
    }
    return locations;
}

uint64_t Board::getBitBoardFromLocation(std::pair<int, int> location)
{
    return 1ULL << (location.first + location.second * 8);
}

void Board::executeMove(Move move)
{
    if (isWhite_)
    {
        lastWhiteMove_ = move;
    }
    else
    {
        lastBlackMove_ = move;
    } // TODO Could speed this by taking color as an argument
    uint64_t fromBitBoard = move.from;
    uint64_t toBitBoard = move.to;
    uint64_t capturedPiece = move.capturedPiece;

    // Determine which piece is moving
    uint64_t* bitBoards[] = {
        &whitePawnsBitBoard_, &whiteRooksBitBoard_, &whiteKnightsBitBoard_,
        &whiteBishopsBitBoard_, &whiteQueensBitBoard_, &whiteKingBitBoard_,
        &blackPawnsBitBoard_, &blackRooksBitBoard_, &blackKnightsBitBoard_,
        &blackBishopsBitBoard_, &blackQueensBitBoard_, &blackKingBitBoard_
    };

    // If the move captures an opponent's piece, remove it from the board
    removePiece(toBitBoard);
    if (capturedPiece != 0)
    {
        removePiece(capturedPiece);
    }

    for (auto& bitBoard : bitBoards)
    {
        if (*bitBoard & fromBitBoard)
        {
            *bitBoard &= ~fromBitBoard; // Remove piece from the original position
            *bitBoard |= toBitBoard; // Place piece at the new position
            break;
        }
    }
    isWhite_ = !isWhite_;
}

uint64_t Board::getWhiteBitBoard() const
{
    return whitePawnsBitBoard_ | whiteRooksBitBoard_ | whiteKnightsBitBoard_ | whiteBishopsBitBoard_ |
        whiteQueensBitBoard_ | whiteKingBitBoard_;
}

uint64_t Board::getBlackBitBoard() const
{
    return blackPawnsBitBoard_ | blackRooksBitBoard_ | blackKnightsBitBoard_ | blackBishopsBitBoard_ |
        blackQueensBitBoard_ | blackKingBitBoard_;
}

bool Board::isMoveLegal(const Move& move, bool isWhite)
{
    // Make the move on a temporary board
    auto tempBoard = Board(*this);
    tempBoard.executeMove(move);

    // Check if the king is in check after the move
    std::pair<int, int> kingPosition;
    auto kingLocations = tempBoard.getAllPieces(Pieces::King, isWhite);
    if (!kingLocations.empty())
    {
        kingPosition = kingLocations[0];
    }
    else
    {
        // No king found, which should not happen in a legal game state
        return false;
    }

    // Check if any opponent piece can attack the king
    auto opponentMoves = tempBoard.generatePseudoLegalMoves(!isWhite);
    for (const auto& opponentMove : opponentMoves)
    {
        if (opponentMove.to == getBitBoardFromLocation(kingPosition))
        {
            return false; // King is in check
        }
    }

    return true; // Move is legal
}

bool Board::isTileOccupiedByColor(std::pair<int, int> location, bool isWhite) const
{
    auto bitBoardOfPos = getBitBoardFromLocation(location);
    auto bitBoardOfColor = isWhite ? getWhiteBitBoard() : getBlackBitBoard();
    return bitBoardOfPos & bitBoardOfColor;
}

bool Board::isPosInsideBoard(std::pair<int, int> location)
{
    return location.first >= 0 && location.first < 8 && location.second >= 0 && location.second < 8;
}

Pieces Board::getPieceFromLocation(uint64_t bitboard) const
{
    if ((whitePawnsBitBoard_ | blackPawnsBitBoard_) & bitboard) return Pieces::Pawn;
    if ((whiteRooksBitBoard_ | blackRooksBitBoard_) & bitboard) return Pieces::Rook;
    if ((whiteKnightsBitBoard_ | blackKnightsBitBoard_) & bitboard) return Pieces::Knight;
    if ((whiteBishopsBitBoard_ | blackBishopsBitBoard_) & bitboard) return Pieces::Bishop;
    if ((whiteQueensBitBoard_ | blackQueensBitBoard_) & bitboard) return Pieces::Queen;
    if ((whiteKingBitBoard_ | blackKingBitBoard_) & bitboard) return Pieces::King;
    return Pieces::None;
}

std::vector<Move> Board::generatePseudoLegalMoves(bool isWhite)
{
    std::vector<Move> allMoves;
    std::vector<Move> pseudoLegalMoves;

    pseudoLegalMoves = generateAllPawnMoves(isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = generateAllRookMoves(isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = generateAllKnightMoves(isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = generateAllBishopMoves(isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = generateAllQueenMoves(isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());

    pseudoLegalMoves = generateAllKingMoves(isWhite);
    allMoves.insert(allMoves.end(), pseudoLegalMoves.begin(), pseudoLegalMoves.end());
    return allMoves;
}

std::vector<Move> Board::generateAllPawnMoves(bool isWhite)
{
    std::vector<Move> moves;
    auto locationOfPieces = getAllPieces(Pieces::Pawn, isWhite);
    for (auto& pair : locationOfPieces)
    {
        std::vector<std::pair<int, int>> legalPositions;
        std::pair<int, int> newLocation = {pair.first, pair.second};
        // Check if the pawn can move one step forward
        newLocation.second += (isWhite ? 1 : -1);
        if (not isTileOccupiedByColor(newLocation, true) && not isTileOccupiedByColor(newLocation, false)
            && isPosInsideBoard(newLocation))
        {
            moves.emplace_back(getBitBoardFromLocation(pair), getBitBoardFromLocation(newLocation));
        }
        // Check if the pawn can move two steps forward
        newLocation.second += (isWhite ? 1 : -1);
        std::pair<int, int> otherLocationToCheck = {newLocation.first, newLocation.second + (isWhite ? -1 : 1)};
        if (pair.second == (isWhite ? 1 : 6) && not isTileOccupiedByColor(newLocation, true)
            && not isTileOccupiedByColor(newLocation, false) && not isTileOccupiedByColor(otherLocationToCheck, true) &&
            not isTileOccupiedByColor(otherLocationToCheck, false) && isPosInsideBoard(newLocation))
        {
            moves.emplace_back(getBitBoardFromLocation(pair), getBitBoardFromLocation(newLocation));
        }
        // Resets newLocation
        newLocation = {pair.first, pair.second};
        // Check if the pawn can capture a piece
        for (int i = -1; i < 2; i++)
        {
            if (i == 0)
            {
                continue;
            }
            newLocation = {pair.first + i, pair.second + (isWhite ? 1 : -1)};
            if (isTileOccupiedByColor(newLocation, not isWhite) && isPosInsideBoard(newLocation))
            {
                moves.emplace_back(getBitBoardFromLocation(pair), getBitBoardFromLocation(newLocation));
            }
        }
        // Check for en passant capture
        auto lastMove = isWhite ? lastBlackMove_ : lastWhiteMove_;
        if (getPieceFromLocation(lastMove.to) == Pieces::Pawn)
        {
            int lastMoveFromBitPos = __builtin_ctzll(lastMove.from);
            int lastMoveToBitPos = __builtin_ctzll(lastMove.to);

            int lastMoveFromRow = lastMoveFromBitPos / 8;
            int lastMoveToRow = lastMoveToBitPos / 8;

            if (std::abs(lastMoveToRow - lastMoveFromRow) == 2)
            {
                int moveFromRow = pair.second;
                int moveFromCol = pair.first;
                int moveToRow = moveFromRow + (isWhite ? 1 : -1);
                int moveToCol = lastMoveToBitPos % 8;

                if (std::abs(moveFromCol - moveToCol) == 1 && abs(moveFromRow - moveToRow) == 1 && isPosInsideBoard({
                    moveToCol, moveToRow
                }) && isTileOccupiedByColor({moveToCol, moveFromRow}, not isWhite))
                {
                    uint64_t targetSquare = getBitBoardFromLocation({moveToCol, moveToRow});
                    auto move = Move(getBitBoardFromLocation(pair), targetSquare);
                    move.capturedPiece = getBitBoardFromLocation({moveToCol, moveFromRow});
                    moves.push_back(move);
                }
            }
        }
        if (isWhite && pair.second == 6)
        {
            Move move = Move(getBitBoardFromLocation(pair),
                             getBitBoardFromLocation(std::pair(pair.first, pair.second + 1)));
            move.promotion = 'Q';
            moves.push_back(move);

            move.promotion = 'N';
            moves.push_back(move);

            move.promotion = 'B';
            moves.push_back(move);

            move.promotion = 'R';
            moves.push_back(move);

            move.promotion = 'P';
            moves.push_back(move);
        }
    }

    return moves;
}

std::vector<Move> Board::generateAllRookMoves(bool isWhite)
{
    std::vector<Move> moves;

    auto locationOfPieces = getAllPieces(Pieces::Rook, isWhite);
    for (auto& pair : locationOfPieces)
    {
        auto movesFromLocation = generateRookMovesFromLocation(pair, isWhite);
        moves.insert(moves.end(), movesFromLocation.begin(), movesFromLocation.end());
    }
    return moves;
}

std::vector<Move> Board::generateAllKnightMoves(bool isWhite)
{
    std::vector<Move> moves;

    auto locationOfPieces = getAllPieces(Pieces::Knight, isWhite);

    for (auto& pair : locationOfPieces)
    {
        std::vector<std::pair<int, int>> possibleMoves =
        {
            {pair.first + 1, pair.second + 2},
            {pair.first + 1, pair.second - 2},
            {pair.first - 1, pair.second + 2},
            {pair.first - 1, pair.second - 2},
            {pair.first + 2, pair.second + 1},
            {pair.first + 2, pair.second - 1},
            {pair.first - 2, pair.second + 1},
            {pair.first - 2, pair.second - 1}
        };

        for (auto& newLocation : possibleMoves)
        {
            if (not isPosInsideBoard(newLocation))
            {
                continue;
            }

            if (isTileOccupiedByColor(newLocation, isWhite))
            {
                continue;
            }
            moves.emplace_back(getBitBoardFromLocation(pair), getBitBoardFromLocation(newLocation));
        }
    }

    return moves;
}

std::vector<Move> Board::generateAllBishopMoves(bool isWhite)
{
    std::vector<Move> moves;
    auto locationOfPieces = getAllPieces(Pieces::Bishop, isWhite);

    for (auto& pair : locationOfPieces)
    {
        auto movesFromLocation = generateBishopMovesFromLocation(pair, isWhite);
        moves.insert(moves.end(), movesFromLocation.begin(), movesFromLocation.end());
    }

    return moves;
}

std::vector<Move> Board::generateAllQueenMoves(bool isWhite)
{
    std::vector<Move> moves;

    auto locationOfPieces = getAllPieces(Pieces::Queen, isWhite);

    for (auto& pair : locationOfPieces)
    {
        auto rookMoves = generateRookMovesFromLocation(pair, isWhite);
        auto bishopMoves = generateBishopMovesFromLocation(pair, isWhite);
        moves.insert(moves.end(), rookMoves.begin(), rookMoves.end());
        moves.insert(moves.end(), bishopMoves.begin(), bishopMoves.end());
    }

    return moves;
}

std::vector<Move> Board::generateAllKingMoves(bool isWhite)
{
    std::vector<Move> moves;

    auto locationOfPieces = getAllPieces(Pieces::King, isWhite);

    for (auto& pair : locationOfPieces)
    {
        for (int i = -1; i < 2; i++)
        {
            for (int k = -1; k < 2; k++)
            {
                std::pair<int, int> newLocation = {pair.first + i, pair.second + k};
                if (i == 0 && k == 0 || not isPosInsideBoard(newLocation))
                {
                    continue;
                }
                if (isTileOccupiedByColor(newLocation, isWhite))
                {
                    continue;
                }
                moves.emplace_back(getBitBoardFromLocation(pair), getBitBoardFromLocation(newLocation));
            }
        }
    }

    return moves;
}

std::vector<Move> Board::generateRookMovesFromLocation(std::pair<int, int> pair, bool isWhite)
{
    std::vector<Move> moves;
    std::pair<int, int> directions[] = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };

    for (const auto& direction : directions)
    {
        for (int i = 1; i < 8; ++i)
        {
            std::pair<int, int> newLocation = {
                pair.first + i * direction.first, pair.second + i * direction.second
            };
            if (!isPosInsideBoard(newLocation))
            {
                break;
            }
            if (isTileOccupiedByColor(newLocation, isWhite))
            {
                break;
            }
            moves.emplace_back(getBitBoardFromLocation(pair), getBitBoardFromLocation(newLocation));
            if (isTileOccupiedByColor(newLocation, !isWhite))
            {
                break;
            }
        }
    }
    return moves;
}

std::vector<Move> Board::generateBishopMovesFromLocation(std::pair<int, int> pair, bool isWhite)
{
    std::vector<Move> moves;
    std::pair<int, int> directions[] = {
        {1, 1},
        {1, -1},
        {-1, 1},
        {-1, -1}
    };

    for (const auto& direction : directions)
    {
        for (int i = 1; i < 8; ++i)
        {
            std::pair<int, int> newLocation = {
                pair.first + i * direction.first, pair.second + i * direction.second
            };
            if (!isPosInsideBoard(newLocation))
            {
                break;
            }
            if (isTileOccupiedByColor(newLocation, isWhite))
            {
                break;
            }
            moves.emplace_back(getBitBoardFromLocation(pair), getBitBoardFromLocation(newLocation));
            if (isTileOccupiedByColor(newLocation, !isWhite))
            {
                break;
            }
        }
    }
    return moves;
}

void Board::removePiece(uint64_t bitboard)
{
    uint64_t* bitBoards[] = {
        &whitePawnsBitBoard_, &whiteRooksBitBoard_, &whiteKnightsBitBoard_,
        &whiteBishopsBitBoard_, &whiteQueensBitBoard_, &whiteKingBitBoard_,
        &blackPawnsBitBoard_, &blackRooksBitBoard_, &blackKnightsBitBoard_,
        &blackBishopsBitBoard_, &blackQueensBitBoard_, &blackKingBitBoard_
    };

    for (auto& bitBoard : bitBoards)
    {
        if (*bitBoard & bitboard)
        {
            *bitBoard &= ~bitboard;
            break;
        }
    }
}
