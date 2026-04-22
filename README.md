# 🏭 Product Item Counter
### Intelligent Production Line Monitoring System

---

## 👥 Team Members

| Sl. No | Name | SRN |
|--------|------|-----|
| 1 | Sanjana M Kulkarni | PES1UG24AM249 |
| 2 | Sanvika M Naik | PES1UG24AM253 |
| 3 | Sanika Patil | PES1UG24AM248 |

---

## 📌 Project Overview

The **Product Item Counter** is an Intelligent Production Line Monitoring System designed to automate item counting while incorporating modern industrial requirements like **power saving** and **real-time processing**.

The system uses a **State-Machine logic** to manage transitions between an idle and active state, triggered by human presence detection — making it both efficient and smart.

---

## ⚙️ Components Used

| Component | Description |
|-----------|-------------|
| **Arduino Uno** | ATmega328P-based microcontroller acting as the central processing unit. Manages sensor data and updates the display via the I2C protocol. |
| **IR Proximity Sensor** | Digital sensor for high-speed item counting. Works on infrared reflection and triggers a Hardware Interrupt on the Arduino. |
| **PIR Sensor** | Passive Infrared sensor for system power management. Detects human presence to wake the system from an idle state. |
| **I2C 16×2 LCD** | Liquid crystal display that serves as the User Interface (UI), showing live item count and system status. |

---

## 🔌 Circuit Connections

### Power Rails
- Arduino **5V** and **GND** connected to the breadboard `+` and `-` rails.

### IR Sensor
| Pin | Connection |
|-----|------------|
| VCC | 5V |
| GND | GND |
| OUT | Digital Pin 2 *(Interrupt Pin)* |

### PIR Sensor
| Pin | Connection |
|-----|------------|
| VCC | 5V |
| GND | GND |
| OUT | Digital Pin 11 |

### I2C LCD
| Pin | Connection |
|-----|------------|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

---

## 🔄 System Logic (State Machine)
IDLE STATE  ──(PIR detects human)──►  ACTIVE STATE
│
IR sensor counts items
│
(No motion for 10 seconds)
│
▼
IDLE STATE

1. **Idle State** — PIR sensor monitors the workstation. LCD backlight is off to save power.
2. **Active State** — PIR detects an operator; the system "wakes up" and enables the display.
3. **Counting** — As items pass on a conveyor, the IR sensor detects transitions. Edge-Triggered Interrupts ensure each item is counted **exactly once**, regardless of speed.

---

## 🧠 Pseudocode
INITIALIZE I2C_LCD, IR_Sensor, PIR_Sensor
SET Count = 0
SET System_Active = FALSE
LOOP infinitely:
READ PIR_Sensor_Signal
IF PIR_Signal is HIGH:
    SET System_Active = TRUE
    TURN ON LCD Backlight
    RECORD Current_Time as Last_Motion_Time

IF System_Active is TRUE:
    IF IR_Sensor detects FALLING_EDGE (Object passes):
        INCREMENT Count
        UPDATE LCD with New_Count

    IF (Current_Time - Last_Motion_Time) > 10 seconds:
        SET System_Active = FALSE
        TURN OFF LCD Backlight
        DISPLAY "Idle Mode"
END LOOP

---

## 📸 Output

<img width="211" height="320" alt="Picture1" src="https://github.com/user-attachments/assets/1823a378-b50c-45bf-86ea-0304aff04e9d" />

---

## 🚀 How to Run

1. Connect all components as per the circuit diagram above.
2. Open the `.ino` file in the [Arduino IDE](https://www.arduino.cc/en/software).
3. Install the required library:
   - `LiquidCrystal_I2C` (available via Library Manager)
4. Select **Board:** Arduino Uno and the correct **COM Port**.
5. Click **Upload**.
6. Power the circuit — wave your hand in front of the PIR sensor to activate the system, then pass objects in front of the IR sensor to count them.

---

## 📁 Repository Structure
📦 product-item-counter
┣ 📄 product_item_counter.ino   # Main Arduino sketch
┣ 📄 README.md                  # Project documentation
┗ 📁 images/                    # Circuit diagram and output photos

---

## 📚 Libraries Used

- [`LiquidCrystal_I2C`](https://github.com/johnrickman/LiquidCrystal_I2C) — For controlling the I2C LCD display.
- `Arduino.h` — Standard Arduino library (built-in).

---


