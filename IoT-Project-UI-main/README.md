# Smart Home for Aged People - IoT and Web Application

## Overview

This project aims to create a smart home system tailored for elderly individuals, combining IoT devices for fall detection, health monitoring, fire/smoke detection, and automatic door control. The system allows real-time communication through MQTT and integrates with OM2M to provide an interactive web interface. The entire system is built using Flask and JavaScript for the frontend, with styling through CSS.

## Features

### IoT Device Integration

1. **Ultrasonic and Gyroscope Sensors**:
   - Detect falls and provide orientation information.
   - Collect data and send it to the central server.
   - Collecting Real-Time location in house.

2. **Health Sensors (BP, Heart Rate, SpO2)**:
   - Continuously monitor vital signs.
   - Send health data to the central server for analysis.

3. **Fire and Smoke Detectors**:
   - Detect the presence of fire or smoke.
   - Trigger alerts and safety protocols.

4. **Automatic Door Control**:
   - Open and close doors based on user interaction or automated triggers.

### Real-time Communication

- **MQTT Server**:
   - Facilitate real-time communication between IoT devices and the central server.
   - Ensure efficient data transfer and control signals.

### OM2M Integration

- **OM2M Transformation**:
   - Convert IoT data and events into OM2M resources.
   - Enable interoperability with the OM2M platform.

### Web Application

- **Flask Backend**:
   - Handle user requests, data processing, and device control.
   - Communicate with IoT devices and OM2M platform.

- **Interactive Frontend**:
   - JavaScript-powered frontend for real-time monitoring and control.
   - User-friendly web interface for accessing data and controlling devices.

- **Styling with CSS**:
   - Create an intuitive and visually appealing web design for the user interface.

## Getting Started

1. **Hardware Setup**:
   - Connect and configure your IoT devices (ultrasonic, gyroscope, health sensors, fire/smoke detectors).
   - Set up the MQTT server for communication.

2. **OM2M Configuration**:
   - Configure the OM2M platform for data transformation and integration.

3. **Flask Backend**:
   - Install dependencies using `pip install -r requirements.txt`.
   - Configure Flask and MQTT settings.

4. **Frontend**:
   - Customize the frontend interface according to your requirements.
   - Ensure JavaScript scripts are set up for real-time interaction.

5. **Styling**:
   - Customize CSS styles for a visually pleasing interface.

6. **Run the Application**:
   - Start the Flask server using `flask run`.
   - Access the web application in your browser.

## Usage

1. **Monitoring Health**:
   - View real-time health data including blood pressure, heart rate, and SpO2.

2. **Safety Alerts**:
   - Receive alerts for falls, fire, or smoke detection.

3. **Door Control**:
   - Control doors manually or set up automated triggers.

## Acknowledgments

- This project was inspired by the need for smart home solutions for elderly individuals.
- Special thanks to the Flask, JavaScript, MQTT, and OM2M communities for their valuable tools and resources.
- Special thanks to my Team members for their consistent hardwork and support.

