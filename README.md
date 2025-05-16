# ESP Hardware Monitor
Retrieves JSON data from "Open Hardware Monitor" and displays it on a TFT display, providing a quick view of your computer's hardware statistics.



## Details
* **Personal project**: Built for personal use, feel free to customize.
* **Data Parsing**: The JSON is parsed based on Open Hardware Monitor's IDs.

Make sure to create `/include/config.h` and define variables there!

*Example of a config file*:
```cpp
#define WIFI_SSID "mywifi"
#define WIFI_PASSWORD "password"
#define SERVER_URL "192.168.xxx.xxx"
```

You can modify the parsing logic by adjusting the parseHardwareData function in ```src/hardware.cpp```.

Enjoy monitoring your system's performance on a small OLED display!

![pic](https://github.com/user-attachments/assets/c2661131-0eb5-4941-8a82-0d3b21dbbc1a)
