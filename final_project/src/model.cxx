#include "model.hxx"


using namespace ge211;


Model::Model(int size, int mines)
        : Model(size, size, mines)
{ }

///Constructor for model, constructs board and places mines at random positions
Model::Model(int width, int height, int mines)
        :numMines_(mines),
         numFlags_(0),
         height_(height),
         width_(width),
         time(0)

{   bool posns [width][height];
    for (int i = 0;i<width;i++){
        for (int j = 0;j<height;j++){
            posns[i][j] = false;
        }
    }
    int m = 0;
    ge211::Random_source<int> c(0, width-1);
    while (m<mines) {
        int x = c.next();
        int y = c.next();
        if(!posns[x][y]){
            posns[x][y] = true;
            m++;
        }
    }

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            tiles_.emplace(Position(i, j), Tile(posns[i][j]));
            if (i == 0)
            {
                if (j > 0)
                {
                    tiles_[Position(i,j)].add_adjacent_tile(&tiles_[Position
                            (i,j - 1)]);
                    tiles_[Position(i, j - 1)].add_adjacent_tile
                            (&tiles_[Position(i, j)]);
                }
            }
            else if (j == 0)
            {
                if (i > 0) {
                    tiles_[Position(i, j)].add_adjacent_tile(&tiles_[Position
                            (i - 1, j)]);
                    tiles_[Position(i - 1, j)].add_adjacent_tile
                            (&tiles_[Position(i, j)]);

                    tiles_[Position(i, j)].add_adjacent_tile(&tiles_[Position(i - 1, j + 1)]);
                    tiles_[Position(i - 1, j + 1)].add_adjacent_tile(&tiles_[Position(i,j)]);
                }
            }
            else
            {
                tiles_[Position(i,j)].add_adjacent_tile(&tiles_[Position
                        (i,j - 1)]);
                tiles_[Position(i, j - 1)].add_adjacent_tile
                        (&tiles_[Position(i, j)]);
                tiles_[Position(i,j)].add_adjacent_tile(&tiles_[Position
                        (i - 1,j)]);
                tiles_[Position(i - 1, j)].add_adjacent_tile
                        (&tiles_[Position(i, j)]);
                tiles_[Position(i,j)].add_adjacent_tile(&tiles_[Position
                        (i - 1,j - 1)]);
                tiles_[Position(i - 1, j - 1)].add_adjacent_tile
                        (&tiles_[Position(i, j)]);
                if (j != width_ - 1) {
                    tiles_[Position(i, j)].add_adjacent_tile(&tiles_[Position(i - 1, j + 1)]);
                    tiles_[Position(i - 1, j + 1)].add_adjacent_tile(&tiles_[Position(i, j)]);
                }
            }
        }
    }

}

Model::Model(int width, int height,std::vector<Model::Position>locs)
        :numMines_(locs.size()),
         numFlags_(0),
         height_(height),
         width_(width),
         time(0)

{   bool posns [width][height];
    for (int i = 0;i<width;i++){
        for (int j = 0;j<height;j++){
            posns[i][j] = false;
        }
    }
    for (unsigned int i = 0;i<locs.size();i++){
        posns[locs[i].x][locs[i].y] = true;
    }

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            tiles_.emplace(Position(i, j), Tile(posns[i][j]));
            if (i == 0)
            {
                if (j > 0)
                {
                    tiles_[Position(i,j)].add_adjacent_tile(&tiles_[Position
                            (i,j - 1)]);
                    tiles_[Position(i, j - 1)].add_adjacent_tile
                            (&tiles_[Position(i, j)]);
                }
            }
            else if (j == 0)
            {
                if (i > 0) {
                    tiles_[Position(i, j)].add_adjacent_tile(&tiles_[Position
                            (i - 1, j)]);
                    tiles_[Position(i - 1, j)].add_adjacent_tile
                            (&tiles_[Position(i, j)]);

                    tiles_[Position(i, j)].add_adjacent_tile(&tiles_[Position(i - 1, j + 1)]);
                    tiles_[Position(i - 1, j + 1)].add_adjacent_tile(&tiles_[Position(i,j)]);
                }
            }
            else
            {
                tiles_[Position(i,j)].add_adjacent_tile(&tiles_[Position
                        (i,j - 1)]);
                tiles_[Position(i, j - 1)].add_adjacent_tile
                        (&tiles_[Position(i, j)]);
                tiles_[Position(i,j)].add_adjacent_tile(&tiles_[Position
                        (i - 1,j)]);
                tiles_[Position(i - 1, j)].add_adjacent_tile
                        (&tiles_[Position(i, j)]);
                tiles_[Position(i,j)].add_adjacent_tile(&tiles_[Position
                        (i - 1,j - 1)]);
                tiles_[Position(i - 1, j - 1)].add_adjacent_tile
                        (&tiles_[Position(i, j)]);
                if (j != width_ - 1) {
                    tiles_[Position(i, j)].add_adjacent_tile(&tiles_[Position(i - 1, j + 1)]);
                    tiles_[Position(i - 1, j + 1)].add_adjacent_tile(&tiles_[Position(i, j)]);
                }
            }
        }
    }

}

///returns all positions on the board
Model::Rectangle
Model::board() const
{
    return Rectangle::from_top_left(the_origin, Dimensions(height_, width_));
}

///checks state of game to see if game is over
bool
Model::is_game_over() const
{
    return game_over_;
}

