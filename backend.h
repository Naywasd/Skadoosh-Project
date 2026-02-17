#ifndef BACKEND_H
#define BACKEND_H

#include <string>

using namespace std;

int toMinutes(int h, int m);
void fillSchedule(int dIdx, string name, int sH, int sM, int eH, int eM);
int getNetFreeMinutes(int dDay, int dHour, int dMinute);
//bjbjh

#endif