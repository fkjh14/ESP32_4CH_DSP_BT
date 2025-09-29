ESP32 Wroom DSP with BT
A project that utilizes an ESP32 in combination with DSP functions to play music via Bluetooth or an
analog input and to adjust DSP parameters via WLAN (Web UI).
Features
• Bluetooth Wireless Audio & Analog Audio Input
• DSP with the following features:
• Gain / Polarity / Mute / Source Select / Internal Mono-Summing
• Individual Highpass / Lowpass per channel
• 5 parametric equalizers per channel (Bell, HighShelf, LowShelf)
• Delay up to 30ms per channel
• Power output limiter
• Virtual Bass Enhancement
• Dynamic Bass Boost
• Integrated WIFI Access Point and Windows-based UI software
• Enables real-time DSP modification
• One software tool to configure everything and supports saving/loading presets as a file
How to Install
1. Download the code in the Zip from
https://github.com/fkjh14/ESP32_4CH_DSP_BT_AMPLIFIER/tree/main.
2. Install and open Visual Studio Code.
3. Install the ESP-IDF extension.
4. Click on the extension (on the left side) → click on "advanced" at the bottom → "configure
esp-idf extension" → a new window opens → click on "EXPRESS" → click on "Show all ESP-IDF
tags" → under "Select ESP-IDF version", choose 4.2 → press "Install".
5. Unzip the downloaded file and open "esp-idf firmware" as a folder in VSCode.
6. Connect the ESP32 to the PC via USB.
7. Select the correct COM port in the bottom bar (available devices are displayed above under
the search bar).
8. Click on "open esp idf terminal" in the bottom bar.
9. In the terminal, type "idf.py flash" to flash the ESP32.
10. If the terminal displays "Connecting", you may need to press the "Boot" button on the ESP32.
11. After the Terminal displays “Done”, you are ready to use your DSP software or play Music
through Bluetooth.
Pin Outputs I2S Signal
I2S Output Ch1&2:
LCK (Left/Right Clock) → GPIO 25
DIN (Data In) → GPIO 22
BCK (Bit Clock) → GPIO 26
I2S Output Ch 3&4:
LCK (Left/Right Clock) → GPIO 4
DIN (Data In) → GPIO 16
BCK (Bit Clock) → GPIO 27
Pin Layouts
Pin Layout from ESP32 to Audio Dac Ch1&2 (like in our Project):
Connection Audio DAC Connection ESP32
Vin 3,3v
Gnd Gnd
LCK GPIO 25
DIN GPIO 22
BCK GPIO 26
Pin Layout Audio Dac Ch3&4 (like in our Project):
Connection Audio DAC Connection ESP32
Vin 3,3v
Gnd Gnd
LCK GPIO 4
DIN GPIO 16
BCK GPIO 27
Mode Switch:
WLAN (GUI Mode) GPIO 34 → GND
BT Mode GPIO 34 → 3,3v
For the Switch, make the desired connection and eighter press the “EN” or “RST” (the abbreviation
might varie) button on the PCB of the ESP32 or unplug and replug the ESP to power.
GUI Instructions
1. Establish a WIFI signal by connecting the right pins (see above).
2. Connect to the WIFI.
3. Open the GUI.
4. Press "Reset All" once to set all settings to default.
5. Adjust the settings as desired.
6. With the "Control link" function, the same settings from the current channel are applied to
the selected channels.
7. To save the settings, press "Upload to Device".