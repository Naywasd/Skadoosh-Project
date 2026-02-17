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
