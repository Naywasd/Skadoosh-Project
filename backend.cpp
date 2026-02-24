
#include "Backend.h"
#include "data.h" // รอไอ่นายเขียน

int toMinutes(int h, int m) { // แปลงชมเด้อ
    return (h * 60) + m;
}


// คิดตรรกะ
void fillSchedule(int dIdx, string name, int sH, int sM, int eH, int eM) {
    int start = toMinutes(sH, sM); // เริ่มรูที่น
    int end = toMinutes(eH, eM);  // จบรูทีนนนน
   
if (end < start) { 
        for(int m = start; m < 1440; m++)   week[dIdx].timeSlots[m] = name;   
        for(int m = 0; m <= end; m++)   week[dIdx].timeSlots[m] = name;
        } else {
        for(int m = start; m <= end; m++) week[dIdx].timeSlots[m] = name;
           }
     }




int getNetFreeMinutes  (int dDay, int dHour, int dMinute) {  // นับเวลาว่างที่มีก่อนเอาไปคิดต่อ
        int freeCount = 0;
        int startMinToday = toMinutes(currentHour, currentMinute);
        int targetEndMin = toMinutes(dHour, dMinute);

    for (int d = currentDay - 1; d < dDay; d++) {
            int mStart = (d == currentDay - 1) ? startMinToday : 0;
            int mEnd = (d == dDay - 1) ? targetEndMin : 1439;

        for (int m = mStart; m <= mEnd; m++) {
            if (m >= 0 && m < 1440 && week[d].timeSlots[m] == "Free") {
                freeCount++;
            }
        }
    }
    return freeCount;
}
  

