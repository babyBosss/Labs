#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "taskmanagerlogic.h"

//Класс реализует главное окно интерфейса

/*
Главное окно является единственным окном GUI, и в нем реализованы 2 таблицы - таблица процессов,
которые добавляет пользователь, а также таблица состояния диспетчера задач, включающая в себя
имя процесса, текущий процесс на исполнении и очередь готовых задач.
Есть поля для ввода параметров процесса и кнопка добавления процесса.
*/


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,
               TaskManagerLogic *TaskManager = nullptr);
    ~MainWindow();

private slots:
    int  on_UserAddProcess_clicked(); //Добавить процесс

    void on_pushButton_clicked(); //Запустить диспетчер

private:
    Ui::MainWindow*   ui;
    TaskManagerLogic* TaskManagerPtr;
};
#endif // MAINWINDOW_H
