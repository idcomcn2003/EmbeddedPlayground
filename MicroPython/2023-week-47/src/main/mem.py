import gc

"""
MicroPython v1.20.0 on 2023-04-26; ESP module with ESP8266
Type "help()" for more information.
只要将程序名xxx.py改为main.py，就让开发板开机自启动该脚本了。
"""


### idcomcn2023 20230527
### 获取内存的大小

def main():
    # 剩余的可用字节数
    flash_size = gc.mem_free()
    # 获取分配内存的大小，即已使用的字节数
    ram_size = gc.mem_alloc()
    print("Flash Size:", flash_size, "bytes")
    print("RAM Size:", ram_size, "bytes")


if __name__ == '__main__':
    main()
