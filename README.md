# ESP32 Smart Gas & Smoke Detector 

A complete IoT-based gas and smoke detection system built with an ESP32 and an MQ-2 sensor. This project provides real-time environmental monitoring via a local web server dashboard, visual and audible alerts, and automated physical response using a servo-controlled ventilation mechanism.

##  Features
* **Live Web Dashboard:** Monitors real-time analog gas concentration levels via a lightweight embedded web server accessible from any device on the local network.
* **Automated Ventilation:** Actuates an SG90 servo motor (e.g., to open a vent or close a valve) automatically when dangerous gas levels are detected.
* **Local Alerts:** Triggers an active piezo buzzer and a red warning LED during emergency states.

##  Hardware Requirements
* ESP32 Development Board
* MQ-2 Gas/Smoke Sensor Module
* SG90 Micro Servo Motor
* Active Piezo Buzzer
* 2x LEDs (1 Red, 1 Green)
* 2x 220Ω Resistors
* Breadboard and Jumper Wires

##  Circuit & Pin Configuration

| Component | Pin / Wire | ESP32 Connection | Notes |
| :--- | :--- | :--- | :--- |
| **MQ-2 Sensor** | VCC | `5V` (VIN) | Recommended 5V for internal heater |
| | GND | `GND` | |
| | AO (Analog Out) | `GPIO 34` | DO pin is left disconnected |
| **Buzzer** | Positive (+) | `GPIO 23` | |
| | Negative (-) | `GND` | |
| **Servo Motor** | Signal (Orange/Yellow)| `GPIO 18` | Requires ESP32 PWM support |
| | VCC (Red) | `5V` (VIN) | |
| | GND (Brown/Black) | `GND` | |
| **LEDs** | Green LED (+) | `GPIO 21` | Connect via 220Ω resistor |
| | Red LED (+) | `GPIO 22` | Connect via 220Ω resistor |

##  Software Setup & Installation

### 1. Prerequisites
* [Arduino IDE](https://www.arduino.cc/en/software) installed.
* ESP32 Board Package installed in Arduino IDE (`Tools > Board > Boards Manager`).
* **ESP32Servo Library** by Kevin Harrington installed (`Sketch > Include Library > Manage Libraries`).

### 2. Configuration
1. Clone this repository or download the `.ino` file.
2. Open the sketch in Arduino IDE.
3. Update the network credentials in the code to match your home network:
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
