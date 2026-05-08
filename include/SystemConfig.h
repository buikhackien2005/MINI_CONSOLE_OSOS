#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

// Danh sách lệnh giao tiếp giữa các task
enum class Cmd : uint8_t {
    NONE         = 0,
    BTN_SHORT    = 1,   // nhấn nút ngắn
    BTN_LONG     = 2,   // giữ nút dài
    SHOW_SCORE   = 10,  // hiển thị điểm
    SHOW_MENU    = 11,  // hiển thị menu
    SHOW_GAMEOVER= 12,  // hiển thị game over
    PLAY_BEEP    = 20,  // phát tiếng beep (Phần 3 xử lý)
};

// Queue toàn cục — khai báo extern ở đây
extern QueueHandle_t   gCmdQueue;
extern SemaphoreHandle_t gSpiMutex;  // Mutex bảo vệ SPI