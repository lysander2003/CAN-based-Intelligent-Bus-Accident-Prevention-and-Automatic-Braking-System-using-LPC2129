# CAN-Based Vehicle Safety and Alert System using LPC2129

## Overview
This project implements a **Controller Area Network (CAN) based Vehicle Safety and Alert System** using the **LPC2129 ARM7 microcontroller**. The system enables reliable real-time communication between multiple vehicle nodes through the CAN bus, allowing safety-critical information to be transmitted efficiently with minimal latency.

The project demonstrates the use of CAN communication in automotive environments, where different electronic control units (ECUs) exchange information for monitoring and safety purposes. By utilizing the LPC2129's built-in CAN controller, the system ensures robust and fault-tolerant communication between nodes.

---

## Objectives
- Implement CAN communication using LPC2129.
- Enable real-time data exchange between multiple nodes.
- Demonstrate message transmission, reception, and arbitration.
- Improve vehicle safety through timely alert generation.
- Understand automotive networking concepts and protocols.

---

## Features
- Real-time CAN communication
- Multi-node communication architecture
- CAN frame configuration and message arbitration
- Error detection and handling
- Reliable and fault-tolerant data transmission
- Embedded C firmware development
- Scalable design for automotive applications

---

## Hardware Requirements
- LPC2129 ARM7 Microcontroller
- CAN Transceiver (e.g., MCP2551)
- Power Supply
- Connecting Wires
- Development Board

---

## Software Requirements
- Keil µVision
- Flash Magic
- Embedded C

---

## System Architecture

Node A (Transmitter)
↓
CAN Bus
↓
Node B (Receiver)

The transmitter node sends safety-related messages through the CAN bus, while the receiver node processes the received data and triggers the necessary alerts or actions.

---

## Working Principle
1. The LPC2129 initializes the CAN controller and configures communication parameters.
2. Safety-related data is collected and packed into CAN frames.
3. The transmitter node sends messages over the CAN bus.
4. The receiver node receives and validates the CAN frames.
5. Appropriate alerts or actions are generated based on the received information.
6. CAN error detection mechanisms ensure reliable communication.

---

## Technologies Used
- LPC2129 (ARM7TDMI-S)
- Embedded C
- Controller Area Network (CAN)
- Keil µVision
- Flash Magic

---

## Applications
- Vehicle Safety Systems
- Automotive Communication Networks
- Driver Alert Systems
- Industrial Automation
- Distributed Embedded Systems

---

## Learning Outcomes
- Understanding CAN protocol fundamentals
- Embedded firmware development
- Real-time communication systems
- Automotive networking concepts
- Microcontroller peripheral interfacing
- Fault-tolerant system design

---

## Future Enhancements
- Integration with additional vehicle sensors
- Wireless monitoring and diagnostics
- Data logging and analytics
- Advanced safety alert mechanisms
- IoT-based vehicle monitoring

---

## Author
Developed as an embedded systems project to demonstrate practical implementation of CAN-based communication using the LPC2129 microcontroller for automotive safety applications.
