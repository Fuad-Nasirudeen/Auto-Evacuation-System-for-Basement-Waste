# Auto Evacuation System for Basement Waste

An smart system designed to automatically evacuate wastewater from basement septic tanks using sensor-based monitoring and intelligent pump control.

This project was developed in the **Department of Mechatronics Engineering, Bayero University Kano** as part of the prerequisite for the Bachelor of Engineering degree.

![System](https://github.com/Fuad-Nasirudeen/Dano-Airlines-Customer-Satisfaction-Analysis/blob/main/Dana%20Image.jpeg)

---

# Project Overview

Basement septic systems often lie below the natural drainage gradient, making gravity-based discharge impossible. Waste accumulates and must be evacuated manually or via pumping systems.

This project presents a microcontroller-based smart waste evacuation system that:

- Continuously monitors septic tank waste level
- Automatically activates pumps when needed
- Detects pump failure
- Switches to a backup pump
- Displays real-time system status
- Performs periodic flushing to prevent stagnation

The system provides a low-cost automation solution for smart waste management in basement environments.

---

# Key Features

- Automatic waste level monitoring
- Dual pump redundancy (Primary + Backup)
- Real-time LCD system monitoring
- Pump failure detection
- Manual override mode
- Time-based maintenance flushing
- Closed-loop feedback control
- Low-cost microcontroller implementation

---

# System Architecture

The system consists of three main subsystems:

## 1. Sensing System
Measures septic tank liquid level.

**Component used:**

- Ultrasonic Sensor (HC-SR04)

**Function:**

- Measures distance from sensor to liquid surface
- Arduino converts distance to tank level percentage

---

## 2. Control System
Processes sensor data and executes logic.

**Component used:**

- Arduino Uno

**Responsibilities:**

- Read sensor data
- Calculate tank level
- Control pumps via relays
- Detect pump failure
- Run maintenance flush timer
- Update LCD display

---

## 3. Actuation System
Performs the evacuation process.

**Components used:**

- Primary DC Pump
- Backup DC Pump
- Relay Modules

**Operation:**

- Pump 1 activates when tank reaches **70% level**
- Pump stops when level drops to **20%**
- Pump 2 activates automatically if Pump 1 fails

---

# System Circuit Diagram

![Ciruit Diagram](https://github.com/Fuad-Nasirudeen/Auto-Evacuation-System-for-Basement-Waste/blob/main/AEBW.PNG)

---

# Hardware Components

| Component | Quantity |
|--------|--------|
| Arduino Uno | 1 |
| Ultrasonic Sensor (HC-SR04) | 1 |
| 16x2 LCD with I2C | 1 |
| Relay Module | 2 |
| DC Water Pump | 2 |
| Push Button | 1 |
| Breadboard | 1 |
| Plastic Containers (Tank Model) | 3 |
| Water Hose | 1 |
| Power Supply | 12V |

---


# Control Algorithm

The system operates using the following logic:

1. Measure tank level using ultrasonic sensor
2. Convert distance to percentage
3. If level ≥ 70%  
   → Activate primary pump
4. Monitor level reduction
5. If level does not reduce within timeout  
   → Activate backup pump
6. Stop pumping when level ≤ 20%
7. Trigger maintenance flush if idle for a long period
8. Allow manual override via push button

---

# Software Tools

## Arduino IDE (v2.3.2)

Used for:

- Writing embedded C/C++ code
- Compiling firmware
- Uploading code to Arduino

---

## Proteus Design Suite (v8.17)

Used for:

- Circuit simulation
- Arduino code testing
- Virtual prototyping

Simulation allowed:

- Testing pump control logic
- Verifying sensor response
- Debugging circuit before hardware implementation

---

# Time-Based Flush Feature

Traditional systems rely solely on **level-based triggers**.

However, waste may stagnate when the tank is not used frequently.

To solve this, the system includes **periodic flushing**.

**Operation:**

- Arduino tracks time since last pump cycle
- If system remains idle beyond threshold
- A short maintenance pump cycle is executed

**Advantages:**

- Prevents waste stagnation
- Reduces odor
- Prevents hydrogen sulfide corrosion
- Keeps pumps functional

---

# Experimental Results

## Ultrasonic Sensor Accuracy

| Actual Distance | Sensor Reading | Error |
|---|---|---|
10 cm | 10.4 cm | 4% |
15 cm | 15.3 cm | 2% |
20 cm | 19.7 cm | 1.5% |
25 cm | 25.5 cm | 2% |
30 cm | 30.2 cm | 0.7% |

Average error ≈ **2%**

---

## Pump Performance

| Parameter | Value |
|------|------|
Activation threshold | 70% |
Stop threshold | 20% |
Pump start delay | 0.5 sec |
Full evacuation time | ~12 sec |

---

## Backup Pump Test

When Pump 1 was disconnected:

- Arduino detected no level drop
- Backup pump activated after **10 seconds**
- Evacuation completed successfully

---

## Time-Based Flush Test

Idle tank condition triggered:

- Automatic flush after preset period
- Pump operated for **15 seconds**
- System reset timer afterward

---

# Project Results

The prototype successfully demonstrated:

- Accurate level monitoring
- Reliable automatic pumping
- Intelligent pump fault detection
- Backup redundancy
- Time-based maintenance operation
- Real-time LCD monitoring

The system achieved **all project objectives**.

---

# Advantages of the System

- Reduces manual septic maintenance
- Prevents overflow incidents
- Improves hygiene and sanitation
- Provides fault tolerance via backup pump
- Low-cost and scalable solution

---

# Limitations

- Prototype uses small DC pumps
- Designed for demonstration scale
- Industrial deployment requires stronger pumps and sensors

---

# Future Improvements

Possible upgrades include:

## IoT Monitoring
Add WiFi or GSM module to enable:

- Remote monitoring
- SMS alerts

## Data Logging
Store operational data using:

- SD card
- Cloud database

## Renewable Power
Add:

- Solar panels
- Battery backup

## Industrial Components
Use:

- Submersible sewage pumps
- Industrial-grade sensors

## Smart Control
Implement advanced control algorithms:

- PID control
- Fuzzy logic
- Predictive maintenance

---


# License

This project is released for **educational and research purposes**.
