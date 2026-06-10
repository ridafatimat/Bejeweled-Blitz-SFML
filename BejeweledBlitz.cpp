#include <SFML/Graphics.hpp>
#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

const int GRID_SIZE = 8;
const float CELL_SIZE = 80.f;
const int GEM_TYPES = 6;
const int GAME_TIME_SECONDS = 60;

struct MatchResult
{
    bool found = false;
    int removedCount = 0;
};

bool areAdjacent(sf::Vector2i a, sf::Vector2i b)
{
    int dx = std::abs(a.x - b.x);
    int dy = std::abs(a.y - b.y);
    return (dx + dy) == 1;
}

bool insideGrid(int row, int col)
{
    return row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE;
}

int randomGem()
{
    return std::rand() % GEM_TYPES;
}

sf::Color gemColor(int id)
{
    static sf::Color colors[GEM_TYPES] = {
        sf::Color(220, 40, 60),     // red
        sf::Color(45, 140, 255),    // blue
        sf::Color(70, 200, 90),     // green
        sf::Color(250, 210, 60),    // yellow
        sf::Color(170, 80, 220),    // purple
        sf::Color(255, 135, 35)     // orange
    };

    return colors[id % GEM_TYPES];
}

void drawGem(sf::RenderWindow& window, int id, int row, int col)
{
    float x = col * CELL_SIZE;
    float y = row * CELL_SIZE;
    float padding = 10.f;

    sf::Color color = gemColor(id);

    if (id == 0)
    {
        // Circle gem
        sf::CircleShape shape((CELL_SIZE - padding * 2) / 2);
        shape.setFillColor(color);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(2.f);
        shape.setPosition(x + padding, y + padding);
        window.draw(shape);
    }
    else if (id == 1)
    {
        // Diamond gem
        sf::ConvexShape shape(4);
        shape.setPoint(0, sf::Vector2f(x + CELL_SIZE / 2, y + padding));
        shape.setPoint(1, sf::Vector2f(x + CELL_SIZE - padding, y + CELL_SIZE / 2));
        shape.setPoint(2, sf::Vector2f(x + CELL_SIZE / 2, y + CELL_SIZE - padding));
        shape.setPoint(3, sf::Vector2f(x + padding, y + CELL_SIZE / 2));
        shape.setFillColor(color);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(2.f);
        window.draw(shape);
    }
    else if (id == 2)
    {
        // Square gem
        sf::RectangleShape shape(sf::Vector2f(CELL_SIZE - padding * 2, CELL_SIZE - padding * 2));
        shape.setFillColor(color);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(2.f);
        shape.setPosition(x + padding, y + padding);
        window.draw(shape);
    }
    else if (id == 3)
    {
        // Triangle gem
        sf::CircleShape shape((CELL_SIZE - padding * 2) / 2, 3);
        shape.setFillColor(color);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(2.f);
        shape.setPosition(x + padding, y + padding + 5);
        window.draw(shape);
    }
    else if (id == 4)
    {
        // Hexagon gem
        sf::CircleShape shape((CELL_SIZE - padding * 2) / 2, 6);
        shape.setFillColor(color);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(2.f);
        shape.setPosition(x + padding, y + padding);
        window.draw(shape);
    }
    else
    {
        // Star-like gem
        sf::ConvexShape shape(10);
        float cx = x + CELL_SIZE / 2;
        float cy = y + CELL_SIZE / 2;
        float outer = 32.f;
        float inner = 15.f;

        for (int i = 0; i < 10; i++)
        {
            float angle = -90.f + i * 36.f;
            float radius = (i % 2 == 0) ? outer : inner;
            float rad = angle * 3.14159265f / 180.f;
            shape.setPoint(i, sf::Vector2f(cx + std::cos(rad) * radius, cy + std::sin(rad) * radius));
        }

        shape.setFillColor(color);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(2.f);
        window.draw(shape);
    }
}

