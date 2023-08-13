#include "Minesweeper.hpp"

// Constructor
Board::Board(int x_size, int y_size, int num_mines, std::vector<std::vector<int>> matrix)
    : x_size{x_size},
      y_size{y_size},
      num_mines{num_mines},
      matrix{matrix},
      clicking_matrix{matrix},
      window{sf::VideoMode(504, 321), "Minesweeper"}
{
}

// Loading the texture and then generating the sprites
// There are very few sprites that are constantly in use so they're all
// loaded and ready to go at all times
void Board::load_sprites()
{

    if (!texture.loadFromFile("minesweeper-sprites.png"))
    {
        std::cout << "Couldn't load sprites!" << std::endl;
    }

    // Corner sprites
    corner_1.setTexture(texture);
    corner_1.setTextureRect(sf::IntRect(0, 85, 3, 3));

    corner_2.setTexture(texture);
    corner_2.setTextureRect(sf::IntRect(4, 85, 3, 3));

    corner_3.setTexture(texture);
    corner_3.setTextureRect(sf::IntRect(8, 85, 3, 3));

    corner_4.setTexture(texture);
    corner_4.setTextureRect(sf::IntRect(12, 85, 3, 3));

    corner_5.setTexture(texture);
    corner_5.setTextureRect(sf::IntRect(16, 85, 3, 3));

    // Playing sprites
    unclicked.setTexture(texture);
    unclicked.setTextureRect(sf::IntRect(0, 51, 16, 16));

    holding.setTexture(texture);
    holding.setTextureRect(sf::IntRect(17, 51, 16, 16));

    empty.setTexture(texture);
    empty.setTextureRect(sf::IntRect(17, 51, 16, 16));

    number_1.setTexture(texture);
    number_1.setTextureRect(sf::IntRect(0, 68, 16, 16));

    number_2.setTexture(texture);
    number_2.setTextureRect(sf::IntRect(17, 68, 16, 16));

    number_3.setTexture(texture);
    number_3.setTextureRect(sf::IntRect(34, 68, 16, 16));

    number_4.setTexture(texture);
    number_4.setTextureRect(sf::IntRect(51, 68, 16, 16));

    number_5.setTexture(texture);
    number_5.setTextureRect(sf::IntRect(68, 68, 16, 16));

    number_6.setTexture(texture);
    number_6.setTextureRect(sf::IntRect(85, 68, 16, 16));

    number_7.setTexture(texture);
    number_7.setTextureRect(sf::IntRect(102, 68, 16, 16));

    number_8.setTexture(texture);
    number_8.setTextureRect(sf::IntRect(119, 68, 16, 16));

    mine.setTexture(texture);
    mine.setTextureRect(sf::IntRect(85, 51, 16, 16));

    clicked_mine.setTexture(texture);
    clicked_mine.setTextureRect(sf::IntRect(12, 51, 16, 16));

    wrong_flag.setTexture(texture);
    wrong_flag.setTextureRect(sf::IntRect(119, 51, 16, 16));

    flag.setTexture(texture);
    flag.setTextureRect(sf::IntRect(34, 51, 16, 16));

    happy.setTexture(texture);
    happy.setTextureRect(sf::IntRect(0, 24, 26, 26));
    happy.setPosition(sf::Vector2f(239.f, 14.f));

    happy_pressed.setTexture(texture);
    happy_pressed.setTextureRect(sf::IntRect(27, 24, 26, 26));
    happy_pressed.setPosition(sf::Vector2f(239.f, 14.f));

    surprised.setTexture(texture);
    surprised.setTextureRect(sf::IntRect(54, 24, 26, 26));
    surprised.setPosition(sf::Vector2f(239.f, 14.f));

    sunglasses.setTexture(texture);
    sunglasses.setTextureRect(sf::IntRect(81, 24, 26, 26));
    sunglasses.setPosition(sf::Vector2f(239.f, 14.f));

    dead.setTexture(texture);
    dead.setTextureRect(sf::IntRect(108, 24, 26, 26));
    dead.setPosition(sf::Vector2f(239.f, 14.f));
}

