#include "tile.hxx"

Tile::Tile(bool isMine)
        : adjacentTiles({}),
          numAdjMines(0),
          hasMine(isMine),
          isRevealed(false),
          isFlagged(false)

{

}

Tile::Tile()
        : adjacentTiles({}),
          numAdjMines(0),
          hasMine(false),
          isRevealed(false),
          isFlagged(false)
{

}

void
Tile::add_adjacent_tile(Tile* newTile)
{
    adjacentTiles.push_back(newTile);
    if (newTile->hasMine) {
        ++numAdjMines;
    }
}


void
Tile::reveal_tile()
{
    isRevealed = true;
}

void
Tile::flag_tile()
{
    isFlagged = true;
}

void
Tile::unflag_tile()
{
    isFlagged = false;
}


bool
Tile::revealed() const
{
    return isRevealed;
}

bool
Tile::mine() const
{
    return hasMine;
}

bool
Tile::flagged() const
{
    return isFlagged;
}
int
Tile::num_adj_mines() const
{
    return numAdjMines;
}

std::vector<Tile*>
Tile::adjtiles()
{
    return adjacentTiles;
}

