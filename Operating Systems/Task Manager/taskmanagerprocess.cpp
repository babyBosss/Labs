#include "taskmanagerprocess.h"

TaskManagerProcess::TaskManagerProcess(QString const UserProcessName,
                                       int     const UserProcessTickCount,
                                       int     const UserProcessTickStart)
                                       :
                                       Name          (UserProcessName),
                                       TickCount     (UserProcessTickCount),
                                       TickStart     (UserProcessTickStart)
                                       {}

//Getters

int     const & TaskManagerProcess::TickCountGet()     const { return TickCount; }

int     const & TaskManagerProcess::TickStartGet()     const { return TickStart; }

QString const & TaskManagerProcess::NameGet()          const { return Name; }

////////////////////////SETTERS///////////////////////////////

void TaskManagerProcess::TickCountDec() { TickCount--; }
