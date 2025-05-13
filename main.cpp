#include <QApplication>
#include "mainwindow.h"
#include "startmenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建开始菜单
    StartMenu startMenu;
    startMenu.show();

    // 创建主窗口但不立即显示
    MainWindow mainWindow;
    //mainWindow.setFixedSize(900, 600);
    //mainWindow.hide();

    // 连接开始菜单的信号到主窗口
    QObject::connect(&startMenu, &StartMenu::startGame, &mainWindow, [&mainWindow]() {
        // 创建主窗口但不立即显示
        //MainWindow mainWindow;
        mainWindow.setFixedSize(900, 600);
        //mainWindow.hide();

        mainWindow.show();
    });

    return a.exec();
}
