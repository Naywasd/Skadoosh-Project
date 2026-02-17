#include "Data.h"

Day::Day() {
    for(int i=0; i<1440; i++) timeSlots[i] = "Free";
}

vector<Day> week(7);
vector<Task> taskList;
int currentDay = 1;
int currentHour = 0;
int currentMinute = 0;