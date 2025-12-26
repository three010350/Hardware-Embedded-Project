# Garbage Toxic Gas Detection System

This project focuses on detecting toxic gases released from garbage piles located in community areas.  
Garbage accumulation can emit harmful gases that negatively affect human health and the surrounding environment.  
To address this issue, this project was developed to monitor gas levels in real time and provide both local and remote alerts when dangerous conditions are detected.

---

## Project Overview

The system uses two microcontroller boards:
- **Arduino Uno R3** as the main controller for sensor data acquisition and local alerting
- **NodeMCU ESP8266** for wireless communication and LINE notification

Arduino Uno R3 continuously measures gas concentrations using multiple gas sensors.  
When any gas value exceeds predefined safety thresholds, the system:
- Activates a **buzzer** at the garbage site for immediate warning
- Sends a **notification via LINE** using the ESP8266 module

---

## Hardware Components

### Microcontrollers
- Arduino Uno R3
- NodeMCU ESP8266

### Sensors
- **MH-Z14A** – CO₂ gas sensor
- **MQ-7** – Carbon Monoxide (CO) gas sensor
- **MQ-4** – Methane (CH₄) gas sensor

### Output Devices
- **LCD Display** – Displays real-time gas concentration values
- **Buzzer** – Audible alert when gas levels exceed safety limits

---

## System Architecture

- The **Arduino Uno R3** acts as the main board:
  - Reads data from all gas sensors
  - Displays gas values on the LCD
  - Controls the buzzer when dangerous gas levels are detected

- The **NodeMCU ESP8266**:
  - Receives alert signals from the Arduino
  - Connects to Wi-Fi
  - Sends notifications through **LINE Notify**

---

## Project Structure

The main project folder in this repository is named `arduino_project`, organized as follows:

```
arduino_project/
│
├── mix_iot_esp8266/
│   └── (ESP8266 source code for LINE notification and Wi-Fi communication)
│
└── uno/
    └── (Arduino Uno R3 source code for sensor reading, LCD display, and buzzer control)
```

---

## Features
- Real-time toxic gas monitoring
- Local audible warning using a buzzer
- Visual display of gas values via LCD
- Remote notification via LINE application
- Designed for community garbage monitoring

---

## Purpose

This project was developed to:
- Raise awareness of toxic gas emissions from garbage piles
- Improve safety in community areas
- Apply embedded systems and IoT concepts in a real-world environmental problem
- Gain hands-on experience with sensors, microcontrollers, and IoT communication

---

## Technologies Used
- Arduino
- ESP8266 (Wi-Fi & IoT)
- Gas Sensors (MH-Z14A, MQ-7, MQ-4)
- LINE Notify API
