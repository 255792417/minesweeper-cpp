struct Grid
{
    bool isMined;
    bool isRevealed;
    bool isFlagged;
    int adjacentMines;

    Grid();
    void reveal();
    void flag();
};