#pragma once

#include "model.hxx"

#include<string>

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    explicit View(Model& model);

    void draw(ge211::Sprite_set& set);

    void reset_view(Model& model);

    View::Position board_to_screen(Model::Position physical) const;
    Model::Position screen_to_board(View::Position logical) const;
    Dimensions initial_window_dimensions() const;


private:
    Model& model_;
    ge211::Image_sprite const flag_sprite;
    ge211::Image_sprite const bomb_sprite;
    ge211::Image_sprite const hidden_tile_sprite;
    ge211::Image_sprite const face_win;
    ge211::Image_sprite const face_dead;
    ge211::Image_sprite const reset;
    ge211::Image_sprite const offending_mine;
    ge211::Text_sprite time_sprite;
    ge211::Text_sprite num_flag_sprite;
    ge211::Image_sprite red_flag_sprite;
    std::vector<ge211::Image_sprite> const revealed_tile_sprites;
};
