#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#include <vector>
#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>

class Board
{
private:
    // Board dimensions in number of squares
    int x_size;
    int y_size;

    // Total number of mines
    int num_mines;

    // matrix keeps track of the board (mine position and numbers)
    std::vector<std::vector<int>> matrix;
    // clicking_matrix keeps track of player moves
    std::vector<std::vector<int>> clicking_matrix;

    sf::RenderWindow window;

    // Texture atlas
    sf::Texture texture;

    // Rectangle shapes are for the margins of the board
    sf::RectangleShape left;
    sf::RectangleShape top;
    sf::RectangleShape right;
    sf::RectangleShape bottom;

    sf::RectangleShape score_left;
    sf::RectangleShape score_top;
    sf::RectangleShape score_right;
    sf::RectangleShape score_bottom;

    sf::RectangleShape mines_left;
    sf::RectangleShape mines_top;
    sf::RectangleShape mines_right;
    sf::RectangleShape mines_bottom;

    // corner sprites, numbers in doc
    sf::Sprite corner_1;
    sf::Sprite corner_2;
    sf::Sprite corner_3;
    sf::Sprite corner_4;
    sf::Sprite corner_5;

    // game sprites
    sf::Sprite unclicked;
    sf::Sprite holding;
    sf::Sprite empty;
    sf::Sprite number_1;
    sf::Sprite number_2;
    sf::Sprite number_3;
    sf::Sprite number_4;
    sf::Sprite number_5;
    sf::Sprite number_6;
    sf::Sprite number_7;
    sf::Sprite number_8;
    sf::Sprite mine;
    sf::Sprite clicked_mine;
    sf::Sprite wrong_flag;
    sf::Sprite flag;
    sf::Sprite happy;
    sf::Sprite happy_pressed;
    sf::Sprite surprised;
    sf::Sprite sunglasses;
    sf::Sprite dead;

public:
    Board(int x_size, int y_size, int num_mines, std::vector<std::vector<int>> matrix);

    // Visuals
    // These only relate to the initial loading of sprites and creation of shapes and color
    void load_sprites();   // Loading and setting up sprites
    void create_margins(); // Setting up margins
    void render_margins(); // Draw margins on screen

    // These generate the playing board
    void fill_board();
    int count_vicinity_mines(int x_position, int y_position);
    void display_board();
    void reset();

    // Methods relating to the actual playing of the game
    void check_surrounding_empties(int x_position, int y_position);
    void reveal_board_loss();
    bool minesweep();
    int count_vicinity_flags(int x_position, int y_position);
    bool check_win();
    void game_loop();
};

// Function to generate integers, between 0 and max_value
int RNG(int max_value);

#endif