第一步：安装 ESP32 支持库
如果你还没在 Arduino IDE 里看到 ESP32-C3 的选项，需要先安装环境：

打开 文件 (File) -> 首选项 (Settings)。

在“附加开发板管理器地址”中粘贴：
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

点击 工具 (Tools) -> 开发板 (Board) -> 开发板管理器 (Boards Manager)。

搜索 esp32 并安装由 Espressif Systems 提供的最新版本。

第二步：硬件连接与配置
物理连接：用一根 数据线（确保它不仅能充电，还能传输数据）将 ESP32-C3 连接到电脑。

选择开发板：

工具 -> 开发板 -> ESP32 -> ESP32C3 Dev Module。

关键设置（在“工具”菜单里确认）：

USB CDC On Boot: 选 Enabled (非常关键！否则串口监视器没输出)。

Flash Mode: 选 DIO。

选择端口：

工具 -> 端口 (Port) -> 选择出现的 COM 口（通常是 COM3 或更高，Mac/Linux 下显示为 /dev/cu.usb...）。

第三步：烧录代码（上传）
点击 Arduino IDE 左上角的 打钩图标 (Verify)：这会检查代码是否有语法错误。

点击 向右箭头图标 (Upload)：这会将代码编译并“推”送到芯片里。

观察底部状态栏：

如果看到 Writing at 0x00010000... (100%) 和 Hard resetting via RTS pin...，恭喜你，烧录成功了！

新手常遇到的坑：如果上传报错 Failed to connect，请按住板子上的 BOOT 按钮，点上传，等进度条动了再松手。

第四步：如何调试（查看运行结果）
代码烧录进去后，它会立刻运行。我们需要通过“串口监视器”看它有没有连上 WiFi：

点击 IDE 右上角的 放大镜图标（或快捷键 Ctrl+Shift+M）。

设置波特率：在监视器窗口右下角，确保选择 115200 baud。

看输出：

你应该能看到一串点 ....。

如果显示 WiFi 连接成功！ 和 IP 地址，说明你的代码完美运行。

如果一直显示点，请检查代码里的 ssid 和 password 是否写错。