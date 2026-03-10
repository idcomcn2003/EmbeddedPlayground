"""
MicroPython v1.20.0 on 2023-04-26; ESP module with ESP8266
Type "help()" for more information.
只要将程序名xxx.py改为main.py，就让开发板开机自启动该脚本了。
"""

import time
from machine import Pin


### idcomcn2023 20231124
### 循环点灯灭灯

def main():
    led = Pin(2, Pin.OUT)  # create LED object from pin2,Set Pin2 to output
    while True:
        led.value(1)  # Set led turn on
        time.sleep(0.5)
        led.value(0)  # Set led turn off
        time.sleep(0.5)


if __name__ == '__main__':
    main()

