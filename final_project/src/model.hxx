#pragma once

#include <ge211.hxx>
#include "tile.hxx"
#include <unordered_map>
#include <iostream>


class Model
{
public:
    /// Model dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Model positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// Model rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    /// Constructs a model with `size` as both its width and height.
    explicit Model(int size = 10, int mines = 10);

    /// Constructs a model with the given width, height, and mines.
    Model(int width, int height, int mines);

    ///Constructs a model with the given dimensions, locations
    /// of mines
    Model(int width,int height,std::vector<Model::Position> locs);


    /// Returns a rectangle containing all the positions of the board.
    /// This can be used to iterate over the positions.
    Rectangle board() const;

    /// Returns whether the game is finished. This is true when a mine is
    /// found or all tiles without mines have been found
    bool is_game_over() const;

    /// Returns whether the game is won. This is true when all none-mine tiles have been revealed without the player losing.
    bool is_game_won() const;

    ///Plays a move at the given tile. Checks to see if the tile has been
    /// revealed or not. If a player tries to play on a tile that has already
    /// been revealed, the game does nothing. Else, it reveals the tile and
    /// leads to game_over if there is a mine
    void play_move(Position);

    ///returns a pointer to the tile at a certain position in the model.
    Tile* operator[](const Position posn);

    ///Places a flag at the given position. Checks to see if the tile has
    /// been revealed first. if a player tries to place a flag on a tile that
    /// has already been revealed, the game does nothing. Else, it places the
    /// flag on the location.
    void place_flag(Position);

    ///keeps track of the time that has passed
    void time_update(double dt);

    /// returns the amount of time spent on the game
    double get_time() const;

    ///returns the number of mines - number of flags
    int get_diff () const;

    void reset_model();



    std::unordered_map<Position, Tile> tiles_;
    Position offending_mine = {0,0};
private:
    //
    // PRIVATE MEMBER VARIABLES
    // (Don't change these!)
    //

    bool game_over_ = false;
    int numMines_;
    int numFlags_;
    int numRevealedTiles_ = 0;
    int height_;
    int width_;
    double time;
    bool game_won_ = false;

    void play_move_helper(Tile* tile);

};
