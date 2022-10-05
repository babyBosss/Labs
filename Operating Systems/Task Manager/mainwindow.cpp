#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget*          parent,
                       TaskManagerLogic* TaskManager)
                       :
                       QMainWindow(parent),
                       ui(new Ui::MainWindow),
                       TaskManagerPtr(TaskManager)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnWidth(0, 85);
    ui->tableWidget->setColumnWidth(1, 85);
    ui->tableWidget->setColumnWidth(2, 85);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Номер такта" << "Исполнение" << "Готовность");

    ui->UserProcessTable->setColumnCount(3);
    ui->UserProcessTable->setRowCount(0);
    ui->UserProcessTable->setColumnWidth(0, 64);
    ui->UserProcessTable->setColumnWidth(1, 64);
    ui->UserProcessTable->setColumnWidth(2, 256);
    ui->UserProcessTable->setHorizontalHeaderLabels(QStringList() << "Имя" << "Старт" << "Тактов на обслуживание");
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::on_UserAddProcess_clicked()
{

    QString const ProcessName         = ui->UserProcessName     ->text();
    int     const ProcessTickCount    = ui->UserProcessTickCount->value();
    int     const ProcessTickStart    = ui->UserProcessTickStart->value();

    //Проверки на валидность ввода

    if (TaskManagerPtr->SearchName(ProcessName)) {
        QMessageBox ErrorTickStartBox;
        ErrorTickStartBox.setText("Process name is already taken");
        ErrorTickStartBox.exec();
        return 1;
    }

    if (ProcessTickCount <= 0) {
        QMessageBox ErrorTickCountBox;
        ErrorTickCountBox.setText("Process should have at least 1 tick");
        ErrorTickCountBox.exec();
        return 1;
    }

    TaskManagerPtr->AddTask(TaskManagerProcess(ProcessName, ProcessTickCount, ProcessTickStart));

    ui->UserProcessTable->insertRow(ui->UserProcessTable->rowCount());


    ui->UserProcessTable->setItem(ui->UserProcessTable->rowCount()-1, 0, new QTableWidgetItem(ProcessName));
    ui->UserProcessTable->setItem(ui->UserProcessTable->rowCount()-1, 1, new QTableWidgetItem(QString::number(ProcessTickStart)));
    ui->UserProcessTable->setItem(ui->UserProcessTable->rowCount()-1, 2, new QTableWidgetItem(QString::number(ProcessTickCount)));

    return 0;
}

void MainWindow::on_pushButton_clicked()
{
    QTableWidget* MainTablePtr = ui->tableWidget;
    TaskManagerPtr->Start(MainTablePtr);
}
