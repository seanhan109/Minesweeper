#include "model.hxx"
#include <catch.hxx>

TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);
}

// These tests should demonstrate at least 5 of the functional
// requirements.
TEST_CASE("Basic test"){
    Model m(4,4,{{0,0},{1,1},{2,2},{3,3}});
    ///check that num_mines is 4 since no flags have been placed yet
    CHECK(m.get_diff() == 4);
    m.play_move(Model::Position(1,2));
    CHECK(m.tiles_.at(Model::Position(1,2)).revealed() == true);
    CHECK(m.tiles_.at(Model::Position(1,2)).num_adj_mines() == 2);
    m.play_move(Model::Position(0,1));
    CHECK(m.tiles_.at(Model::Position(1,2)).revealed() == true);
    CHECK(m.tiles_.at(Model::Position(1,2)).num_adj_mines() == 2);

    ///CHECK TO SEE IF ADJACENT TILES ARE REVEALED WHEN A TILE WITH NO ADJ
    /// MINES IS REVEALED
    CHECK(m.tiles_.at(Model::Position(2,1)).revealed() == false);
    m.play_move(Model::Position(3,0));
    CHECK(m.tiles_.at(Model::Position(3,0)).revealed()==true);
    CHECK(m.tiles_.at(Model::Position(1,2)).num_adj_mines() == 2);
    CHECK(m.tiles_.at(Model::Position(2,1)).revealed() == true);
    CHECK(m.tiles_.at(Model::Position(2,1)).num_adj_mines() == 2);
    CHECK(m.tiles_.at(Model::Position(0,3)).revealed() == false);

    ///CHECK THE PLACING OF FLAGS
    m.place_flag(Model::Position(0,0));
    CHECK(m.tiles_.at(Model::Position(0,0)).flagged() == true);
    CHECK(m.get_diff() == 3);
    m.place_flag(Model::Position(1,1));
    m.place_flag(Model::Position(2,2));
    m.place_flag(Model::Position(3,3));



    ///Play to Completion
    m.play_move(Model::Position(0,3));
    m.play_move(Model::Position(0,2));
    m.play_move(Model::Position(1,3));
    m.play_move(Model::Position(2,3));
    m.play_move(Model::Position(3,2));
    m.play_move(Model::Position(1,0));

    ///CHECK GAME OVER AND WON
    CHECK(m.is_game_over() == true);
    CHECK(m.is_game_won() == true);
}
TEST_CASE("LOST"){
    ///Creates a 3x3 grid with only the centre space {1,1} being safe
    Model m (3,3,{{0,0},{0,1},{0,2},{1,0},{1,2},{2,0},{2,1},{2,2}});
    CHECK(m.tiles_.at(Model::Position(1,1)).num_adj_mines() == 8);
    CHECK(m.get_diff() == 8);

    ///revealed a bomb/mine
    m.play_move(Model::Position(0,0));

    ///CHECK GAME_OVER AND LOST
    CHECK(m.is_game_over() == true);
    CHECK(m.is_game_won() == false);
}
