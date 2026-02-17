#include "UI.h"
#include "data.h"
#include "Algorithm.h" // รอไฟล์algorithm

void printScheduleTable() {
    cout << "\n--- ตารางเวลาภาพรวม (Overview) ---\n";
    cout << "Time  | D1   | D2   | D3   | D4   | D5   | D6   | D7   |\n";
    cout << "----------------------------------------------------------\n";
    for (int h = 0; h < 24; h++) {
        printf("%02d:00 | ", h); // ใช้printfเพื่อง่ายต่อการเขียน
        for (int d = 0; d < 7; d++) {
            string display = "-";
            for(int m = h*60; m < (h+1)*60; m++) {
                if(week[d].timeSlots[m] != "Free") {
                    display = week[d].timeSlots[m].substr(0, 4);
                    break;
                }
            }
            cout << left << setw(5) << display << "| ";
        }
        cout << endl;
    }
}

void displayToDoList() {
    processTaskPriority(); //อัปเดตข้อมูลจากในalgorithm

}