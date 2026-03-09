#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Task {
    QString name;
    int remainingMinutes;
    int deadlineDay;
    int deadlineHour;
    int deadlineMinute;
    double stressIndex;
};

struct Day {
    QString timeSlots[1440];
    Day() {
        for(int i=0; i<1440; i++) timeSlots[i] = "Free";
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnUpdateTime_clicked();
    void on_btnAddRoutine_clicked();
    void on_btnAddTask_clicked();
    void on_btnCompleteTask_clicked();
    void on_btnClearRoutine_clicked();

private:
    Ui::MainWindow *ui;

    std::vector<Day> week;
    std::vector<Task> taskList;

    int curDay = 1;
    int curHour = 0;
    int curMin = 0;

    int toMinutes(int h, int m);
    int getNetFreeMinutes(int dDay, int dHour, int dMinute);
    void updateDashboard();
    void refreshScheduleTable();
    void refreshToDoTable();
};

#endif // MAINWINDOW_H
