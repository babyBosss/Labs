#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication TaskManagerApp(argc, argv);
    TaskManagerLogic TaskManager;

    MainWindow MainWindowObject(NULL, &TaskManager);
    MainWindowObject.show();


    return TaskManagerApp.exec();
}
