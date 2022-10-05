#include "taskmanagerlogic.h"

TaskManagerLogic::TaskManagerLogic() : CurrentTask(nullptr) {}

void TaskManagerLogic::AddTask(TaskManagerProcess Process) { Tasks.push_back(Process); }

//Эта функция нужна, чтобы пользователь не мог добавить процесс с уже имеющимся именем.
bool TaskManagerLogic::SearchName(QString Name) const
{
    if (Tasks.empty()) return false;

    for (auto& it : Tasks)
    {
        if (it.NameGet() == Name) { return true; }
    }
    return false;
}

void TaskManagerLogic::Start(QTableWidget* TablePtr)
{
    MainTablePtr = TablePtr;
    std::reverse(Tasks.begin(), Tasks.end());
    for (Tick = 0; !Tasks.empty(); Tick++)
    {
        MainTablePtr->insertRow(MainTablePtr->rowCount());

        MainTablePtr->setItem(MainTablePtr->rowCount()-1, 0, new QTableWidgetItem(QString::number(Tick)));

        //Поиск готовых процессов

        QString ReadyProcessesString = "";

        ReadyTasks.clear();
        for (auto& it : Tasks)
            if (it.TickStartGet() <= Tick)
                ReadyTasks.push_back(&it);

        std::reverse(ReadyTasks.begin(), ReadyTasks.end());
        //если есть готовые процессы

        if (!ReadyTasks.empty())
        {
            //Найти процесс с максимальным приоритетом и сделать его текущим процессом
            if (CurrentTask == nullptr)
                CurrentTask = ReadyTasks.front();

            for(size_t i = 0; i < ReadyTasks.size(); i++)
                if (ReadyTasks.at(i)->NameGet() == CurrentTask->NameGet())
                    ReadyTasks.erase(ReadyTasks.begin() + i);
        }

        //Показать готовые процессы
        for (auto& it: ReadyTasks)
        {
            ReadyProcessesString.append(it->NameGet());
            ReadyProcessesString.append(",");
        }
        ReadyProcessesString.chop(1);
        MainTablePtr->setItem(MainTablePtr->rowCount()-1, 2, new QTableWidgetItem(ReadyProcessesString));

        TickTask();
    }
}

void TaskManagerLogic::TickTask()
{
    //Выполнять текущую задачу

    if (CurrentTask) //если она есть
    {
        CurrentTask->TickCountDec();
        MainTablePtr->setItem(MainTablePtr->rowCount()-1, 1, new QTableWidgetItem(QString(CurrentTask->NameGet())));
        if (CurrentTask->TickCountGet() == 0)
            for (size_t i = 0; i < Tasks.size(); i++)
                if (Tasks.at(i).NameGet() == CurrentTask->NameGet())
                {
                    CurrentTask = nullptr;
                    Tasks.erase(Tasks.begin() + i);
                    return;
                }
    }
}
