# Arduino-Based-Robotic-Arm-Mobile-Control
An Arduino-based robotic arm controlled via a mobile application using Bluetooth communication. The system enables real-time control of multiple servo motors for precise and efficient object manipulation.
# Overview

This project presents the design and development of a 4-degree-of-freedom (4-DOF) robotic arm controlled wirelessly using a custom Android application.

The system integrates embedded control, Bluetooth communication, and mobile app development to enable real-time manipulation, motion recording, and automated playback.

# Project Highlights

Designed and built a complete robotic system from scratch

Developed a custom Android control application

Implemented Bluetooth-based communication protocol

Achieved real-time multi-servo control

Integrated hardware + software + mobile interface

# Demo

👉 (Add your demo GIF here for best results)

/media/demo.gif
# System Diagram
+---------------------+
|   Smartphone App    |
| (MIT App Inventor)  |
+----------+----------+
           |
           | Bluetooth Communication
           v
+----------+----------+
|   HC-05 Bluetooth   |
|      Module         |
+----------+----------+
           |
           | Serial Communication
           v
+----------+----------+
|      Arduino        |
|   (Control Unit)    |
+----------+----------+
           |
           | PWM Signals
           v
+-----------------------------+
|   Servo Motors (4 DOF Arm)  |
| Base | Shoulder | Elbow | Grip |
+-----------------------------+
# Hardware Components
Component	Quantity
Arduino Uno	1
HC-05 Bluetooth Module	1
Servo Motors	4
External Power Supply (5V, ≥2A)	1
Robotic Arm Structure	1
Jumper Wires	As required
# Degrees of Freedom (4 DOF)
Joint	Function
Base	Rotation
Shoulder	Vertical Movement
Elbow	Extension
Gripper	Object Handling
# Circuit Connections
Servo Motors
Servo	Arduino Pin
Base	D5
Shoulder	D6
Elbow	D7
Gripper	D8
Bluetooth Module
HC-05	Arduino
VCC	5V
GND	GND
TX	D3
RX	D4

⚠️ Use an external power supply for stable operation.

# App Interface
 Application Preview

 Interface Description

# Connect / Disconnect Buttons
Establish Bluetooth communication

# Control Sliders

Grip → Gripper control

Elbow → Arm extension

Shoulder → Vertical motion

Base → Rotation

Speed → Movement speed

# Control Buttons

SAVE → Store positions

RUN → Execute sequence

RESET → Clear memory

# Status Display
Shows connection status and saved positions

# Design Considerations

Real-time responsiveness

Simple and intuitive UI

Efficient Bluetooth communication

Scalable for future upgrades

# Mobile Application Development

The Android application was developed using MIT App Inventor, utilising a block-based programming approach.

Core Components:

Bluetooth Client

Sliders for servo control

Buttons for automation

Device selection interface

Communication Protocol
s1<angle>
s2<angle>
s3<angle>
s4<angle>
# Arduino Code
#include <SoftwareSerial.h>
#include <Servo.h>

Servo servo1, servo2, servo3, servo4;
SoftwareSerial Bluetooth(3, 4);

void setup() {
  servo1.attach(5);
  servo2.attach(6);
  servo3.attach(7);
  servo4.attach(8);

  Bluetooth.begin(38400);
}

void loop() {
  if (Bluetooth.available()) {
    String data = Bluetooth.readString();

    if (data.startsWith("s1")) servo1.write(data.substring(2).toInt());
    if (data.startsWith("s2")) servo2.write(data.substring(2).toInt());
    if (data.startsWith("s3")) servo3.write(data.substring(2).toInt());
    if (data.startsWith("s4")) servo4.write(data.substring(2).toInt());
  }
}
# Working Principle

The mobile app sends commands via Bluetooth

Arduino processes incoming data

Servo motors move according to the received angles

Positions can be stored and replayed

# Project Gallery
/images/robot_arm.jpg
/images/circuit.jpg
/images/app_interface.jpg
# Future Improvements

Inverse kinematics implementation

Computer vision integration

ROS-based control

Autonomous pick-and-place system

Upgrade to higher DOF

# Skills Demonstrated

Embedded Systems (Arduino)

Mobile App Development

Bluetooth Communication

Robotics System Integration

Real-Time Control Systems

# Author

Mitesh Salvi
MEng (Hons) Intelligent Automation & Robotics
Edge Hill University

# Support

If you found this project useful, consider giving it a ⭐ on GitHub!

# License

MIT License
