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

void MainWindow::on_btnAddTask_clicked()
{
    QString name = ui->inputTaskName->text();
    double hours = ui->spinTaskHours->value();
    int dDay = ui->spinDeadlineDay->value();
    QTime dTime = ui->timeDeadline->time();

    if(name.isEmpty()) {
        QMessageBox::warning(this, "เตือน", "กรุณาใส่ชื่องาน!");
        return;
    }
    Task t;
    t.name = name;
    t.remainingMinutes = (int)(hours * 60);
    t.deadlineDay = dDay;
    t.deadlineHour = dTime.hour();
    t.deadlineMinute = dTime.minute();
    t.stressIndex = 0.0;

    taskList.push_back(t);

    updateDashboard();

    ui->inputTaskName->clear();
    ui->spinTaskHours->setValue(1.0);
}


void MainWindow::on_btnCompleteTask_clicked()
{
    int row = ui->tableToDo->currentRow();
    if(row >= 0 && row < taskList.size()) {
        QString taskName = ui->tableToDo->item(row, 0)->text();
        taskList.erase(taskList.begin() + row);
        updateDashboard();
        QMessageBox::information(this, "สำเร็จ", "เยี่ยมมาก! งาน '" + taskName + "' เสร็จเรียบร้อย");
    } else {
        QMessageBox::warning(this, "เตือน", "กรุณาคลิกเลือกงานในตารางก่อนกดปุ่มนี้");
    }
}

void MainWindow::updateDashboard() {
    for (auto& t : taskList) {
        int free = getNetFreeMinutes(t.deadlineDay, t.deadlineHour, t.deadlineMinute);
        t.stressIndex = (free <= 0) ? 999.0 : (double)t.remainingMinutes / free;
    }
    
    std::sort(taskList.begin(), taskList.end(), [](const Task& a, const Task& b) {
        return a.stressIndex > b.stressIndex;
    });

    refreshScheduleTable();
    refreshToDoTable();

void MainWindow::refreshScheduleTable() {
    for(int h=0; h<24; h++) {
        for(int d=0; d<7; d++) {
            int checkMin = (h * 60) + 30;
            QString status = week[d].timeSlots[checkMin];

            QTableWidgetItem *item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);

            if(status == "Free") {
                item->setText("-");
                item->setBackground(Qt::white);
            } else {
                item->setText(status);
                if(status.contains("นอน") || status.contains("Sleep")) item->setBackground(QColor(200, 200, 200));
                else if(status.contains("เรียน") || status.contains("Study")) item->setBackground(QColor(173, 216, 230));
                else item->setBackground(QColor(255, 228, 196));
            }
            ui->tableSchedule->setItem(h, d, item);
        }
    }
}

void MainWindow::refreshToDoTable() {
    ui->tableToDo->setRowCount(0);

    for(const auto& t : taskList) {
        int row = ui->tableToDo->rowCount();
        ui->tableToDo->insertRow(row);

        double freeHrs = getNetFreeMinutes(t.deadlineDay, t.deadlineHour, t.deadlineMinute) / 60.0;
        double needHrs = t.remainingMinutes / 60.0;

        QString deadlineStr = "D" + QString::number(t.deadlineDay) + " " +
                              QString("%1:%2").arg(t.deadlineHour, 2, 10, QChar('0')).arg(t.deadlineMinute, 2, 10, QChar('0'));

        QString statusStr;
        QColor statusColor;

        if (t.stressIndex > 1.0) { statusStr = "CRITICAL"; statusColor = QColor(255, 100, 100); }
        else if (t.stressIndex > 0.7) { statusStr = "Urgent"; statusColor = QColor(255, 160, 122); }
        else if (t.stressIndex > 0.4) { statusStr = "Warning"; statusColor = QColor(255, 255, 153); }
        else { statusStr = "Chill"; statusColor = QColor(144, 238, 144); } // เขียว

        ui->tableToDo->setItem(row, 0, new QTableWidgetItem(t.name));
        ui->tableToDo->setItem(row, 1, new QTableWidgetItem(deadlineStr));
        ui->tableToDo->setItem(row, 2, new QTableWidgetItem(QString::number(freeHrs, 'f', 1)));
        ui->tableToDo->setItem(row, 3, new QTableWidgetItem(QString::number(needHrs, 'f', 1)));

        QTableWidgetItem *statusItem = new QTableWidgetItem(statusStr);
        statusItem->setBackground(statusColor);
        ui->tableToDo->setItem(row, 4, statusItem);
    }
}
