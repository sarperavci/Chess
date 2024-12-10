//#include "Game.h"
// Terminal-based chess game
//int main()
//{
//    // Create a new game board
//    Game *game = new Game();
//    game->start_game();
//    return 0;
//}

// GUI-based chess game
#include "MainWindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}