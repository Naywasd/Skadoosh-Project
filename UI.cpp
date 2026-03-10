#include "UI.h"
#include "data.h"
#include "Algorithm.h" 
#include "backend.h" 

/**
 * แสดงตารางเวลาภาพรวมรายสัปดาห์ (Weekly Schedule Overview)
 * แสดงกิจกรรมที่ถูกจองไว้ในแต่ละช่วงเวลา 1 ชั่วโมง ของทั้ง 7 วัน
 */
void printScheduleTable() {
    cout << "\n--- ตารางเวลาภาพรวม (Overview) ---\n";
    cout << "Time  | D1   | D2   | D3   | D4   | D5   | D6   | D7   |\n";
    cout << "----------------------------------------------------------\n";

    for (int h = 0; h < 24; h++) {
        // จัดรูปแบบการแสดงผลเวลาเป็น HH:00
        printf("%02d:00 | ", h); 

        for (int d = 0; d < 7; d++) {
            string display = "-";
            
            // ตรวจสอบข้อมูลในช่วง 60 นาทีของชั่วโมงนั้นๆ
            for(int m = h*60; m < (h+1)*60; m++) {
                if(week[d].timeSlots[m] != "Free") {
                    // ดึงชื่อกิจกรรมมาแสดงผลเพียง 4 ตัวอักษรแรกเพื่อรักษาขนาดตาราง
                    display = week[d].timeSlots[m].substr(0, 4);
                    break;
                }
            }
            cout << left << setw(5) << display << "| ";
        }
        cout << endl;
    }
}


//แสดงรายการงานที่ต้องทำ (To-Do List) พร้อมการวิเคราะห์ระดับความสำคัญ
//เรียงลำดับงานตามความเร่งด่วน (Stress Index) และสถานะของงาน

void displayToDoList() {
    
    processTaskPriority(); //อัปเดตค่าความสำคัญจาก algor

    cout << "\n" << string(85, '=') << endl;
    // แสดงสถานะวันและเวลาปัจจุบันของระบบ
    cout << "  NOW: Day " << currentDay << " | Time " << setfill('0') << setw(2) << currentHour << ":" << setw(2) << currentMinute << setfill(' ') << endl;
    cout << string(85, '=') << endl;

    cout << "ชื่องาน          Deadline      เวลาว่างที่เหลือ     เวลาที่ต้องใช้      สถานะ" << endl;
    cout << string(85, '-') << endl;

    for (const auto& t : taskList) {
        // ดึงค่าเวลาว่างที่มีอยู่ก่อนถึง Deadline (หน่วย: ชั่วโมง)
        double freeTime = getNetFreeMinutes(t.deadlineDay, t.deadlineHour, t.deadlineMinute) / 60.0;
        // เวลาที่คาดการณ์ว่าต้องใช้ในการทำงาน (หน่วย: ชั่วโมง)
        double needTime = t.remainingMinutes / 60.0;
        
        // ประเมินระดับความเร่งด่วน (Priority Level) จากค่า Stress Index
        string status = (t.stressIndex > 1.0) ? "CRITICAL" : 
                        (t.stressIndex > 0.7) ? "Urgent"   : 
                        (t.stressIndex > 0.4) ? "Warning"  : "Chill";

        // แสดงผลข้อมูลงานแต่ละแถว โดยเน้นการจัดระยะให้ตรงกันด้วย printf format
        // %-15s: ชื่อ (15 ช่อง), D%d: วันเดดไลน์, %-6.1f: เวลาทศนิยม 1 ตำแหน่ง
        printf("%-15s D%d %02d:%02d    %-6.1f ชม.         %-6.1f ชม.         ", 
                t.name.c_str(), t.deadlineDay, t.deadlineHour, t.deadlineMinute, freeTime, needTime);
        
        cout << status << endl;
    }
    cout << string(85, '-') << endl;
}