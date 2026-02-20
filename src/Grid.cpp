#include "Grid.h"

Grid::Grid()
    : isMined(false), isRevealed(false), isFlagged(false), adjacentMines(0)
{
}

void Grid::reveal()
{
    isRevealed = true;
}

void Grid::flag()
{
    isFlagged = !isFlagged;
}