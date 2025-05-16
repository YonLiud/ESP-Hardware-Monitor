# ESP Hardware Monitor
Retrieves JSON data from "Open Hardware Monitor" and displays it on an ESP32 OLED display, providing a quick view of your computer's hardware statistics.

[Click here for the **TFT LCD version**](https://github.com/YonLiud/ESP-Hardware-Monitor/tree/LCD-Version)

## Details
* **Personal project**: Built for personal use, feel free to customize.

* **Data Parsing**: The JSON is parsed based on Open Hardware Monitor's IDs.

Make sure to create `/include/config.h` and define variables there!

*Example of a config file*:
```cpp
#define WIFI_SSID "subnet"
#define WIFI_PASSWORD "roottoor"
#define SERVER_URL "192.168.1.120"
```

You can modify the parsing logic by adjusting the parseHardwareData function in ```src/hardware.cpp```.

Enjoy monitoring your system's performance on a small OLED display!

![cpu](https://github.com/user-attachments/assets/346e475e-fa51-4349-9cb7-6f3c69c9e806)
![gpu](https://github.com/user-attachments/assets/ae3afe98-a2fe-4da6-aeff-3d714a322d1f)
