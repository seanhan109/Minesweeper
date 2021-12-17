#include "view.hxx"

using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

static int const grid_size  = 16;

View::View(Model& model)
            :model_(model),
            flag_sprite("flagged.png"),
            bomb_sprite("bomb.png"),
             hidden_tile_sprite("facingDown.png"),
             face_win("facewin.png"),
             face_dead("facedead.png"),
             reset("reset.png"),
             offending_mine("offending_mine.png"),
             time_sprite("000", ge211::Font{"sans.ttf", 2 * grid_size}),
             num_flag_sprite("000", ge211::Font{"sans.ttf", 2 * grid_size}),
             red_flag_sprite("red_flag.png"),
             revealed_tile_sprites({ge211::Image_sprite("0.png"), ge211::Image_sprite("1.png"),
                                    ge211::Image_sprite("2.png"), ge211::Image_sprite("3.png"),
                                    ge211::Image_sprite("4.png"), ge211::Image_sprite("5.png"),
                                    ge211::Image_sprite("6.png"), ge211::Image_sprite("7.png"),
                                    ge211::Image_sprite("8.png")})
{}

void
View::draw(ge211::Sprite_set &set)
{
    for (auto iter = model_.tiles_.begin(); iter != model_.tiles_.end(); ++iter)
    {
        if (model_.is_game_over())
        {
            if (model_.is_game_won())
            {
                if (iter->second.mine())
                {
                    set.add_sprite(flag_sprite, board_to_screen(iter->first));
                }
                else
                {
                    set.add_sprite(revealed_tile_sprites[iter->second.num_adj_mines()], board_to_screen(iter->first));
                }
            }
            else
            {
                if(iter->first == model_.offending_mine)
                {
                    set.add_sprite(offending_mine, board_to_screen(iter->first));
                }
                else if (iter->second.mine())
                {
                    set.add_sprite(bomb_sprite, board_to_screen(iter->first));
                }
                else if (iter->second.revealed())
                {
                    set.add_sprite(revealed_tile_sprites[iter->second.num_adj_mines()], board_to_screen(iter->first));
                }
                else if (iter->second.flagged()) {
                    set.add_sprite(red_flag_sprite, board_to_screen(iter->first));
                }
                else
                {
                    set.add_sprite(hidden_tile_sprite, board_to_screen(iter->first));
                }
            }
        }
        else if (iter->second.flagged())
        {
            set.add_sprite(flag_sprite, board_to_screen(iter->first));
        }
        else if (iter->second.revealed())
        {
            set.add_sprite(revealed_tile_sprites[iter->second.num_adj_mines()], board_to_screen(iter->first));
        }
        else
        {
            set.add_sprite(hidden_tile_sprite, board_to_screen(iter->first));
        }

    }
    ge211::Font sans{"sans.ttf", model_.board().width * 3};
    ge211::Text_sprite::Builder time_builder(sans);
    std::string elapsedTime = std::to_string((int)model_.get_time() / 100) + std::to_string((int)model_.get_time() / 10 % 10)
            + std::to_string((int)model_.get_time() % 10);
    time_builder << elapsedTime;
    time_sprite.reconfigure(time_builder);
    set.add_sprite(time_sprite, {0,0});
    Position face_posn = {grid_size * model_.board().width / 2 - 3 * grid_size / 2,0};
    if (!model_.is_game_over())
    {
        set.add_sprite(reset,face_posn);
    }
    else if (model_.is_game_won())
    {
        set.add_sprite(face_win, face_posn);
    }
    else
    {
        set.add_sprite(face_dead, face_posn);
    }
    ge211::Text_sprite::Builder flag_builder(sans);
    std::string flagCount = std::to_string(model_.get_diff() / 100) + std::to_string(model_.get_diff() / 10 % 10)
            + std::to_string(model_.get_diff() % 10);
    flag_builder << flagCount;
    num_flag_sprite.reconfigure(flag_builder);
    set.add_sprite(num_flag_sprite, face_posn.right_by(3 * grid_size));
}

View::Position
View::board_to_screen(Model::Position physical) const
{
    return {physical.x*grid_size, (physical.y + 3)*grid_size};
}

Model::Position
View::screen_to_board(View::Position logical) const
{
    return {logical.x / grid_size, logical.y / grid_size - 3};
}

View::Dimensions
View::initial_window_dimensions() const
{
    Dimensions d = grid_size * model_.board().dimensions();
    d.height += grid_size * 3;
    return d;
}


void
View::reset_view(Model& model)
{
    model_ = model;
}




