#ifndef TASKMANAGERLOGIC_H
#define TASKMANAGERLOGIC_H
#include "taskmanagerprocess.h"
#include <QTableWidget>
#include <string>
#include <vector>

//Класс реализует эмуляцию диспетчера задач

//FCFS

/*
1.	FCFS (first come – first served – первым пришёл - первым обслужился ) – прежде
  процессор получает та задача, которая раньше перешла в состояние готовности.
 Данная дисциплина проста в реализации, равноправна по отношению, как к “длинным ”,
 так и к “коротким” процессам, а среднее время пребывания в очереди готовности весьма значительное.
*/

class TaskManagerLogic
{
public:
    TaskManagerLogic() ;

    bool                                    SearchName(QString Name) const; //Искать имя задачи в списке всех задач

    void                                    AddTask(TaskManagerProcess Process);

    void                                    Start(QTableWidget* MainTablePtr); //Запуск

private:
    std::vector<TaskManagerProcess>     Tasks; //Вектор всех задач
    int                                 Tick; //Текущий тик
    TaskManagerProcess*                 CurrentTask; //Текущая задача на исполнении
    std::vector<TaskManagerProcess*>    ReadyTasks; //Готовые задачи
    QTableWidget*                       MainTablePtr; //Указатель на таблицу процессов

    void                                TickTask(); //Метод исполнения текущей задачи


};

#endif // TASKMANAGERLOGIC_H
