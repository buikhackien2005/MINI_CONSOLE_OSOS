#pragma once   // chỉ include 1 lần, tránh lỗi khai báo kép
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class DisplayManager {

private:  // ← CHỈ DisplayManager biết đến
    Adafruit_SSD1306 _oled;   // đối tượng màn hình vật lý
    bool _ready = false;       // đã khởi tạo xong chưa?

public:   // ← Code bên ngoài được phép gọi

    // Constructor: w=128, h=64 là kích thước mặc định
    DisplayManager(uint8_t w = 128, uint8_t h = 64);

    // PHẢI gọi trong setup() trước mọi thứ khác
    bool begin();

    // Xoá màn hình về đen hoàn toàn
    void clear();

    // Vẽ chuỗi text tại vị trí (x, y)
    void showText(const char* text, uint8_t x, uint8_t y, uint8_t size = 1);

    // Vẽ hình chữ nhật viền (dùng làm khung UI)
    void drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

    // Vẽ đường thẳng từ (x1,y1) đến (x2,y2)
    void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

    // ★ QUAN TRỌNG: gửi buffer → màn hình vật lý
    void update();

    // Kiểm tra đã khởi tạo xong chưa
    bool isReady() const { return _ready; }
};