MatchResult markMatches(int board[GRID_SIZE][GRID_SIZE], bool marked[GRID_SIZE][GRID_SIZE])
{
    MatchResult result;

    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            marked[row][col] = false;
        }
    }

    // Horizontal matches
    for (int row = 0; row < GRID_SIZE; row++)
    {
        int col = 0;

        while (col < GRID_SIZE)
        {
            int start = col;
            int gem = board[row][col];

            while (col < GRID_SIZE && board[row][col] == gem)
            {
                col++;
            }

            int length = col - start;

            if (gem != -1 && length >= 3)
            {
                result.found = true;
                for (int c = start; c < col; c++)
                {
                    if (!marked[row][c])
                    {
                        result.removedCount++;
                    }
                    marked[row][c] = true;
                }
            }
        }
    }

    // Vertical matches
    for (int col = 0; col < GRID_SIZE; col++)
    {
        int row = 0;

        while (row < GRID_SIZE)
        {
            int start = row;
            int gem = board[row][col];

            while (row < GRID_SIZE && board[row][col] == gem)
            {
                row++;
            }

            int length = row - start;

            if (gem != -1 && length >= 3)
            {
                result.found = true;
                for (int r = start; r < row; r++)
                {
                    if (!marked[r][col])
                    {
                        result.removedCount++;
                    }
                    marked[r][col] = true;
                }
            }
        }
    }

    return result;
}

void removeMarkedGems(int board[GRID_SIZE][GRID_SIZE], bool marked[GRID_SIZE][GRID_SIZE])
{
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            if (marked[row][col])
            {
                board[row][col] = -1;
            }
        }
    }
}

void collapseBoard(int board[GRID_SIZE][GRID_SIZE])
{
    for (int col = 0; col < GRID_SIZE; col++)
    {
        int writeRow = GRID_SIZE - 1;

        for (int row = GRID_SIZE - 1; row >= 0; row--)
        {
            if (board[row][col] != -1)
            {
                board[writeRow][col] = board[row][col];

                if (writeRow != row)
                {
                    board[row][col] = -1;
                }

                writeRow--;
            }
        }

        while (writeRow >= 0)
        {
            board[writeRow][col] = randomGem();
            writeRow--;
        }
    }
}

bool hasAnyMatch(int board[GRID_SIZE][GRID_SIZE])
{
    bool marked[GRID_SIZE][GRID_SIZE];
    MatchResult result = markMatches(board, marked);
    return result.found;
}

void clearAllMatches(int board[GRID_SIZE][GRID_SIZE], int& score)
{
    bool keepChecking = true;

    while (keepChecking)
    {
        bool marked[GRID_SIZE][GRID_SIZE];
        MatchResult result = markMatches(board, marked);

        if (!result.found)
        {
            keepChecking = false;
        }
        else
        {
            score += result.removedCount * 10;
            removeMarkedGems(board, marked);
            collapseBoard(board);
        }
    }
}

void initializeBoard(int board[GRID_SIZE][GRID_SIZE])
{
    do
    {
        for (int row = 0; row < GRID_SIZE; row++)
        {
            for (int col = 0; col < GRID_SIZE; col++)
            {
                board[row][col] = randomGem();
            }
        }
    }
    while (hasAnyMatch(board));
}

