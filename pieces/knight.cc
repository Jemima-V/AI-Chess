#include "knight.h"
#include "board.h"

// ctor
Knight::Knight(int owner, bool captured, char id): Pieces(owner, captured, id) {}

// dtor
Knight::~Knight() {}

bool Knight::validMove(Position start, Position end, Board* board) const {
    int rankChange = end.rank - start.rank;
    int fileChange = end.file - start.file;
    // 4 possible moves:
    if (rankChange == 1 && (fileChange == 2 || fileChange == -2)) {
        // move +1 vertically (rank) and then move +2/-2 horizontally (file)
        return true;
    } else if (rankChange == -1 && (fileChange == 2 || fileChange == -2)) {
        // move -1 vertically (rank) and then move +2/-2 horizontally (file)
        return true;
    } else if (fileChange == 1 && (rankChange == 2 || rankChange == -2)) {
        // move +1 horizontally (file) and then move +2/-2 vertically (rank)
        return true;
    } else if (fileChange == -1 && (rankChange == 2 || rankChange == -2)) {
        // move -1 horizontally (file) and then move +2/-2 vertically (rank)
        return true;
    } else {
        return false;
    }
}
