#include <Arduino.h>
#include "DisplayManager.h"
#include "SystemConfig.h"

void DisplayTask(void*);

// Định nghĩa các biến toàn cục
DisplayManager    display;
QueueHandle_t     gCmdQueue;
SemaphoreHandle_t gSpiMutex;

void setup() {
    Serial.begin(115200);

    // 1. Khởi tạo phần cứng (chân 4 & 5 tự động config trong class)
    if (!display.begin()) { while(1); }

    // 2. Tạo Queue (chứa tối đa 10 lệnh Cmd)
    gCmdQueue = xQueueCreate(10, sizeof(Cmd));
    if (!gCmdQueue) { Serial.println("FATAL: Queue loi!"); while(1); }

    // 3. Tạo Mutex
    gSpiMutex = xSemaphoreCreateMutex();
    if (!gSpiMutex) { Serial.println("FATAL: Mutex loi!"); while(1); }

    // 4. Tạo DisplayTask
    xTaskCreatePinnedToCore(DisplayTask, "Disp", 6144, NULL, 3, NULL, 1);

    // 5. Test: tự gửi vài lệnh vào queue để kiểm tra
    delay(2000);  // chờ 2s đầu tiên
    Cmd cmd = Cmd::BTN_SHORT;
    xQueueSend(gCmdQueue, &cmd, 0);
    delay(2000);  // chờ thêm 2s
    cmd = Cmd::SHOW_GAMEOVER;
    xQueueSend(gCmdQueue, &cmd, 0);
}

void loop() { vTaskDelay(portMAX_DELAY); }