// Creating the shapes that make up the margins that surround the board
// No sprites here, just using sfml predefined shapes
void Board::create_margins()
{

    left.setSize(sf::Vector2f(3.f, 318.f));
    left.setFillColor(sf::Color::White);
    left.setPosition(sf::Vector2f(0.f, 0.f));

    top.setSize(sf::Vector2f(498.f, 3.f));
    top.setFillColor(sf::Color::White);
    top.setPosition(sf::Vector2f(3.f, 0.f));

    right.setSize(sf::Vector2f(3.f, 318.f));
    right.setFillColor(sf::Color(128, 128, 128));
    right.setPosition(sf::Vector2f(501.3, 3.f));

    bottom.setSize(sf::Vector2f(498.f, 3.f));
    bottom.setFillColor(sf::Color(128, 128, 128));
    bottom.setPosition(sf::Vector2f(3.f, 318.f));

    score_left.setSize(sf::Vector2f(3.f, 35.f));
    score_left.setFillColor(sf::Color(128, 128, 128));
    score_left.setPosition(sf::Vector2f(9.f, 8.f));

    score_top.setSize(sf::Vector2f(480.f, 3.f));
    score_top.setFillColor(sf::Color(128, 128, 128));
    score_top.setPosition(sf::Vector2f(12.f, 8.f));

    score_right.setSize(sf::Vector2f(3.f, 35.f));
    score_right.setFillColor(sf::Color::White);
    score_right.setPosition(sf::Vector2f(492.f, 11.f));

    score_bottom.setSize(sf::Vector2f(480.f, 3.f));
    score_bottom.setFillColor(sf::Color::White);
    score_bottom.setPosition(sf::Vector2f(12.f, 43.f));

    mines_left.setSize(sf::Vector2f(3.f, 259.f));
    mines_left.setFillColor(sf::Color(128, 128, 128));
    mines_left.setPosition(sf::Vector2f(9.f, 51.f));

    mines_top.setSize(sf::Vector2f(480.f, 3.f));
    mines_top.setFillColor(sf::Color(128, 128, 128));
    mines_top.setPosition(sf::Vector2f(12.f, 51.f));

    mines_right.setSize(sf::Vector2f(3.f, 259.f));
    mines_right.setFillColor(sf::Color::White);
    mines_right.setPosition(sf::Vector2f(492.f, 54.f));

    mines_bottom.setSize(sf::Vector2f(480.f, 3.f));
    mines_bottom.setFillColor(sf::Color::White);
    mines_bottom.setPosition(sf::Vector2f(12.f, 310.f));
}

void Board::render_margins()
{
    window.draw(left);
    window.draw(top);
    window.draw(right);
    window.draw(bottom);
    window.draw(score_left);
    window.draw(score_top);
    window.draw(score_right);
    window.draw(score_bottom);
    window.draw(mines_left);
    window.draw(mines_top);
    window.draw(mines_right);
    window.draw(mines_bottom);

    corner_1.setPosition(sf::Vector2f(0.f, 318.f));
    window.draw(corner_1);

    corner_1.setPosition(sf::Vector2f(501.f, 0.f));
    window.draw(corner_1);

    corner_2.setPosition(sf::Vector2f(9.f, 43.f));
    window.draw(corner_2);

    corner_3.setPosition(sf::Vector2f(9.f, 310.f));
    window.draw(corner_3);

    corner_4.setPosition(sf::Vector2f(492.f, 8.f));
    window.draw(corner_4);

    corner_5.setPosition(sf::Vector2f(492.f, 51.f));
    window.draw(corner_5);
}

