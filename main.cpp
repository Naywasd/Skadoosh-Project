#include "Data.h"
#include "Backend.h"
#include "UI.h"

int main() {
    
    cout << "=== ตั้งค่ากิจกรรมที่ทำเป็นรายวันหรือทุกวัน (ex.นอน,เรียน) ===\n";
    int rCount; cout << "จำนวนกิจกรรม: "; cin >> rCount;
    for(int i=0; i<rCount; i++) {
        string name; int sH, sM, eH, eM, mode; //ตัวแปรรับเวลาชั่วโมง และ นาทีที่เริ่มรูทีน และวัน
        cout << "\nชื่อกิจกรรม: "; cin >> name;
        cout << "เริ่ม(ชม นาที) จบ(ชม นาที): "; cin >> sH >> sM >> eH >> eM; //รับเวลาเริ่มรูทีน ชั่วโมง - นาที และจบรูทีน ชั่วโมง - นาที
        cout << "ลงตารางแบบไหน? (ระบุวัน): "; cin >> mode;
        cout << "ระบุเลขวัน (1-7) พิมพ์ 0 เพื่อจบ: ";
            int dTarget;
            while(cin >> dTarget && dTarget != 0) {
                if(dTarget >= 1 && dTarget <= 7) fillSchedule(dTarget-1, name, sH, sM, eH, eM); //รับข้อมูลว่า รูทีนนี้ ทำในวันไหนบ้าง เช่น 1 = วันจันทร์
            }
        }
    }
    
    cout << "\n=== เพิ่มงาน (Tasks) ===\n";
    int tCount; cout << "จำนวนงาน: "; cin >> tCount;
    for(int i=0; i<tCount; i++) {
        Task t; double hours;
        cout << "ชื่อ ชม.ที่ใช้ วันส่ง เวลาส่ง(ชม นาที): ";
        cin >> t.name >> hours >> t.deadlineDay >> t.deadlineHour >> t.deadlineMinute; // รับชื่อ เวลา และเดดไลน์ ของงาน
        t.remainingMinutes = (int)(hours * 60); // แปลงชั่วโมงเป็นนาที
        taskList.push_back(t);
    }

while (true) { // loop ไว้ทำฟังก์ชั่นต่างๆ
        displayToDoList();
        cout << "\n[ MENU ]\n1. ดูตารางเวลา\n0. ออก\nเลือก: ";
        int choice; cin >> choice;

        if (choice == 1) { // สร้างตารางเวลา
            printScheduleTable(); // ดึงจาก UI
            cout << "\nกด Enter เพื่อกลับเมนูหลัก..."; cin.ignore(1000,'\n');
            cin.get();
        }
        else if (choice == 0) break;
    }
    return 0;
}



