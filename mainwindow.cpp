#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <algorithm>
#include <QTableWidgetItem>
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    week.resize(7);

    ui->tableSchedule->setRowCount(24);
    ui->tableSchedule->setColumnCount(7);
    QStringList headers;
    headers << "จันทร์" << "อังคาร" << "พุธ" << "พฤหัส" << "ศุกร์" << "เสาร์" << "อาทิตย์";
    ui->tableSchedule->setHorizontalHeaderLabels(headers);
    for(int i=0; i<24; i++) {
        QString timeLabel = QString("%1:00").arg(i, 2, 10, QChar('0'));
        ui->tableSchedule->setVerticalHeaderItem(i, new QTableWidgetItem(timeLabel));
    }

    ui->tableToDo->setColumnCount(5);
    QStringList todoHeaders;
    todoHeaders << "ชื่องาน" << "Deadline" << "เวลาว่างเหลือ (ชม.)" << "เวลาต้องใช้ (ชม.)" << "สถานะ";
    ui->tableToDo->setHorizontalHeaderLabels(todoHeaders);
    ui->tableToDo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->spinCurDay->setValue(1);
    ui->timeCur->setTime(QTime(8, 0));
}

MainWindow::~MainWindow()
{
    delete ui;
}
