#include "Algorithm.h"
#include "data.h"
#include "backend.h" // ต้องใช้ getNetFreeMinutes

void processTaskPriority() {
    for (auto& t : taskList) {
        int free = getNetFreeMinutes(t.deadlineDay, t.deadlineHour, t.deadlineMinute);
        t.stressIndex = (free <= 0) ? 999.0 : (double)t.remainingMinutes / free; //คำนวณความรีบของงาน
    }

    sort(taskList.begin(), taskList.end(), [](const Task& a, const Task& b) {
        return a.stressIndex > b.stressIndex;//จัดลำดับความสำคัญ
    });
}