// Method that randomly generates the playing field
void Board::fill_board()
{

    int x_position;
    int y_position;

    // This first loop decides where the mines go
    for (int i = 0; i < num_mines; i++)
    {
        do
        {
            x_position = RNG(x_size);
            y_position = RNG(y_size);
        } while (matrix.at(y_position).at(x_position) != 0);
        matrix.at(y_position).at(x_position) = 9;
    }

    // This second loop checks what little number goes in every square
    for (int i = 0; i < y_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            if (matrix.at(i).at(j) != 9)
            {
                matrix.at(i).at(j) = count_vicinity_mines(j, i);
            }
        }
    }
}

// Method to check the surroundings of a given square to count how many mines they're next to
int Board::count_vicinity_mines(int x_position, int y_position)
{

    int count{0};

    if (y_position > 0)
    {
        if (x_position > 0)
        {
            if (matrix.at(y_position - 1).at(x_position - 1) == 9)
            {
                count++;
            }
        }

        if (matrix.at(y_position - 1).at(x_position) == 9)
        {
            count++;
        }

        if (x_position < x_size - 1)
        {
            if (matrix.at(y_position - 1).at(x_position + 1) == 9)
            {
                count++;
            }
        }
    }

    if (y_position < y_size - 1)
    {
        if (x_position > 0)
        {
            if (matrix.at(y_position + 1).at(x_position - 1) == 9)
            {
                count++;
            }
        }

        if (matrix.at(y_position + 1).at(x_position) == 9)
        {
            count++;
        }

        if (x_position < x_size - 1)
        {
            if (matrix.at(y_position + 1).at(x_position + 1) == 9)
            {
                count++;
            }
        }
    }

    if (x_position > 0)
    {
        if (matrix.at(y_position).at(x_position - 1) == 9)
        {
            count++;
        }
    }

    if (x_position < x_size - 1)
    {
        if (matrix.at(y_position).at(x_position + 1) == 9)
        {
            count++;
        }
    }

    return count;
}

