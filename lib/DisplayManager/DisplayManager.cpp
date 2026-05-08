#include "DisplayManager.h"
#include <Arduino.h>
#include <Wire.h> // Bắt buộc thêm thư viện này để cấu hình I2C

// Constructor
DisplayManager::DisplayManager(uint8_t w, uint8_t h)
    : _oled(w, h, &Wire, -1) {}

bool DisplayManager::begin() {
    // 🛑 ĐÂY LÀ CHỖ CHÚNG TA ĐỔI CHÂN I2C 🛑
    // Wire.begin(SDA_PIN, SCL_PIN)
    Wire.begin(4, 5); 

    // Tiếp tục khởi tạo OLED ở địa chỉ 0x3C
    if (!_oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("[Display] FAIL: khong tim thay OLED o chan 4&5");
        _ready = false;
        return false;
    }
    
    _oled.clearDisplay();
    _oled.display();    // màn hình đen khi mới bật
    _ready = true;
    Serial.println("[Display] OK - san sang tren chan 4&5");
    return true;
}

void DisplayManager::clear() {
    if (!_ready) return;
    _oled.clearDisplay();
}

void DisplayManager::showText(const char* text, uint8_t x, uint8_t y, uint8_t size) {
    if (!_ready) return;
    _oled.setTextSize(size);
    _oled.setTextColor(WHITE);
    _oled.setCursor(x, y);
    _oled.print(text);
}

void DisplayManager::drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    if (!_ready) return;
    _oled.drawRect(x, y, w, h, WHITE);
}

void DisplayManager::drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    if (!_ready) return;
    _oled.drawLine(x1, y1, x2, y2, WHITE);
}

void DisplayManager::update() {
    if (!_ready) return;
    _oled.display(); // Chốt dữ liệu ra màn hình
}