bool
Model::is_game_won() const {
    return game_won_;
}
void
Model::play_move(Position pos)
{
    if (is_game_over()){
        throw Client_logic_error("Model::play_move: game over");
    }
    if (tiles_.find(pos) == tiles_.end())
    {
        throw Client_logic_error("Model::play_move: no such move");
    }
    if (!tiles_[pos].flagged() && tiles_[pos].mine())
    {
        offending_mine = pos;
    }
    play_move_helper(&tiles_[pos]);
}

void
Model::play_move_helper(Tile* tile)
{
    /// do nothing if flagged or revealed
    if (tile->flagged() || tile->revealed())
    {
        return;
    }
    else if (tile->mine())
    {
        tile->reveal_tile();
        ++numRevealedTiles_;
        game_over_ = true;
    }
    else if (tile->num_adj_mines() > 0)
    {
        tile->reveal_tile();
        ++numRevealedTiles_;
    }
    else if (tile->num_adj_mines() == 0)
    {
        tile->reveal_tile();
        ++numRevealedTiles_;
        for (unsigned int i = 0; i < tile->adjtiles().size(); ++i)
        {
            if (!tile->adjtiles()[i]->revealed() && tile->adjtiles()[i]->num_adj_mines() == 0)
            {
                play_move_helper(tile->adjtiles()[i]);
            }
            else if (!tile->adjtiles()[i]->revealed())
            {
                tile->adjtiles()[i]->reveal_tile();
                ++numRevealedTiles_;
            }
        }
    }
    if (numRevealedTiles_ + numMines_ == width_ * height_ && !game_over_)
    {
        game_over_ = true;
        game_won_ = true;
    }
}

void
Model::time_update(double dt)
{
    time += dt;
}

double
Model::get_time() const
{
    return time;
}

int
Model::get_diff() const
{
    return numMines_ - numFlags_;
}

Tile*
Model::operator[](const Position posn)
{
    if (tiles_.find(posn) == tiles_.end()) {
        return nullptr;
    }
    else
    {
        return &tiles_[posn];
    }
}

void
Model::place_flag(Position pos)
{
    if (is_game_over()){
        throw Client_logic_error("Model::play_move: game over");
    }
    else if (tiles_.find(pos) == tiles_.end())
    {
        throw Client_logic_error("Model::place_flag: no such tile at position");
    }
    else if (!tiles_[pos].revealed())
    {
        if (tiles_[pos].flagged())
        {
            tiles_[pos].unflag_tile();
            --numFlags_;
        }
        else if (get_diff() > 0)
        {
            tiles_[pos].flag_tile();
            ++numFlags_;
        }
    }
}

void
Model::reset_model()
{
    tiles_.clear();
    game_over_ = false;
    game_won_ = false;
    time = 0;
    numRevealedTiles_ = 0;
    numFlags_ = 0;
    bool posns [width_][height_];
    for (int i = 0;i<width_;i++){
        for (int j = 0;j<height_;j++){
            posns[i][j] = false;
        }
    }
    int m = 0;
    ge211::Random_source<int> c(0, width_-1);
    while (m<numMines_) {
        int x = c.next();
        int y = c.next();
        if(!posns[x][y]){
            posns[x][y] = true;
            m++;
        }
    }

    for (int i = 0; i < width_; ++i)
    {
        for (int j = 0; j < height_; ++j)
        {
            tiles_.emplace(Position(i, j), Tile(posns[i][j]));
            if (i == 0)
            {
                if (j > 0)
                {
                    tiles_[Position(i,j)].add_adjacent_tile(&tiles_[Position
                            (i,j - 1)]);
                    tiles_[Position(i, j - 1)].add_adjacent_tile
                            (&tiles_[Position(i, j)]);
                }
            }
            else if (j == 0)
            {
                if (i > 0) {
                    tiles_[Position(i, j)].add_adjacent_tile(&tiles_[Position
                            (i - 1, j)]);
                    tiles_[Position(i - 1, j)].add_adjacent_tile
                            (&tiles_[Position(i, j)]);

                    tiles_[Position(i, j)].add_adjacent_tile(&tiles_[Position(i - 1, j + 1)]);
                    tiles_[Position(i - 1, j + 1)].add_adjacent_tile(&tiles_[Position(i,j)]);
                }
            }
            else
            {
                tiles_[Position(i,j)].add_adjacent_tile(&tiles_[Position
                        (i,j - 1)]);
                tiles_[Position(i, j - 1)].add_adjacent_tile
                        (&tiles_[Position(i, j)]);
                tiles_[Position(i,j)].add_adjacent_tile(&tiles_[Position
                        (i - 1,j)]);
                tiles_[Position(i - 1, j)].add_adjacent_tile
                        (&tiles_[Position(i, j)]);
                tiles_[Position(i,j)].add_adjacent_tile(&tiles_[Position
                        (i - 1,j - 1)]);
                tiles_[Position(i - 1, j - 1)].add_adjacent_tile
                        (&tiles_[Position(i, j)]);
                if (j != width_ - 1) {
                    tiles_[Position(i, j)].add_adjacent_tile(&tiles_[Position(i - 1, j + 1)]);
                    tiles_[Position(i - 1, j + 1)].add_adjacent_tile(&tiles_[Position(i, j)]);
                }
            }
        }
    }

}