// This displays the numbers on the terminal
// Not really used in the final code
// Useful to check if the algorithm is working during development
void Board::display_board()
{

    for (int i = 0; i < y_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            if (matrix.at(i).at(j) != 0)
            {
                std::cout << matrix.at(i).at(j) << " ";
            }
            else
            {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
}

void Board::reset()
{

    for (int i = 0; i < y_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            matrix.at(i).at(j) = 0;
            clicking_matrix.at(i).at(j) = 0;
        }
    }
    fill_board();
}

void Board::check_surrounding_empties(int x_position, int y_position)
{

    if (y_position > 0)
    {

        if (matrix.at(y_position - 1).at(x_position) == 0)
        {
            if (clicking_matrix.at(y_position - 1).at(x_position) == 0)
            {
                clicking_matrix.at(y_position - 1).at(x_position) = 1;
                check_surrounding_empties(x_position, y_position - 1);
            }
        }
        else
        {
            clicking_matrix.at(y_position - 1).at(x_position) = 1;
        }

        if (x_position > 0)
        {
            if (matrix.at(y_position - 1).at(x_position - 1) == 0)
            {
                if (clicking_matrix.at(y_position - 1).at(x_position - 1) == 0)
                {
                    clicking_matrix.at(y_position - 1).at(x_position - 1) = 1;
                    check_surrounding_empties(x_position - 1, y_position - 1);
                }
            }
            else
            {
                clicking_matrix.at(y_position - 1).at(x_position - 1) = 1;
            }
        }

        if (x_position < x_size - 1)
        {
            if (matrix.at(y_position - 1).at(x_position + 1) == 0)
            {
                if (clicking_matrix.at(y_position - 1).at(x_position + 1) == 0)
                {
                    clicking_matrix.at(y_position - 1).at(x_position + 1) = 1;
                    check_surrounding_empties(x_position + 1, y_position - 1);
                }
            }
            else
            {
                clicking_matrix.at(y_position - 1).at(x_position + 1) = 1;
            }
        }
    }

    if (x_position > 0)
    {
        if (matrix.at(y_position).at(x_position - 1) == 0)
        {
            if (clicking_matrix.at(y_position).at(x_position - 1) == 0)
            {
                clicking_matrix.at(y_position).at(x_position - 1) = 1;
                check_surrounding_empties(x_position - 1, y_position);
            }
        }
        else
        {
            clicking_matrix.at(y_position).at(x_position - 1) = 1;
        }
    }

    if (x_position < x_size - 1)
    {
        if (matrix.at(y_position).at(x_position + 1) == 0)
        {
            if (clicking_matrix.at(y_position).at(x_position + 1) == 0)
            {
                clicking_matrix.at(y_position).at(x_position + 1) = 1;
                check_surrounding_empties(x_position + 1, y_position);
            }
        }
        else
        {
            clicking_matrix.at(y_position).at(x_position + 1) = 1;
        }
    }

    if (y_position < y_size - 1)
    {

        if (matrix.at(y_position + 1).at(x_position) == 0)
        {
            if (clicking_matrix.at(y_position + 1).at(x_position) == 0)
            {
                clicking_matrix.at(y_position + 1).at(x_position) = 1;
                check_surrounding_empties(x_position, y_position + 1);
            }
        }
        else
            clicking_matrix.at(y_position + 1).at(x_position) = 1;

        if (x_position > 0)
        {
            if (matrix.at(y_position + 1).at(x_position - 1) == 0)
            {
                if (clicking_matrix.at(y_position + 1).at(x_position - 1) == 0)
                {
                    clicking_matrix.at(y_position + 1).at(x_position - 1) = 1;
                    check_surrounding_empties(x_position - 1, y_position + 1);
                }
            }
            else
            {
                clicking_matrix.at(y_position + 1).at(x_position - 1) = 1;
            }
        }

        if (x_position < x_size - 1)
        {
            if (matrix.at(y_position + 1).at(x_position + 1) == 0)
            {
                if (clicking_matrix.at(y_position + 1).at(x_position + 1) == 0)
                {
                    clicking_matrix.at(y_position + 1).at(x_position + 1) = 1;
                    check_surrounding_empties(x_position + 1, y_position + 1);
                }
            }
            else
            {
                clicking_matrix.at(y_position + 1).at(x_position + 1) = 1;
            }
        }
    }
}

void Board::reveal_board_loss()
{
    for (int i = 0; i < y_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            if (matrix.at(i).at(j) == 9 && clicking_matrix.at(i).at(j) == 0)
            {
                clicking_matrix.at(i).at(j) = 1;
            }
            if (matrix.at(i).at(j) != 9 && clicking_matrix.at(i).at(j) == 2)
            {
                clicking_matrix.at(i).at(j) = 4;
            }
        }
    }
}

bool Board::minesweep()
{
    bool still_going{true};
    sf::Sprite sprite;
    for (int i = 0; i < y_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            if (clicking_matrix.at(i).at(j) == 1)
            {

                switch (matrix.at(i).at(j))
                {
                case 0:
                    check_surrounding_empties(j, i);
                    sprite = empty;
                    break;
                case 1:
                    sprite = number_1;
                    break;
                case 2:
                    sprite = number_2;
                    break;
                case 3:
                    sprite = number_3;
                    break;
                case 4:
                    sprite = number_4;
                    break;
                case 5:
                    sprite = number_5;
                    break;
                case 6:
                    sprite = number_6;
                    break;
                case 7:
                    sprite = number_7;
                    break;
                case 8:
                    sprite = number_8;
                    break;
                case 9:
                    sprite = mine;
                    reveal_board_loss();
                    still_going = false;
                    break;
                }
            }
            else if (clicking_matrix.at(i).at(j) == 2)
            {
                sprite = flag;
            }
            else if (clicking_matrix.at(i).at(j) == 3)
            {
                sprite = empty;
            }
            else if (clicking_matrix.at(i).at(j) == 4)
            {
                sprite = wrong_flag;
            }
            else
            {
                sprite = unclicked;
            }
            sprite.setPosition(sf::Vector2f(16 * j + 12, 16 * i + 54));
            window.draw(sprite);
        }
    }
    return still_going;
}


