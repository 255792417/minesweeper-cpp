#include "Board.h"

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();
    void startNewGame(int width, int height, int totalMines);
    void revealCell(int x, int y);
    void revealAdjacent(int x, int y);
    void flagCell(int x, int y);
    void printBoard() const;
    void revealAllMines();

    bool isGameOver() const { return gameOver; }
    bool isWin() const { return win; }

    Board *getBoard() const { return gameBoard; }

private:
    Board *gameBoard;
    bool gameOver;
    bool win;
    bool isFirstMove;
    void floodFill(int x, int y);
    bool checkWinCondition();
};