#include <vector>
#include "Grid.h"

class Board
{
    int width;
    int height;
    int totalMines;

    std::vector<std::vector<Grid>> grid;

public:
    Board(int w, int h, int mines);
    // 第一个点必须不是雷
    void initializeBoard(int x, int y);
    Grid &getGridCell(int x, int y);
    bool validPosition(int x, int y);
    void printBoard();
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};