// This is executed at the end of each iteration of the gameloop to check if
// the game has been won
bool Board::check_win()
{

    bool won{true};
    for (int i = 0; i < y_size && won; i++)
    {
        for (int j = 0; j < x_size && won; j++)
        {
            if (matrix.at(i).at(j) != 9 && clicking_matrix.at(i).at(j) != 1)
            {
                won = false;
            }
        }
    }

    return won;
}

void Board::game_loop()
{

    fill_board();
    window.setVerticalSyncEnabled(true);
    bool still_going{true};
    bool won{false};
    sf::Event event;
    int x_pixel;
    int y_pixel;
    int x_square;
    int y_square;
    int flag_count;

    while (window.isOpen())
    {

        // Rendering the outline
        window.clear(sf::Color(192, 192, 192));
        render_margins();

        if (won)
        {
            still_going = false;
            window.draw(sunglasses);
        }
        else if (still_going)
        {
            window.draw(happy);
        }
        else
        {
            window.draw(dead);
        }

        // We check what the player does
        while (window.pollEvent(event))
        {

            // Ending the game
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Pressing a mouse button
            // This "if" doesn't end until the button is released
            if (event.type == sf::Event::MouseButtonPressed)
            {

                // We store the coordinates of the mouse press
                x_pixel = event.mouseButton.x;
                y_pixel = event.mouseButton.y;

                // Was the smiley pressed?
                // if so, display pressed smiley until mouse button is released
                if (x_pixel > 239 && x_pixel < 264 && y_pixel > 14 && y_pixel < 39)
                {
                    window.draw(happy_pressed);
                    still_going = minesweep();
                    window.display();

                    // Was a square on the board pressed?
                    // if so, minesweep
                }
                else if (x_pixel > 11 && x_pixel < 492 && y_pixel > 53 && y_pixel < 310)
                {
                    // still_going means player hasn't lost the game
                    if (still_going)
                    {
                        // Calculating what square is pressed
                        x_square = (x_pixel - 12) / 16;
                        y_square = (y_pixel - 54) / 16;

                        // If it was the left button, show that the square is being pressed
                        // on the clicking_matrix:
                        // 0 means unclicked
                        // 1 means clicked and released
                        // 2 means flagged
                        // 3 means clicked but hasn't been released
                        // 4 means wrongly flagged square
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            if (clicking_matrix.at(y_square).at(x_square) == 0)
                            {
                                clicking_matrix.at(y_square).at(x_square) = 3;
                                still_going = minesweep();
                                window.display();
                            }

                            // Right mouse button
                        }
                        else if (event.mouseButton.button == sf::Mouse::Right)
                        {
                            if (clicking_matrix.at(y_square).at(x_square) == 0)
                            {
                                // Lay flag
                                clicking_matrix.at(y_square).at(x_square) = 2;
                            }
                            else if (clicking_matrix.at(y_square).at(x_square) == 2)
                            {
                                // Remove flag
                                clicking_matrix.at(y_square).at(x_square) = 0;
                            }
                        }
                    }
                }

                // wait until mouse button is released
                do
                {
                    window.pollEvent(event);
                } while (event.type != sf::Event::MouseButtonReleased);

                // Coordinates of where the mouse was when the button is released, divided by 16 to
                // determine what square is being pressed
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (x_pixel > 239 && x_pixel < 264 && y_pixel > 14 && y_pixel < 39)
                    {
                        still_going = true;
                        reset();
                    }
                    else if (x_pixel > 11 && x_pixel < 492 && y_pixel > 53 && y_pixel < 310)
                    {
                        if (clicking_matrix.at(y_square).at(x_square) == 3)
                        {
                            clicking_matrix.at(y_square).at(x_square) = 1;
                        }
                    }
                }   
            }
        }
        still_going = minesweep();
        window.display();
        won = check_win();
    }
}

int RNG(int max_value)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(0, max_value);
    return distr(gen);
}