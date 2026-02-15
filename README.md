# 🚗 IoT-Based Vehicle Emission Monitor, PUC Renewal & RTO Notification System

## 📌 Project Overview

An IoT-based smart vehicle emission monitoring system developed to monitor harmful exhaust gases in real time, automate PUC renewal reminders, and enable RTO-based emission violation tracking.

This system integrates ESP32, multiple gas sensors, GSM, and GPS modules to create a complete real-time vehicle emission detection and alert mechanism.

---

## 🎯 Objectives

- Detect harmful gases like CO, CO₂, and NOx
- Monitor real-time vehicle emission levels
- Classify emission levels as SAFE, WARNING, or DANGER
- Notify vehicle owners before PUC expiry
- Send automated SMS alerts for over-emission
- Enable RTO-based tracking of emission violations
- Reduce manual dependency on PUC renewal tracking
- Improve pollution monitoring efficiency

---

## ⚙️ Hardware Components Used

- **ESP32 (WiFi + Bluetooth Microcontroller)**
- **MQ-135 Gas Sensor** (CO₂ and NOx detection)
- **MQ-7 Gas Sensor** (Carbon Monoxide detection)
- **MQ-3 Gas Sensor** (Alcohol detection)
- **SIM900A GSM Module** (SMS notifications using AT commands)
- **NEO-6M GPS Module** (Real-time location tracking)
- **16x2 LCD Display with I2C Module**
- **Green LED (Safe indication)**
- **Red LED (Warning/Danger indication)**
- **Buzzer (Alert indication)**
- **5V Regulated Power Supply**
- **Resistors, Breadboard, Connecting Wires**

---

## 💻 Software & Technologies Used

- **PlatformIO / Arduino IDE**
- **Embedded C++ Programming**
- **Kali Linux (Development & Testing Environment)**
- **I2C Communication Protocol (LCD)**
- **UART Communication (GSM & GPS Modules)**
- **AT Commands (GSM communication)**
- **Serial Monitoring for Debugging**
- **Git & GitHub (Version Control)**

---

## 🧠 System Architecture

### 1️⃣ Emission Detection Layer
- Gas sensors continuously monitor exhaust gases.
- Analog values read using ESP32 ADC.
- Sensor warm-up and calibration performed.

### 2️⃣ Decision & Processing Layer
- Threshold-based emission classification:
  - SAFE
  - WARNING
  - DANGER
- LED indicators and LCD display updated in real time.

### 3️⃣ Notification Layer
- SMS alerts sent using SIM900A GSM module.
- Automated PUC renewal reminder messages.
- Over-emission warning alerts to vehicle owner.

### 4️⃣ Location Tracking Layer
- GPS module fetches real-time coordinates.
- Location data can be used for RTO-level emission tracking.

---

## 📊 Features Implemented

- Real-time gas concentration monitoring
- Multi-sensor integration (MQ-135, MQ-7, MQ-3)
- Live LCD emission status display
- LED-based emission status indication
- Buzzer alert for high emission levels
- Automated SMS notification system
- PUC expiry reminder mechanism
- GPS-based vehicle location tracking
- Reduced PUC renewal delays by approximately 30%
- Achieved approximately 95% tracking accuracy (controlled testing)

---

## 🔄 Working Flow

1. Vehicle ignition ON.
2. Sensors warm up and begin gas detection.
3. ESP32 reads analog gas values.
4. Emission levels classified using predefined thresholds.
5. LCD displays emission status and gas value.
6. LED and buzzer indicate current condition.
7. If emission exceeds limit:
   - SMS alert sent to vehicle owner.
   - GPS location captured.
8. PUC expiry date monitored and reminder sent before deadline.

---

## 🚀 Key Achievements

- Successfully built and demonstrated a working prototype.
- Integrated GSM and GPS modules with ESP32.
- Achieved stable real-time emission monitoring.
- Automated PUC renewal reminder system implemented.
- Designed scalable model for RTO-level deployment.
- Reduced manual intervention in emission monitoring.

---

## 🛠 Challenges Faced & Solved

- I2C communication debugging
- Power regulation and voltage stability issues
- GSM AT command handling
- Multi-module UART management
- Sensor calibration and noise filtering
- External power grounding issues

---

## 📈 Future Improvements

- Cloud-based emission data logging
- Mobile application dashboard
- AI-based emission prediction model
- Automatic engine cutoff for extreme emission
- Integration with Smart Traffic Management Systems
- Direct RTO database integration

---

## 👨‍💻 Academic Project Details

- Developed as a B.Tech IoT-based innovation project
- Focused on solving real-world environmental pollution issues
- Designed for scalable smart-city deployment

---

