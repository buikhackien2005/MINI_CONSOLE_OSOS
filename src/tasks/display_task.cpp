#include <Arduino.h>
#include "DisplayManager.h"
#include "SystemConfig.h"

extern DisplayManager display;

void DisplayTask(void* param) {
    Serial.println("[DisplayTask] Core 1 - san sang");

    Cmd  currentCmd = Cmd::NONE;
    char statusMsg[32] = "Cho lenh...";
    uint32_t frame = 0;

    for (;;) {
        // ── Đọc lệnh mới từ Queue ──────────────────
        // Chờ tối đa 33ms.
        if (xQueueReceive(gCmdQueue, &currentCmd, pdMS_TO_TICKS(33)) == pdTRUE) {
            switch (currentCmd) {
                case Cmd::BTN_SHORT:
                    snprintf(statusMsg, sizeof(statusMsg), "Nhan: NGAN");
                    break;
                case Cmd::BTN_LONG:
                    snprintf(statusMsg, sizeof(statusMsg), "Nhan: DAI");
                    break;
                case Cmd::SHOW_MENU:
                    snprintf(statusMsg, sizeof(statusMsg), "MENU");
                    break;
                case Cmd::SHOW_GAMEOVER:
                    snprintf(statusMsg, sizeof(statusMsg), "GAME OVER");
                    break;
                default:
                    break;
            }
        }

        // ── Vẽ màn hình ────────────────────────────
        // Lấy mutex trước khi dùng bus
        if (xSemaphoreTake(gSpiMutex, pdMS_TO_TICKS(50)) == pdTRUE) {

            display.clear();
            display.showText("Mini-Console OS", 5, 0);
            display.drawLine(0, 10, 127, 10);

            // Hiển thị trạng thái nhận được từ Queue
            display.showText(statusMsg, 5, 18, 2);

            // Frame counter nhỏ ở góc dưới phải
            char buf[16];
            snprintf(buf, sizeof(buf), "f%lu", ++frame);
            display.showText(buf, 100, 55);

            display.update();

            xSemaphoreGive(gSpiMutex);   // PHẢI trả mutex!
        }
    }
}