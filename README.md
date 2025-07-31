# Safe-T – Intelligent Air Quality Monitor

![Safe-T Design](images/Safe-T.png)

## 📌 Introduction

**Safe-T** is an intelligent air quality monitoring device designed to detect and respond to indoor air pollution in real-time. It tracks temperature, humidity, and harmful gas concentrations (such as CO₂ and VOCs), providing immediate visual feedback and actionable recommendations to improve the indoor environment.

This project was designed to be **accessible**, **educational**, and **easy to replicate**, particularly in home or classroom settings.

---

## ⚙️ Features

- Measures **ambient temperature** using an **analog TMP36 sensor**
- Detects air pollution with a **gas sensor** (e.g., MQ-135 equivalent)
- Real-time data display on a **16x2 LCD screen**
- Visual alerts via **LEDs** (green, orange, red)
- **Adjustable contrast** for the LCD using a **250 kΩ potentiometer**
- Modular and beginner-friendly **open-source code**

---

## 🛠 Required Components

| Component           | Description                              |
|---------------------|------------------------------------------|
| Arduino Uno R3      | Main microcontroller board               |
| TMP36               | Analog temperature sensor                |
| Gas Sensor          | Detects harmful gases (CO₂, VOCs, etc.)  |
| 16x2 LCD Display    | Displays air quality information         |
| 250 kΩ Potentiometer| Adjusts LCD screen contrast              |
| LEDs + 1 kΩ Resistors| Visual indicators (green, orange, red)  |
| Breadboard + Wires  | For assembling the prototype             |

---

## 📂 Project Structure

<pre>
safe-t/
├── code/          # Arduino source code
├── images/        # Circuit diagrams and screenshots
├── docs/          # Additional documentation
├── LICENSE        # Project license
└── README.md      # This file
</pre>
