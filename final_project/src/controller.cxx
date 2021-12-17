#include "controller.hxx"

Controller::Controller(int size, int numMines)
        : model_(size, numMines),
          view_(model_),
          mouse_down_position_(ge211::Posn<int>(0,0))
{ }

Controller::Controller(int width, int height, int numMines)
        : model_(width, height, numMines),
        view_(model_),
        mouse_down_position_(ge211::Posn<int>(0,0))
{

}

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}
void
Controller::on_frame(double dt)
{
    if (!model_.is_game_over())
    {
        model_.time_update(dt);
    }
}
void
Controller::on_mouse_down(ge211::Mouse_button button, ge211::Posn<int> posn)
{
    mouse_down_position_ = posn;
}
///On a left click, play move or reset board, and on right click, place a flag, if the location is valid.
void
Controller::on_mouse_up(ge211::Mouse_button button, ge211::Posn<int> posn)
{
    if (posn.x > 16 * model_.board().width / 2 - 3 * 16 / 2 && posn.x < 16 * model_.board().width / 2 + 3 * 16 / 2 &&
    posn.y < 48 && view_.screen_to_board(posn) == view_.screen_to_board(mouse_down_position_))
    {
        model_.reset_model();
        view_.reset_view(model_);
    }
    else if (view_.screen_to_board(posn) ==
        view_.screen_to_board(mouse_down_position_)) {
        if (button == ge211::Mouse_button::left) {
            if (!model_.is_game_over()) {
                model_.play_move(view_.screen_to_board(posn));
            }
        }
        else if(button == ge211::Mouse_button::right)
            if (!model_.is_game_over()) {
                model_.place_flag(view_.screen_to_board(posn));
            }
    }
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

