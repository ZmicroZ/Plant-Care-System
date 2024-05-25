# Plant Status Monitor

## Overview
This project utilizes a PIC18F4580 microcontroller to read analog data from a moisture sensor and then sends this data via UART to an ESP32. The ESP32 hosts a web server that displays the moisture levels. Additionally, the system is designed to turn on a pump when the moisture levels fall below 20% and to indicate the moisture levels using three LEDs.

## Components
- PIC18F4580 Microcontroller
- ESP32 Module
- Moisture Sensor
- LEDs
- Pumps

## Configuration
The PIC18F4580 is configured to read the analog values from the moisture sensor using ADC. It then converts these values to a voltage percentage representation of the moisture levels. The UART communication is set up at a baud rate of 9600.

The ESP32 is set up as an access point with the SSID "Plant Status Monitor" and a predefined password. It hosts a web server that refreshes every 3 seconds to display the latest moisture levels.

## Operation
1. The PIC18F4580 continuously reads the moisture level from the sensor.
2. The ADC value is converted to a percentage and sent over UART to the ESP32.
3. The ESP32 updates the web server with the current moisture level.
4. If the moisture level is below 20%, the PIC18F4580 activates the pump.
5. The LEDs on the PIC18F4580 indicate the range of the moisture level:
   - Red LED for low (0-19%)
   - Yellow LED for medium (20-39%)
   - Green LED for high (40-100%)

## Web Server
The web server displays the moisture level with a color code:
- Red for low moisture
- Orange for medium moisture
- Green for high moisture

## Setup Instructions
1. Connect the moisture sensor to the PIC18F4580.
2. Connect the LEDs and the pump to the appropriate pins on the PIC18F4580.
3. Set up the ESP32 with the provided code and connect it to the PIC18F4580 via UART.
4. Power up the system and connect to the ESP32's WiFi network.
5. Access the web server using the IP address displayed in the serial monitor.

## Code
The code for both the PIC18F4580 and the ESP32 is included in the project files. Ensure to configure the microcontroller and the module according to the pin definitions and settings provided in the code comments.

## Safety
Ensure that all electrical connections are secure and that the pump is suitable for the voltage provided by the PIC18F4580.

## License
This project is released under the MIT License.
