#include <GameEngine.h>
#include <algorithm>

GameEngine::GameEngine()
    : gameBoard(nullptr)
{
}

GameEngine::~GameEngine()
{
    if (gameBoard)
        delete gameBoard;
}

void GameEngine::startNewGame(int width, int height, int totalMines)
{
    if (width <= 0)
        width = 9;
    if (height <= 0)
        height = 9;
    if (totalMines <= 0)
        totalMines = 10;
    if (totalMines >= width * height)
        totalMines = width * height - 1;

    if (gameBoard != nullptr)
    {
        delete gameBoard;
    }
    gameBoard = new Board(width, height, totalMines);
    isFirstMove = true;
    gameOver = false;
    win = false;
}

void GameEngine::revealCell(int x, int y)
{
    if (gameOver)
        return;

    if (isFirstMove)
    {
        gameBoard->initializeBoard(x, y);
        isFirstMove = false;
    }

    Grid &cell = gameBoard->getGridCell(x, y);
    cell.reveal();
    if (cell.adjacentMines == 0 && !cell.isMined)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                int nx = x + dx;
                int ny = y + dy;
                if (gameBoard->validPosition(nx, ny))
                {
                    floodFill(nx, ny);
                }
            }
        }
    }

    if (cell.isMined)
    {
        gameOver = true;
        win = false;
    }
    else if (checkWinCondition())
    {
        gameOver = true;
        win = true;
    }
}

void GameEngine::flagCell(int x, int y)
{
    if (gameOver)
        return;

    Grid &cell = gameBoard->getGridCell(x, y);
    cell.flag();
}

void GameEngine::revealAdjacent(int x, int y)
{
    if (gameOver)
        return;

    Grid &cell = gameBoard->getGridCell(x, y);
    if (!cell.isRevealed)
        return;

    int flaggedCount = 0;
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            if (dx == 0 && dy == 0)
                continue;
            int nx = x + dx;
            int ny = y + dy;
            if (gameBoard->validPosition(nx, ny) && gameBoard->getGridCell(nx, ny).isFlagged)
            {
                flaggedCount++;
            }
        }
    }

    if (flaggedCount == cell.adjacentMines)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                    continue;
                int nx = x + dx;
                int ny = y + dy;
                if (gameBoard->validPosition(nx, ny))
                {
                    Grid &neighbor = gameBoard->getGridCell(nx, ny);
                    if (!neighbor.isFlagged && !neighbor.isRevealed)
                    {
                        revealCell(nx, ny);
                    }
                }
            }
        }
    }
}

void GameEngine::printBoard() const
{
    gameBoard->printBoard();
}

void GameEngine::floodFill(int x, int y)
{
    Grid &cell = gameBoard->getGridCell(x, y);
    if (cell.isRevealed || cell.isMined)
        return;
    cell.reveal();
    if (cell.adjacentMines > 0)
        return;
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            int nx = x + dx;
            int ny = y + dy;
            if (gameBoard->validPosition(nx, ny))
            {
                floodFill(nx, ny);
            }
        }
    }
}

bool GameEngine::checkWinCondition()
{
    for (int i = 0; i < gameBoard->getHeight(); ++i)
    {
        for (int j = 0; j < gameBoard->getWidth(); ++j)
        {
            Grid &cell = gameBoard->getGridCell(j, i);
            if (!cell.isMined && !cell.isRevealed)
            {
                return false;
            }
        }
    }
    return true;
}

void GameEngine::revealAllMines()
{
    for (int i = 0; i < gameBoard->getHeight(); ++i)
    {
        for (int j = 0; j < gameBoard->getWidth(); ++j)
        {
            Grid &cell = gameBoard->getGridCell(j, i);
            if (cell.isMined && !cell.isFlagged)
            {
                cell.reveal();
            }
            else if (!cell.isMined && cell.isFlagged)
            {
                cell.reveal();
            }
        }
    }
}