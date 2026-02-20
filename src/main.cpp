#include <iostream>
#include <string>
#include <limits>
#include "GameEngine.h"

static void printHelp()
{
    std::cout << "\n操作命令:\n"
              << "  r <x> <y>  -- 揭开格子 (x=列, y=行)\n"
              << "  f <x> <y>  -- 标记/取消标记地雷旗\n"
              << "  a <x> <y>  -- 对已揭开格子展开相邻格 (周围旗数满足时)\n"
              << "  h          -- 显示帮助\n"
              << "  q          -- 退出游戏\n\n";
}

static void chooseDifficulty(int &w, int &h, int &mines)
{
    std::cout << "选择难度:\n"
              << "  1. 初级   (9x9,  10 雷)\n"
              << "  2. 中级   (16x16, 40 雷)\n"
              << "  3. 高级   (30x16, 99 雷)\n"
              << "  4. 自定义\n"
              << "请输入选项 [1-4]: ";

    int choice = 0;
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        w = 9;
        h = 9;
        mines = 10;
        break;
    case 2:
        w = 16;
        h = 16;
        mines = 40;
        break;
    case 3:
        w = 30;
        h = 16;
        mines = 99;
        break;
    default:
        std::cout << "宽度: ";
        std::cin >> w;
        std::cout << "高度: ";
        std::cin >> h;
        std::cout << "地雷数: ";
        std::cin >> mines;
        break;
    }
}

int main()
{
    std::cout << "========== 扫雷游戏 ==========\n";

    GameEngine engine;
    bool running = true;

    while (running)
    {
        int w = 9, h = 9, mines = 10;
        chooseDifficulty(w, h, mines);
        engine.startNewGame(w, h, mines);

        std::cout << "\n游戏开始！输入 h 查看帮助。\n";
        engine.printBoard();

        bool inGame = true;
        while (inGame)
        {
            std::cout << "\n请输入命令: ";
            std::string cmd;
            if (!(std::cin >> cmd))
                break;

            if (cmd == "q" || cmd == "Q")
            {
                running = false;
                inGame = false;
                break;
            }
            else if (cmd == "h" || cmd == "H")
            {
                printHelp();
                continue;
            }
            else if (cmd == "r" || cmd == "f" || cmd == "a")
            {
                int x, y;
                if (!(std::cin >> x >> y))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "输入格式错误，请重试。\n";
                    continue;
                }

                Board *board = engine.getBoard();
                if (!board->validPosition(x, y))
                {
                    std::cout << "坐标超出范围 (x: 0-" << board->getWidth() - 1
                              << ", y: 0-" << board->getHeight() - 1 << ")，请重试。\n";
                    continue;
                }

                if (cmd == "r")
                {
                    Grid &cell = board->getGridCell(x, y);
                    if (cell.isRevealed)
                    {
                        std::cout << "该格子已揭开。\n";
                        continue;
                    }
                    if (cell.isFlagged)
                    {
                        std::cout << "该格子已插旗，请先取消标记。\n";
                        continue;
                    }
                    engine.revealCell(x, y);
                }
                else if (cmd == "f")
                {
                    Grid &cell = board->getGridCell(x, y);
                    if (cell.isRevealed)
                    {
                        std::cout << "该格子已揭开，无法插旗。\n";
                        continue;
                    }
                    engine.flagCell(x, y);
                }
                else // "a"
                {
                    Grid &cell = board->getGridCell(x, y);
                    if (!cell.isRevealed)
                    {
                        std::cout << "该格子尚未揭开，无法展开相邻格。\n";
                        continue;
                    }
                    engine.revealAdjacent(x, y);
                }

                engine.printBoard();

                if (engine.isGameOver())
                {
                    if (engine.isWin())
                    {
                        std::cout << "\n*** 恭喜你，成功扫雷！***\n";
                    }
                    else
                    {
                        std::cout << "\n!!! 踩到地雷，游戏结束 !!!\n";
                        engine.revealAllMines();
                        engine.printBoard();
                    }
                    inGame = false;
                }
            }
            else
            {
                std::cout << "未知命令。输入 h 查看帮助。\n";
            }
        }

        if (running)
        {
            std::cout << "\n是否再来一局？(y/n): ";
            char again;
            std::cin >> again;
            if (again != 'y' && again != 'Y')
                running = false;
        }
    }

    std::cout << "感谢游玩，再见！\n";
    return 0;
}
