#ifndef TASKMANAGERPROCESS_H
#define TASKMANAGERPROCESS_H
#include <QString>

//класс реализует отдельно взятую задачу

class TaskManagerProcess
{
public:
    TaskManagerProcess(QString const UserProcessName,
                       int     const UserProcessTickCount,
                       int     const UserProcessTickStart);

//Getters

    int     const & TickCountGet()     const;
    int     const & TickStartGet()     const;
    QString const & NameGet()          const;

//Setters

    void    TickCountDec(); //Декремент тактов выполнения (прогресс выполнения)

private:
    QString      Name;      //Имя задачи
    int          TickCount; //Количество тактов на исполнение
    int          TickStart; //Такт готовности
};

#endif // TASKMANAGERPROCESS_H
