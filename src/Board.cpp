#include <algorithm>
#include <vector>
#include <numeric>
#include <iostream>
#include <random>
#include <Board.h>

Board::Board(int w, int h, int mines)
    : width(w), height(h), totalMines(mines), grid(h, std::vector<Grid>(w))
{
}

void Board::initializeBoard(int x, int y)
{
    std::vector<int> pos_int(width * height);
    std::iota(pos_int.begin(), pos_int.end(), 0);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pos_int.begin(), pos_int.end(), g);
    int sum = this->totalMines;

    for (int i = 0; i < sum; ++i)
    {
        int p = pos_int[i];
        int cur_x = p % width;
        int cur_y = p / width;

        if (cur_x == x && cur_y == y)
        {
            ++sum;
            continue;
        }
        grid[cur_y][cur_x].isMined = true;
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (grid[i][j].isMined)
                continue;

            int mineCount = 0;
            for (int dx = -1; dx <= 1; ++dx)
            {
                for (int dy = -1; dy <= 1; ++dy)
                {
                    int nx = j + dx;
                    int ny = i + dy;
                    if (validPosition(nx, ny) && grid[ny][nx].isMined)
                    {
                        ++mineCount;
                    }
                }
            }
            grid[i][j].adjacentMines = mineCount;
        }
    }
}

Grid &Board::getGridCell(int x, int y)
{
    // Fix: Access grid as grid[row][col] -> grid[y][x]
    return grid[y][x];
}

bool Board::validPosition(int x, int y)
{
    return x >= 0 && x < width && y >= 0 && y < height;
}

void Board::printBoard()
{
    std::cout << "  ";
    for (int i = 0; i < width; ++i)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < height; ++i)
    {
        std::cout << i << " ";
        for (int j = 0; j < width; ++j)
        {
            if (grid[i][j].isRevealed)
            {
                if (grid[i][j].isMined)
                {
                    std::cout << "* ";
                }
                else
                {
                    std::cout << grid[i][j].adjacentMines << " ";
                }
            }
            else if (grid[i][j].isFlagged)
            {
                std::cout << "F ";
            }
            else
            {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}
