/**
 * 项目名称: ESP32-C3 WiFi 连接示例
 * 功能描述: 实现 WiFi 自动连接、状态监控及掉线重连
 * 注意事项: 请确保已在工具栏选择 "ESP32-C3 Dev Module"
 */

#include <WiFi.h>

// --- 用户配置区 ---
const char* ssid     = "DESKTOP-ABC";     // 替换为你的 2.4G WiFi 名称
const char* password = "abc12345678";     // 替换为你的 WiFi 密码

// --- 函数声明 ---
void connectToWiFi();

void setup() {
  // 初始化串口输出，用于调试
  // 注意：如果看不到输出，请在工具菜单中开启 "USB CDC On Boot"
  Serial.begin(115200);
  delay(2000);

  Serial.println("\n==============================");
  Serial.println("ESP32-C3 启动中...");

  // 1. 初始化 WiFi
  connectToWiFi();
}

void loop() {
  // 2. 检查 WiFi 连接状态，如果断开则尝试重连
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("检测到 WiFi 连接丢失，尝试重连...");
    connectToWiFi();
  }

  // 3. 每隔 10 秒打印一次本地 IP，证明设备在线
  static unsigned long lastTime = 0;
  if (millis() - lastTime > 10000) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("系统在线。当前 IP: ");
      Serial.println(WiFi.localIP());
    }
    lastTime = millis();
  }
}

/**
 * 处理 WiFi 连接的具体逻辑
 */
void connectToWiFi() {
  Serial.print("正在连接到: ");
  Serial.println(ssid);

  // 设置为工作站模式
  WiFi.mode(WIFI_STA);

  // 开始连接
  WiFi.begin(ssid, password);

  // 等待连接结果（带有简单的超时机制）
  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED && attempt < 20) {
    delay(500);
    Serial.print(".");
    attempt++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi 连接成功！");
    Serial.print("IP 地址: ");
    Serial.println(WiFi.localIP());
    Serial.print("信号强度 (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  } else {
    Serial.println("\nWiFi 连接失败，请检查 SSID 和密码。");
  }
  Serial.println("==============================\n");
}