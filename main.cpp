#include "data.h"
#include "backend.h"
#include "UI.h"

int main() {
    
    cout << "=== ตั้งค่ากิจกรรมที่ทำเป็นประจำ(ex.นอน,เรียน) ===\n";
    int rCount; cout << "จำนวนกิจกรรม: "; cin >> rCount;
    for(int i=0; i<rCount; i++) {
        string name; int sH, sM, eH, eM, mode; //ตัวแปรรับเวลาชั่วโมง และ นาทีที่เริ่มรูทีน และวัน
        cout << "\nชื่อกิจกรรม: "; cin >> name;
        cout << "เวลาที่เริ่มและจบ(ชม.และนาที)(ex. 6 00 23 59): "; cin >> sH >> sM >> eH >> eM; //รับเวลาเริ่มรูทีน ชั่วโมง - นาที และจบรูทีน ชั่วโมง - นาที
        cout << "ลงตารางแบบไหน? (1: ทุกวัน, 2: ระบุวัน): "; cin >> mode; // สามารถลงตารางแบบระบุวันหรือทำทุกวันเลยก็ได้
        if(mode == 1) {
            for(int d=0; d<7; d++) fillSchedule(d, name, sH, sM, eH, eM);
        } else {
            cout << "ระบุเลขวันทั้งหมดที่ต้องการลง (1-7) พิมพ์ 0 เพื่อจบ: ";
            int dTarget;
            while(cin >> dTarget && dTarget != 0) {
                if(dTarget >= 1 && dTarget <= 7) fillSchedule(dTarget-1, name, sH, sM, eH, eM);
            }
        }
    }
    
    cout << "\n=== เพิ่มงาน (Tasks) ===\n";
    int tCount; cout << "จำนวนงาน: "; cin >> tCount;
    for(int i=0; i<tCount; i++) {
        Task t; double hours;
        cout << "ชื่อ จำนวนชม.ที่คาดว่าต้องใช้ในการทำ วันส่ง เวลาส่ง(ชม. นาที)(ex. การบ้าน 2 3 23 59) : ";
        cin >> t.name >> hours >> t.deadlineDay >> t.deadlineHour >> t.deadlineMinute; // รับชื่อ เวลา และเดดไลน์ ของงาน
        t.remainingMinutes = (int)(hours * 60); // แปลงชั่วโมงเป็นนาที
        taskList.push_back(t);
    }

while (true) { // loop ไว้ทำฟังก์ชั่นต่างๆ
        displayToDoList();
        cout << "\n[ MENU ]\n1. ดูตารางเวลา\n2. เพิ่มงานใหม่\n3. เพิ่มธุระพิเศษ\n4. แจ้งงานเสร็จ\n5. อัปเดตเวลาปัจจุบัน\n0. ออก\nเลือก: ";
        int choice; cin >> choice;

        if (choice == 1) { // สร้างตารางเวลา
            printScheduleTable(); // ดึงจาก UI
            cout << "\nกด Enter เพื่อกลับเมนูหลัก..."; cin.ignore(1000,'\n');
            cin.get();
        }
        else if (choice == 2) { //เพิ่มงานใหม่
            Task t; double h;
            cout << "ชื่อ / ชม.ที่ใช้ / วันที่ส่ง / เวลาที่ส่ง(ชม นาที): ";
            cin >> t.name >> h >> t.deadlineDay >> t.deadlineHour >> t.deadlineMinute;
            t.remainingMinutes = h * 60;
            taskList.push_back(t);
        }
        else if (choice == 3) { //เพิ่มธุระใหม่
            string name; int d, sH, sM, eH, eM;
            cout << "วัน(1-7) / ชื่อธุระ / เริ่ม(ชม นาที) / จบ(ชม นาที): ";
            cin >> d >> name >> sH >> sM >> eH >> eM;
            if(d >= 1 && d <= 7) fillSchedule(d-1, name, sH, sM, eH, eM);
        }
        else if (choice == 4) { // แจ้ง delete งานที่ทำเสร็จแล้ว
            string n; cout << "ชื่องานที่เสร็จ: "; cin >> n;
            for(int i=0; i<taskList.size(); i++) if(taskList[i].name == n){ 
                taskList.erase(taskList.begin()+i); break; }
        }
        else if (choice == 5) { // บอกเวลาปัจจุบัน ไว้อัปเดตตาราง
            cout << "ระบุวัน(1-7) และเวลา(ชม. นาที) ณ เวลาปัจจุบัน : ";
            cin >> currentDay >> currentHour >> currentMinute;
        }
        else if (choice == 0) break;
    }
    return 0;
}



