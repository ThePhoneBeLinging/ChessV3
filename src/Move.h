//
// Created by Elias Aggergaard Larsen on 26/09/2024.
//

#ifndef MOVE_H
#define MOVE_H
#include <cassert>
#include <cstdint>

class Move
{
public:
    Move(uint64_t from, uint64_t to) : from(from), to(to), promotion(0), isCastle(false)
    {
    };

    bool operator==(const Move& rhs) const
    {
        return from == rhs.from && to == rhs.to;
    }

    uint64_t from;
    uint64_t to;
    char promotion;
    bool isCastle;
    uint64_t capturedPiece = 0;

    std::string toString() const
    {
        return squareToString(bitScanForward(from)) + squareToString(bitScanForward(to));
    }

private:
    static int bitScanForward(uint64_t bb)
    {
        assert(bb != 0 && (bb & (bb - 1)) == 0); // ensure only 1 bit is set
#if defined(_MSC_VER)
        unsigned long index;
        _BitScanForward64(&index, bb);
        return static_cast<int>(index);
#elif defined(__GNUC__) || defined(__clang__)
        return __builtin_ctzll(bb); // count trailing zeros
#else
        // Fallback method (portable)
        for (int i = 0; i < 64; i++) {
            if (bb & (1ULL << i)) return i;
        }
        return -1; // shouldn't happen
#endif
    }

    static std::string squareToString(int index)
    {
        char file = 'a' + (index % 8);
        char rank = '1' + (index / 8);
        return std::string{file, rank};
    }
};

#endif //MOVE_H

