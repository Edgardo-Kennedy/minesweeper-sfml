#include "Minesweeper.hpp"

int main()
{

    const int x_size{30};
    const int y_size{16};
    const int num_mines{99};

    Board game{x_size,
               y_size,
               num_mines,
               std::vector<std::vector<int>>(y_size, std::vector<int>(x_size, 0))};

    //game.display_board();
    game.load_sprites();
    game.create_margins();
    game.game_loop();
}