void swapCells(int board[GRID_SIZE][GRID_SIZE], sf::Vector2i a, sf::Vector2i b)
{
    std::swap(board[a.y][a.x], board[b.y][b.x]);
}

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(
        static_cast<unsigned int>(GRID_SIZE * CELL_SIZE),
        static_cast<unsigned int>(GRID_SIZE * CELL_SIZE)),
        "Bejeweled Blitz - Score: 0 | Time: 60");

    window.setFramerateLimit(60);

    int board[GRID_SIZE][GRID_SIZE];
    initializeBoard(board);

    int score = 0;
    sf::Clock gameClock;

    sf::Vector2i selectedCell(-1, -1);
    sf::Vector2i cursorCell(0, 0);

    while (window.isOpen())
    {
        int timeLeft = GAME_TIME_SECONDS - static_cast<int>(gameClock.getElapsedTime().asSeconds());

        if (timeLeft < 0)
        {
            timeLeft = 0;
        }

        window.setTitle("Bejeweled Blitz - Score: " + std::to_string(score) +
                        " | Time: " + std::to_string(timeLeft));

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (timeLeft == 0)
            {
                continue;
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                int col = event.mouseButton.x / static_cast<int>(CELL_SIZE);
                int row = event.mouseButton.y / static_cast<int>(CELL_SIZE);

                if (insideGrid(row, col))
                {
                    sf::Vector2i clickedCell(col, row);

                    if (selectedCell.x == -1)
                    {
                        selectedCell = clickedCell;
                    }
                    else
                    {
                        if (areAdjacent(selectedCell, clickedCell))
                        {
                            swapCells(board, selectedCell, clickedCell);

                            if (hasAnyMatch(board))
                            {
                                clearAllMatches(board, score);
                            }
                            else
                            {
                                swapCells(board, selectedCell, clickedCell);
                            }
                        }

                        selectedCell = sf::Vector2i(-1, -1);
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up && cursorCell.y > 0)
                {
                    cursorCell.y--;
                }
                else if (event.key.code == sf::Keyboard::Down && cursorCell.y < GRID_SIZE - 1)
                {
                    cursorCell.y++;
                }
                else if (event.key.code == sf::Keyboard::Left && cursorCell.x > 0)
                {
                    cursorCell.x--;
                }
                else if (event.key.code == sf::Keyboard::Right && cursorCell.x < GRID_SIZE - 1)
                {
                    cursorCell.x++;
                }
                else if (event.key.code == sf::Keyboard::Enter ||
                         event.key.code == sf::Keyboard::Return)
                {
                    if (selectedCell.x == -1)
                    {
                        selectedCell = cursorCell;
                    }
                    else
                    {
                        if (areAdjacent(selectedCell, cursorCell))
                        {
                            swapCells(board, selectedCell, cursorCell);

                            if (hasAnyMatch(board))
                            {
                                clearAllMatches(board, score);
                            }
                            else
                            {
                                swapCells(board, selectedCell, cursorCell);
                            }
                        }

                        selectedCell = sf::Vector2i(-1, -1);
                    }
                }
            }
        }

        window.clear(sf::Color(22, 22, 30));

        // Draw board cells and gems
        for (int row = 0; row < GRID_SIZE; row++)
        {
            for (int col = 0; col < GRID_SIZE; col++)
            {
                sf::RectangleShape cellBackground(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
                cellBackground.setPosition(col * CELL_SIZE + 1, row * CELL_SIZE + 1);
                cellBackground.setFillColor(sf::Color(35, 35, 48));
                cellBackground.setOutlineColor(sf::Color(70, 70, 90));
                cellBackground.setOutlineThickness(1.f);
                window.draw(cellBackground);

                drawGem(window, board[row][col], row, col);
            }
        }

        // Draw keyboard cursor
        sf::RectangleShape cursorHighlight(sf::Vector2f(CELL_SIZE - 4, CELL_SIZE - 4));
        cursorHighlight.setPosition(cursorCell.x * CELL_SIZE + 2, cursorCell.y * CELL_SIZE + 2);
        cursorHighlight.setFillColor(sf::Color::Transparent);
        cursorHighlight.setOutlineColor(sf::Color::Cyan);
        cursorHighlight.setOutlineThickness(3.f);
        window.draw(cursorHighlight);

        // Draw selected cell
        if (selectedCell.x != -1)
        {
            sf::RectangleShape selectedHighlight(sf::Vector2f(CELL_SIZE - 8, CELL_SIZE - 8));
            selectedHighlight.setPosition(selectedCell.x * CELL_SIZE + 4, selectedCell.y * CELL_SIZE + 4);
            selectedHighlight.setFillColor(sf::Color::Transparent);
            selectedHighlight.setOutlineColor(sf::Color::White);
            selectedHighlight.setOutlineThickness(4.f);
            window.draw(selectedHighlight);
        }

        // Game over overlay
        if (timeLeft == 0)
        {
            sf::RectangleShape overlay(sf::Vector2f(GRID_SIZE * CELL_SIZE, GRID_SIZE * CELL_SIZE));
            overlay.setFillColor(sf::Color(0, 0, 0, 150));
            window.draw(overlay);
            window.setTitle("Bejeweled Blitz - GAME OVER | Final Score: " + std::to_string(score));
        }

        window.display();
    }

    return 0;
}
