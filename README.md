# Biometric Attendance Verification System (BAVS)

An Arduino-based biometric attendance management system developed using Object-Oriented Programming (OOP) principles.

## Features
- Admin fingerprint authentication
- Student fingerprint enrollment
- Attendance marking
- Duplicate attendance prevention
- Attendance records viewing
- Attendance reset
- Automatic admin logout after inactivity

## Hardware Components
- Arduino Uno
- Fingerprint Sensor
- 4×4 Matrix Keypad
- I2C LCD Display
- Buzzer

## Technologies Used
- Arduino IDE
- Embedded C++ / OOP
- Fingerprint Authentication
- LCD Interface
- Keypad Navigation

## OOP Concepts Implemented
- Encapsulation
- Abstraction
- Inheritance
- Polymorphism

## Hardware Connections

### LCD
- SDA → A4
- SCL → A5

### Fingerprint Sensor
- TX → 10
- RX → 11

### Keypad
- A0, A1, A2, A3, 2, 3, 4, 5

### Buzzer
- Positive → 12
- Negative → GND

## System Workflow
1. Admin authenticates using fingerprint
2. Admin accesses system menu
3. Students enroll fingerprints
4. Attendance session opens
5. Students scan fingerprints
6. Attendance is recorded
7. Duplicate attendance is prevented
8. Session closes automatically after timeout

## Author
AMBWERE MELVINE JERRY  
ENE212-0166/2024

## Course
ECE

## Unit
EEC2212
