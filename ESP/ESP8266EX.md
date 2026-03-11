# ESP8266EX ESP-12F

## 获取内存大小
```
>esptool flash-id
esptool v5.2.0
Connected to ESP8266 on COM4:
Chip type:          ESP8266EX
Features:           Wi-Fi, 160MHz
Crystal frequency:  26MHz
MAC:                ec:fa:bc:2e:4a:84

Stub flasher running.

Flash Memory Information:
=========================
Manufacturer: 20
Device: 4016
Detected flash size: 4MB

Hard resetting via RTS pin...
```

## 备份固件
```
>esptool --port COM4 --baud 115200 read-flash 0x00000 0x400000 backup_firmware.bin
esptool v5.2.0
Connected to ESP8266 on COM4:
Chip type:          ESP8266EX
Features:           Wi-Fi, 160MHz
Crystal frequency:  26MHz
MAC:                ec:fa:bc:2e:4a:84

Stub flasher running.

Configuring flash size...
Read 4194304 bytes from 0x00000000 in 381.5 seconds (87.9 kbit/s) to 'backup_firmware.bin'.

Hard resetting via RTS pin...
```
