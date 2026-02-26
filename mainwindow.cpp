#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <algorithm>
#include <QTableWidgetItem>
#include <QCheckBox>

int MainWindow::toMinutes(int h, int m) {
    return (h * 60) + m;
}

int MainWindow::getNetFreeMinutes(int dDay, int dHour, int dMinute) {
    int freeCount = 0;
    int startMinToday = toMinutes(curHour, curMin);
    int targetEndMin = toMinutes(dHour, dMinute);

    for (int d = curDay - 1; d < dDay && d < 7; d++) {
        int mStart = (d == curDay - 1) ? startMinToday : 0;
        int mEnd = (d == dDay - 1) ? targetEndMin : 1439;

        for (int m = mStart; m <= mEnd; m++) {
            if (week[d].timeSlots[m] == "Free") {
                freeCount++;
            }
        }
    }
    return freeCount;
}


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

void MainWindow::on_btnUpdateTime_clicked()
{
    curDay = ui->spinCurDay->value();
    QTime t = ui->timeCur->time();
    curHour = t.hour();
    curMin = t.minute();

    updateDashboard();
    QMessageBox::information(this, "อัปเดต", "อัปเดตเวลาและคำนวณสถานะงานใหม่เรียบร้อย!");
}

void MainWindow::on_btnAddRoutine_clicked()
{
    QString name = ui->inputRoutineName->text();
    QTime tStart = ui->timeStart->time();
    QTime tEnd = ui->timeEnd->time();

    if(name.isEmpty()) return;

    int startM = toMinutes(tStart.hour(), tStart.minute());
    int endM = toMinutes(tEnd.hour(), tEnd.minute());

    QCheckBox* days[] = {ui->cbMon, ui->cbTue, ui->cbWed, ui->cbThu, ui->cbFri, ui->cbSat, ui->cbSun};

    for(int i=0; i<7; i++) {
        if(days[i]->isChecked()) {
            if(endM > startM) {
                for(int m = startM; m < endM; m++) week[i].timeSlots[m] = name;
            } else {
                for(int m = startM; m < 1440; m++) week[i].timeSlots[m] = name;
                for(int m = 0; m < endM; m++) week[i].timeSlots[m] = name;
            }
        }
    }
    
    updateDashboard();
    ui->inputRoutineName->clear();
    for(int i=0; i<7; i++) days[i]->setChecked(false);
}
