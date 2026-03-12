# install WiFiManager 
```
虽然 WiFi.h 是 ESP32 开发板包自带的，但 WiFiManager 是一个第三方库，需要手动添加。

你可以通过以下两个方法解决：

方法一：通过库管理器安装（最简单）
打开 Arduino IDE。

点击左侧工具栏的 库管理器 图标（看起来像一叠书），或者使用快捷键 Ctrl + Shift + I。

在搜索框中输入 WiFiManager。

找到由 tablatronix 编写的那个版本（通常名字就叫 WiFiManager）。

点击 安装 (Install)。

注意：如果弹出提示需要安装其他依赖库（如 WebSockets 等），请选择 "Install All"。

方法二：下载 ZIP 包安装
访问 GitHub - WiFiManager。

点击绿色按钮 Code -> Download ZIP。

在 Arduino IDE 中，点击顶部菜单：项目 (Sketch) -> 包含库 (Include Library) -> 添加 .ZIP 库 (.Add .ZIP Library...)。

选择你刚才下载的 ZIP 文件即可。
```
