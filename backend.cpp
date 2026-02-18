#include "Backend.h"
#include "Data.h" // รอไอ่นายเขียน

int toMinutes(int h, int m) {  // แปลงชมเป็นนาที
    return (h * 60) + m;
}


// คิดตรรกะ
void fillSchedule(int dIdx, string name, int sH, int sM, int eH, int eM) {
    int start = toMinutes(sH, sM); // เวลาที่เรื่มทำรูทีน
    int end = toMinutes(eH, eM); // เวลาจบรูทีน

    if (end < start) { 
        for(int m = start; m < 1440; m++) week[dIdx].timeSlots[m] = name;
        for(int m = 0; m <= end; m++) week[dIdx].timeSlots[m] = name;
    } else {
        for(int m = start; m <= end; m++) week[dIdx].timeSlots[m] = name;
    }
}
   







