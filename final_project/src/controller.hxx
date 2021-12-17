#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller(int size = 10, int numMines = 10);
    Controller(int width, int height, int numMines);

protected:
    void draw(ge211::Sprite_set& set) override;
    void on_frame(double dt) override;
    void on_mouse_down(ge211::Mouse_button button,ge211::Posn<int> posn)
    override;
    void on_mouse_up(ge211::Mouse_button button, ge211::Posn<int> posn)
    override;
    View::Dimensions initial_window_dimensions() const override;



private:
    Model model_;
    View view_;
    ge211::Posn<int> mouse_down_position_;
};
