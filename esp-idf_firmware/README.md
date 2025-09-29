# ESP-IDF A2DP-SINK Demo

> **Note:** This project is based initially on the A2DP-SINK demo from Espressif.

| Supported Targets | ESP32 |
| ----------------- | ----- |

## Overview

This demo implements the **A2DP audio sink role** using the Advanced Audio Distribution Profile to receive audio streams from Bluetooth devices.

### Key Features

- **A2DP**: Bluetooth legacy profile for audio stream reception
- **AVRCP**: Media information notifications
- **I2S**: Audio stream output interface

This example serves as a reference for basic functionalities that applications such as Bluetooth speakers can utilize.

## How to use this example

### Hardware Required

#### Audio Output Options

1. **External I2S Codec + Loudspeaker** (Recommended)
   - Provides high-quality audio output
   - Tested with PCM5102 chip (other I2S boards should work as well)

2. **Internal DAC + Loudspeaker** (Alternative)
   - Uses ESP32's built-in DAC
   - Limited to 8-bit resolution
   - No external codec required

> **Note:** Without a loudspeaker, the example will only display audio packet counts without audible output.

#### I2S Pin Configuration

| ESP32 Pin | I2S Signal | Description |
| :-------- | :--------- | :---------- |
| GPIO22    | LRCK       | Left/Right Clock |
| GPIO25    | DATA       | Audio Data |
| GPIO26    | BCK        | Bit Clock |

> 📝 **Configuration Note:** Pin assignments can be modified through `idf.py menuconfig`

#### Internal DAC Output

When using internal DAC:
- **GPIO25**: Analog audio output (8-bit resolution)
- **GPIO26**: Analog audio output (8-bit resolution)

### Project Configuration

Run the configuration menu:

```bash
idf.py menuconfig
```

#### Required Configuration Steps

1. **Audio Output Selection**
   - Navigate to: `A2DP Example Configuration`
   - Choose between external I2S codec or internal DAC
   - Configure output pins as needed

2. **Bluetooth Configuration**
   - Navigate to: `Component config` → `Bluetooth` → `Bluedroid Enable`
   - Enable Classic Bluetooth and A2DP support

### Build and Flash

Build, flash, and monitor the project:

```bash
idf.py -p PORT flash monitor
```

> 💡 **Tip:** Replace `PORT` with your actual serial port (e.g., `COM3` on Windows, `/dev/ttyUSB0` on Linux)

**Exit monitor:** Press `Ctrl+]`

## Example Output

### Device Discovery

After startup, the example enters discoverable mode:
- 📱 **Device Name**: `ESP_SPEAKER`
- 🔍 **Status**: Awaiting connection from Bluetooth devices
- 📱 Compatible devices: Smartphones, tablets, or other A2DP source devices

### Connection Establishment

Upon successful A2DP connection, you'll see:

```
I (106427) BT_AV: A2DP connection state: Connected, [64:a2:f9:69:57:a4]
```

### Audio Streaming

When audio playback starts from the connected device:

```
I (120627) BT_AV: A2DP audio state: Started
I (122697) BT_AV: Audio packet count 100
I (124697) BT_AV: Audio packet count 200
I (126697) BT_AV: Audio packet count 300
I (128697) BT_AV: Audio packet count 400
```

### Audio Output

- 🔊 **With Loudspeaker**: Audio will be heard through connected speakers
- 📊 **Without Loudspeaker**: Only packet counts are displayed in the console

> **Note**: When using ESP32 A2DP source as input, the audio output will be noise since the source generates random sample sequences.

## Troubleshooting

### Audio Codec Support

- **Supported Codec**: SBC (Sub-Band Coding)
- **Audio Format**:
  - Sample Rate: 44.1kHz
  - Channels: Stereo (2-channel)
  - Bit Depth: 16-bit PCM
- **Custom Configurations**: Other decoder settings require protocol stack modifications

### Connection Limitations

- **Maximum Connections**: One A2DP source device at a time
- **Profile Compatibility**:
  - ❌ Cannot run A2DP sink and A2DP source simultaneously
  - ✅ Compatible with other profiles (SPP, HFP)

### Common Issues

- **No Audio Output**: Verify loudspeaker connections and I2S configuration
- **Connection Issues**: Ensure Bluetooth is properly enabled in menuconfig
- **Audio Quality**: Check if external I2S codec is properly connected
