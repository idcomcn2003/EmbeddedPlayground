/**
 * 项目名称：ESP32-C3 继电器开关控制示例
 * 功能描述：通过板载 BOOT 按钮控制继电器的开关状态，支持去抖动处理
 * 硬件说明：
 *   - BUTTON_PIN 9: 板载 BOOT 按钮（内部上拉，按下为 LOW）
 *   - RELAY_PIN 4: 板载继电器或 MOS 管控制引脚
 *   - 状态指示灯：IO3
 *   - 额外引出 IO: IO0 和 IO1
 * 注意事项：请确保已在工具栏选择 "ESP32-C3 Dev Module"
 */

#define BUTTON_PIN 9         //boot键IO
#define RELAY_PIN 4          //继电器IO口
#define DEBOUNCE_DELAY 50    // 去抖动延时，单位：毫秒
  
unsigned long lastDebounceTime = 0;     // 上次检查去抖动的时间
bool lastButtonState = HIGH;            // 上次读取的按钮状态
bool ledState = false;                  // LED的当前状态
  
void setup() {  
  pinMode(BUTTON_PIN, INPUT_PULLUP);    // 设置按钮引脚为输入模式，并启用内部上拉电阻
  pinMode(RELAY_PIN, OUTPUT);           // 设置LED引脚为输出模式
  Serial.begin(115200);                 // 初始化串口通信
}  
  
void loop() {  
  unsigned long currentTime = millis(); // 获取当前时间  
  
  // 读取按钮状态  
  int reading = digitalRead(BUTTON_PIN);  
  
  // 检查是否需要去抖动  
  if ((currentTime - lastDebounceTime) > DEBOUNCE_DELAY) {  
    // 如果按钮状态与上次不同  
    if (reading != lastButtonState) {  
      // 重置去抖动时间  
      lastDebounceTime = currentTime;  
  
      // 更新最后按钮状态  
      lastButtonState = reading;  
  
      // 如果按钮被按下（内部上拉，所以读到LOW是按下）  
      if (reading == LOW) {  
        // 切换LED状态  
        ledState = !ledState;  
  
        // 根据LED状态设置LED引脚  
        digitalWrite(RELAY_PIN, ledState);  
  
        // 打印LED状态  
        if (ledState) {  
          Serial.println("LED ON");  
        } else {  
          Serial.println("LED OFF");  
        }  
      }  
    }  
  }  
}