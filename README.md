# 🤖 RoboCup Soccer 1v1 Robot

![RoboCup](https://img.shields.io/badge/Competition-RoboCup%20Junior-blue)
![Status](https://img.shields.io/badge/Status-Active-success)
![Platform](https://img.shields.io/badge/Microcontroller-RP2040-orange)
![License](https://img.shields.io/badge/License-MIT-green)

---

## 🚀 Overview

This repository contains the development of our autonomous RoboCup Junior Soccer 1v1 robot.

The robot is designed to:

- ⚽ Detect and track the infrared soccer ball  
- 🧭 Maintain orientation using an IMU  
- 🛑 Detect boundaries and avoid leaving the field  
- 🎯 Play strategically in competitive matches  
- 📡 Communicate via Bluetooth for debugging  

---

## 🛠 Hardware

### Main Components

- **Microcontroller:** RP2040 Zero  
- **IR Sensors:** 16x TSSP58038 (360° ball detection)  
- **IMU:** BNO055  
- **Motor Driver:** Pololu Motor Controller  
- **Motors:** 12V 25Dx48L HP Metal Gearmotors  
- **Custom 2-layer PCB design**

---

## 💻 Software

- **Language:** C++ (Arduino Framework)  
- **Environment:** PlatformIO  
- **Architecture:** Modular sensor & motor control system  
- **Communication:** Bluetooth debugging interface  
- **Control System:** Gyro stabilization + dynamic speed control  

---

## 📂 Project Structure

```
.
├── src/        # Main robot code
├── lib/        # Custom libraries
├── hardware/   # PCB files & schematics
├── docs/       # Documentation & strategies
└── README.md
```

---

## 🧠 Key Features

### 360° Ball Detection
Using 16 IR sensors placed evenly around the robot.

### Orientation Stabilization
Gyroscope-based correction system to prevent unwanted rotation.

### Dynamic Motor Control
Motor speed adapts based on load and match situation.

### Modular PCB System
Stacked upper & lower board for optimized space usage.

---

## 📸 Robot Preview

Add an image in an `images` folder and use:

![Robot](images/robot.jpg)

---

## 📱 Social Media

Follow our development journey:

- 📸 Instagram: https://instagram.com/yourusername  
- ▶ YouTube: https://youtube.com/yourchannel  
- 🎵 TikTok: https://tiktok.com/@yourusername  
- 🌍 Website: https://yourwebsite.com  

---

## 🏆 Competition

Developed for:

**RoboCup Junior Soccer – 1v1 Category**

---

## 📈 Future Improvements

- Improved ball tracking algorithm  
- Faster rotation stabilization  
- Advanced match strategy AI  
- PCB revision v2  

---

## 📜 License

This project is licensed under the MIT License.

---

### ⭐ If you like this project, consider giving it a star!