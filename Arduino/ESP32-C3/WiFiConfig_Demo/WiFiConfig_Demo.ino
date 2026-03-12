/**
 * 项目名称：ESP32-C3 极致静默配网方案 (终极版)
 * 功能特性：
 * 1. 绝对静默：只要配过网，任何情况下（路由器关机、重启）均不自发热点。
 * 2. 物理重置：唯一进入配网模式的途径是开机长按 BOOT 键（GPIO 9）5秒。
 * 3. 首次引导：若芯片从未配置过 Wi-Fi，开机自动进入配网模式。
 * 4. 内核重连：利用 ESP32 底层自愈机制，实现路由器恢复后的秒级归队。
*/

#include <WiFi.h>
#include <WiFiManager.h>
#include <esp_wifi.h> // 核心：用于读取底层持久化配置

// --- 硬件定义 ---
const int RESET_PIN = 9;            // ESP32-C3 默认 BOOT 引脚
const int LONG_PRESS_TIME = 5000;   // 5秒长按判定

// --- 全局对象 ---
WiFiManager wm;

/**
 * 核心逻辑：从 ESP32 底层 Flash 直接读取 Wi-Fi 配置
 * 解决原生 WiFi.SSID() 在启动瞬时可能返回空值导致的误判
 */
bool hasSavedCredentials() {
    wifi_config_t conf;
    // 从底层接口尝试获取 Station 模式配置
    esp_wifi_get_config(WIFI_IF_STA, &conf);
    // 检查 SSID 第一个字符是否为非空
    return (conf.sta.ssid[0] != 0);
}

/**
 * 封装：进入配网页面逻辑
 */
void enterConfigPortal() {
    Serial.println("\n[System] 进入手动配网模式...");
    Serial.println("[System] 请连接 Wi-Fi 热点: ESP32_C3_AutoDevice");

    wm.setConfigPortalTimeout(180); // 3分钟无操作则自动退出

    // 强制启动配置页面
    if (!wm.startConfigPortal("ESP32_C3_AutoDevice", "abc12345678")) {
        Serial.println("[WiFi] 配网超时或失败");
    } else {
        Serial.println("[WiFi] 配网成功，正在保存并重启...");
    }

    delay(1000);
    ESP.restart(); // 重新加载 NVS 里的新配置
}

/**
 * 物理按键检测：开机时调用
 */
void checkResetButton() {
    pinMode(RESET_PIN, INPUT_PULLUP);

    if (digitalRead(RESET_PIN) == LOW) {
        Serial.println("\n[System] 检测到按键按下，验证长按重置...");
        unsigned long startTime = millis();

        while (digitalRead(RESET_PIN) == LOW) {
            unsigned long duration = millis() - startTime;
            if (duration > LONG_PRESS_TIME) {
                Serial.println("[System] 长按确认！正在抹除旧配置...");
                wm.resetSettings(); // 清除 WiFiManager 保存的信息
                enterConfigPortal(); // 直接开启配网
            }
            delay(10);
        }
        Serial.println("[System] 按键提前释放，继续正常启动程序。");
    }
}

void setup() {
    Serial.begin(115200);
    delay(1500); // 💡 给系统 1.5 秒稳定时间，确保 NVS 加载完成
    Serial.println("\n\n=== ESP32-C3 WiFi Silent Manager Started ===");

    // 1. 物理安全检查：只有按住 5 秒才会有热点
    checkResetButton();

    // 2. 逻辑分流：检查底层是否有保存过的凭据
    if (!hasSavedCredentials()) {
        Serial.println("[System] 未发现 Wi-Fi 凭据，自动进入配网引导...");
        enterConfigPortal();
    }

    // 3. 静默连接模式：绝对禁止自发热点
    Serial.println("[WiFi] 发现已保存凭据，开启静默连接模式...");

    WiFi.mode(WIFI_STA);        // 强制设为 STA 模式，杜绝 AP 模式
    WiFi.setAutoReconnect(true); // 启用内核级自动重连
    WiFi.begin();                // 自动使用底层 Flash 存储的 SSID 和密码

    // 仅在初始化时打印重连进度，不阻塞后续 loop
    int retryCount = 0;
    while (WiFi.status() != WL_CONNECTED && retryCount < 20) {
        delay(500);
        Serial.print(".");
        retryCount++;
    }
    Serial.println("");
}

void loop() {
    static unsigned long lastMonitor = 0;
    unsigned long now = millis();

    // 监控守护：每 10 秒报告一次状态
    if (now - lastMonitor > 10000) {
        lastMonitor = now;

        if (WiFi.status() == WL_CONNECTED) {
            Serial.printf("[Monitor] 在线 | IP: %s | 信号: %d dBm\n",
                          WiFi.localIP().toString().c_str(), WiFi.RSSI());
        } else {
            // 这里绝对不会触发热点，只是在串口静默提示
            Serial.println("[Monitor] 离线 | 路由器未连接，系统内核重连中...");
        }
    }

    // --- 在此处添加您的业务逻辑 (如读取传感器数据、MQTT上传等) ---
}
