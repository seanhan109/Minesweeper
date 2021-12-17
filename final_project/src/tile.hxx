#pragma once

#include <ge211.hxx>
#include <vector>

class Tile
{
public:

    /// Tile dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Tile positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// Tile rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

private:
    // vector of pointers to adjacent tiles from the current tile.
    std::vector<Tile*> adjacentTiles;

    //number of adjacent tiles that have mines; used to determine the number
    // to be revealed in view.
    int numAdjMines;

    // indicates whether the tile contains a mine or not.
    bool hasMine;

    // indicates whether the tile has been revealed or not
    bool isRevealed;

    /// indicates whether the tile has been flagged
    bool isFlagged;

public:

    //default constructor
    explicit Tile(bool isMine);

    Tile();


    ///adds an adjacent tile
    void add_adjacent_tile(Tile* newTile);

    ///reveals tile
    void reveal_tile();

    ///flags tile
    void flag_tile();

    ///unflags tile
    void unflag_tile();

    /// Determines if a tile has been revealed
    bool revealed() const;

    ///Determines if a tile has a mine
    bool mine() const;

    ///Determines if a tile is flagged
    bool flagged() const;

    ///Determines number of adjacent mines
    int num_adj_mines() const;

    std::vector<Tile*> adjtiles();

};
